/** @file test_timezone.c
 *  @brief Comprehensive test for u Time Zone Library with progress and summary
 *  @author tree-s
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utz.h"
#include "../zones.h"

#define TEST_PRINT(...)  printf(__VA_ARGS__)

/* ------------------------------------------------------------- */
/* Helpers                                                       */
/* ------------------------------------------------------------- */

static int valid_offset(const uoffset_t* o) {
    if (o->minutes < 0 || o->minutes >= 60)
        return 0;
    if (o->hours < -14 || o->hours > 14)
        return 0;
    return 1;
}

static int offset_minutes(const uoffset_t* o) {
    return (int)o->hours * 60 + (int)o->minutes;
}

/* Apply offset to a UTC time and normalize */
static void apply_offset(
    int utc_hour,
    int utc_minute,
    const uoffset_t* off,
    int* out_hour,
    int* out_minute
) {
    int total = utc_hour * 60 + utc_minute;
    total += off->hours * 60 + off->minutes;

    total %= (24 * 60);
    if (total < 0)
        total += (24 * 60);

    *out_hour = total / 60;
    *out_minute = total % 60;
}

/* ------------------------------------------------------------- */
/* Test runner                                                   */
/* ------------------------------------------------------------- */

int test_all_generated_zones(void) {
    TEST_PRINT("Testing all generated zones...\n");

    udatetime_t winter = {
        .date = { .year = UYEAR_FROM_YEAR(2025), .month = 1, .dayofmonth = 15, .dayofweek = 0 },
        .time = { .hour = 12, .minute = 0, .second = 0 }
    };

    udatetime_t summer = {
        .date = { .year = UYEAR_FROM_YEAR(2025), .month = 7, .dayofmonth = 15, .dayofweek = 0 },
        .time = { .hour = 12, .minute = 0, .second = 0 }
    };

    /* Treat these as UTC reference times */
    const int utc_hour = 12;
    const int utc_minute = 0;

    const unsigned char* name_ptr = zone_names;

    int total_zones = NUM_ZONE_NAMES;
    int passed_zones = 0;

    for (int i = 0; i < total_zones; i++) {
        const char* zone_name = (const char*)name_ptr;
        uint8_t defn_idx = name_ptr[strlen(zone_name) + 1];

        uzone_t zone;
        unpack_zone(&zone_defns[defn_idx], zone_name, &zone);

        uoffset_t off_winter, off_summer;
        char l_winter = get_current_offset(&zone, &winter, &off_winter);
        char l_summer = get_current_offset(&zone, &summer, &off_summer);

        int winter_min = offset_minutes(&off_winter);
        int summer_min = offset_minutes(&off_summer);

        int zone_passed = 1;

        TEST_PRINT("[%d/%d] Testing %s: rules_len=%d\n",
                   i + 1, total_zones, zone_name, zone.rules_len);


        TEST_PRINT("  Winter offset: %s%d:%02d\n",
                   (off_winter.hours >= 0 ? "+" : ""),
                   off_winter.hours, off_winter.minutes);

        TEST_PRINT("  Summer offset: %s%d:%02d\n",
                   (off_summer.hours >= 0 ? "+" : ""),
                   off_summer.hours, off_summer.minutes);

        /* -------------------------------------------------- */
        /* Offset sanity                                     */
        /* -------------------------------------------------- */

        if (!valid_offset(&off_winter)) {
            TEST_PRINT("  ERROR: invalid winter offset (%d:%d)\n",
                       off_winter.hours, off_winter.minutes);
            zone_passed = 0;
        }

        if (!valid_offset(&off_summer)) {
            TEST_PRINT("  ERROR: invalid summer offset (%d:%d)\n",
                       off_summer.hours, off_summer.minutes);
            zone_passed = 0;
        }

        /* -------------------------------------------------- */
        /* No-DST zones must not change offset                */
        /* -------------------------------------------------- */

        if (zone.rules_len == 0) {
            if (winter_min != summer_min) {
                TEST_PRINT("  ERROR: offset changed without DST (%d -> %d)\n",
                           winter_min, summer_min);
                zone_passed = 0;
            }
        } else {
            int delta = summer_min - winter_min;
            if (delta != 60 && delta != -60) {
                TEST_PRINT("  ERROR: invalid DST delta (%d minutes)\n", delta);
                zone_passed = 0;
            }

            if (l_winter == l_summer && l_winter != '-') {
                TEST_PRINT("  ERROR: DST letter did not change (%c)\n", l_winter);
                zone_passed = 0;
            }

            if (off_winter.minutes != off_summer.minutes) {
                TEST_PRINT("  ERROR: DST changed minutes (%d -> %d)\n",
                           off_winter.minutes, off_summer.minutes);
                zone_passed = 0;
            }
        }

        /* -------------------------------------------------- */
        /* Local clock correctness                            */
        /* -------------------------------------------------- */

        int local_h, local_m;
        int expected_h;

        /* Winter */
        apply_offset(utc_hour, utc_minute, &off_winter, &local_h, &local_m);

        expected_h = (utc_hour + off_winter.hours) % 24;
        if (expected_h < 0) expected_h += 24;

        if (local_m != off_winter.minutes) {
            TEST_PRINT("  ERROR: winter minute mismatch (expected %d, got %d)\n",
                       off_winter.minutes, local_m);
            zone_passed = 0;
        }

        if (local_h != expected_h) {
            TEST_PRINT("  ERROR: winter hour mismatch (expected %d, got %d)\n",
                       expected_h, local_h);
            zone_passed = 0;
        }

        /* Summer */
        apply_offset(utc_hour, utc_minute, &off_summer, &local_h, &local_m);

        expected_h = (utc_hour + off_summer.hours) % 24;
        if (expected_h < 0) expected_h += 24;

        if (local_m != off_summer.minutes) {
            TEST_PRINT("  ERROR: summer minute mismatch (expected %d, got %d)\n",
                       off_summer.minutes, local_m);
            zone_passed = 0;
        }

        if (local_h != expected_h) {
            TEST_PRINT("  ERROR: summer hour mismatch (expected %d, got %d)\n",
                       expected_h, local_h);
            zone_passed = 0;
        }

        if (zone_passed)
            passed_zones++;

        /* advance to next zone name */
        name_ptr += strlen(zone_name) + 2;
    }

    double percent = ((double)passed_zones / total_zones) * 100.0;
    TEST_PRINT("\nTest Summary: %d/%d zones passed (%.2f%%)\n",
               passed_zones, total_zones, percent);

    return passed_zones == total_zones ? 1 : 0;
}

/* ------------------------------------------------------------- */

int main(void) {
    return test_all_generated_zones() ? 0 : 1;
}
