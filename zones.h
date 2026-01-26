#ifndef _ZONES_H
#define _ZONES_H

extern const urule_packed_t zone_rules[20];
extern const char zone_abrevs[162];

#define MAX_ABREV_FORMATTER_LEN 7

extern const uzone_packed_t zone_defns[47];
#define UTZ_CAIRO               0
#define UTZ_BRAZZAVILLE         1
#define UTZ_HARARE              2
#define UTZ_NAIROBI             3
#define UTZ_ANCHORAGE           4
#define UTZ_SAO_PAULO           5
#define UTZ_BUENOS_AIRES        5
#define UTZ_RIO_DE_JANEIRO      5
#define UTZ_BELO_HORIZONTE      5
#define UTZ_CHICAGO             6
#define UTZ_DALLASFORT_WORTH    6
#define UTZ_HOUSTON             6
#define UTZ_DENVER              7
#define UTZ_HALIFAX             8
#define UTZ_LOS_ANGELES         9
#define UTZ_TIJUANA             9
#define UTZ_SAN_FRANCISCO       9
#define UTZ_INLAND_EMPIRE       9
#define UTZ_MANAUS              10
#define UTZ_MEXICO_CITY         11
#define UTZ_REGINA              11
#define UTZ_GUADALAJARA         11
#define UTZ_NEW_YORK            12
#define UTZ_WASHINGTON_DC       12
#define UTZ_PHILADELPHIA        12
#define UTZ_MIAMI               12
#define UTZ_ATLANTA             12
#define UTZ_BOSTON              12
#define UTZ_GODTHAB             13
#define UTZ_PHOENIX             14
#define UTZ_SANTIAGO            15
#define UTZ_ST_JOHNS            16
#define UTZ_BANGKOK             17
#define UTZ_DUBAI               18
#define UTZ_HONG_KONG           19
#define UTZ_JERUSALEM           20
#define UTZ_KARACHI             21
#define UTZ_LAHORE              21
#define UTZ_KATMANDU            22
#define UTZ_KOLKATA             23
#define UTZ_CALCUTTA            23
#define UTZ_DELHI               23
#define UTZ_MUMBAI              23
#define UTZ_BANGALORE           23
#define UTZ_CHENNAI             23
#define UTZ_HYDERABAD           23
#define UTZ_AHMEDABAD           23
#define UTZ_PUNE                23
#define UTZ_SURAT               23
#define UTZ_ISTANBUL            24
#define UTZ_KUWAIT              24
#define UTZ_ANKARA              24
#define UTZ_SEOUL               25
#define UTZ_SHANGHAI            26
#define UTZ_TAIPEI              26
#define UTZ_CHONGQING           26
#define UTZ_GUANGZHOU           26
#define UTZ_BEIJING             26
#define UTZ_SHENZHEN            26
#define UTZ_WUHAN               26
#define UTZ_CHENGDU             26
#define UTZ_TIANJIN             26
#define UTZ_HANGZHOU            26
#define UTZ_XIAN                26
#define UTZ_CHANGZHOU           26
#define UTZ_NANJING             26
#define UTZ_JINAN               26
#define UTZ_ZHENGZHOU           26
#define UTZ_QINGDAO             26
#define UTZ_SHENYANG            26
#define UTZ_WENZHOU             26
#define UTZ_NANCHANG            26
#define UTZ_KUALA_LUMPUR        27
#define UTZ_TEHRAN              28
#define UTZ_TOKYO               29
#define UTZ_OSAKA               29
#define UTZ_NAGOYA              29
#define UTZ_RANGOON             30
#define UTZ_ADELAIDE            31
#define UTZ_BRISBANE            32
#define UTZ_DARWIN              33
#define UTZ_HOBART              34
#define UTZ_PERTH               35
#define UTZ_SYDNEY              36
#define UTZ_UTC                 37
#define UTZ_ATHENS              38
#define UTZ_HELSINKI            38
#define UTZ_BELGRADE            39
#define UTZ_BERLIN              39
#define UTZ_BRUSSELS            39
#define UTZ_MADRID              39
#define UTZ_ROME                39
#define UTZ_AMSTERDAM           39
#define UTZ_SARAJEVO            39
#define UTZ_RHINERUHR           39
#define UTZ_BARCELONA           39
#define UTZ_MUNICH              39
#define UTZ_STUTTGART           39
#define UTZ_HAMBURG             39
#define UTZ_MILAN               39
#define UTZ_LONDON              40
#define UTZ_MOSCOW              41
#define UTZ_AUCKLAND            42
#define UTZ_GUAM                43
#define UTZ_HONOLULU            44
#define UTZ_MIDWAY              45
#define UTZ_MAJURO              46

#define NUM_ZONE_NAMES 107
#define MAX_ZONE_NAME_LEN 17

extern const unsigned char zone_names[1026];
#endif /* _ZONES_H */