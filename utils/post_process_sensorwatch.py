import re

NAME_LEN = 6
ALLOWED_CHARS = (
    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ "
)

ZONE_ARRAY_RE = re.compile(
    r'const unsigned char zone_names\[\d+\]\s*=\s*\{(.*?)\};',
    re.S
)
ZONE_DEFNS_RE = re.compile(
    r'const uzone_packed_t zone_defns\[\d+\] = \{(.*?)\};',
    re.S
)
UTZ_DEFINE_RE = re.compile(r"#define\s+(UTZ_[A-Z0-9_]+)\s+(\d+)")

def sanitize_char(c):
    if c == '\\':
        return ' '
    return c if c in ALLOWED_CHARS else ' '

def rewrite_zones(c_path, h_path):
    # --- Load zones.c ---
    with open(c_path, "r", encoding="utf-8") as f:
        text = f.read()

    # Parse zone_names
    match = ZONE_ARRAY_RE.search(text)
    if not match:
        raise RuntimeError("zone_names array not found")
    tokens = re.findall(r"'(.)'|(\d+)", match.group(1))
    entries = []
    i = 0
    while i < len(tokens):
        name_chars = []
        while i < len(tokens) and tokens[i][1] == '':
            name_chars.append(tokens[i][0])
            i += 1
        if i < len(tokens) and tokens[i][1] == '0':
            i += 1
        else:
            raise RuntimeError("Expected NUL byte after zone name")
        if i < len(tokens) and tokens[i][1] != '':
            idx = int(tokens[i][1])
            i += 1
        else:
            raise RuntimeError("Expected index after NUL")
        sanitized = [sanitize_char(c) for c in name_chars]
        padded = sanitized[:NAME_LEN] + [' '] * (NAME_LEN - len(sanitized))
        entries.append({"name": padded, "orig_idx": idx})

    # Parse zone_defns
    defns_match = ZONE_DEFNS_RE.search(text)
    if not defns_match:
        raise RuntimeError("zone_defns not found")
    defns_tokens = re.findall(r"\{([^}]+)\}", defns_match.group(1))
    defns = []
    for idx, token in enumerate(defns_tokens):
        parts = [int(x.strip()) for x in token.split(",")]
        defns.append({"data": parts, "orig_idx": idx, "offset": parts[0]})

    # Map zone_names to defns
    for e in entries:
        e["offset"] = defns[e["orig_idx"]]["offset"]

    # Sort by offset ascending (most negative → most positive)
    entries.sort(key=lambda x: x["offset"])

    # Rebuild zone_names and zone_defns
    out_bytes = bytearray()
    new_zone_names = []
    new_zone_defns = []
    old_to_new = {}
    for new_idx, e in enumerate(entries):
        old_to_new[e["orig_idx"]] = new_idx
        chars = ",".join(f"'{c}'" for c in e["name"])
        new_zone_names.append(f"    {chars},'\\\\0',{new_idx},")
        out_bytes.extend(ord(c) for c in e["name"])
        out_bytes.append(0)
        out_bytes.append(new_idx)
        # zone_defns: preserve all fields except update index
        d = defns[e["orig_idx"]]["data"]
        new_zone_defns.append(f"{{ {d[0]},{d[1]},{d[2]},{new_idx} }},")

    # Write updated zone_names
    zone_names_array = f"const unsigned char zone_names[{len(out_bytes)}] = {{\n"
    zone_names_array += "\n".join(new_zone_names)
    zone_names_array += "\n};"
    text = ZONE_ARRAY_RE.sub(zone_names_array, text)

    # Write updated zone_defns
    zone_defns_array = f"const uzone_packed_t zone_defns[{len(new_zone_defns)}] = {{\n"
    zone_defns_array += "\n".join(new_zone_defns)
    zone_defns_array += "\n};"
    text = ZONE_DEFNS_RE.sub(zone_defns_array, text)

    with open(c_path, "w", encoding="utf-8") as f:
        f.write(text)
    print(f"Updated {c_path} — {len(new_zone_defns)} zones sorted by offset")

    # --- Update zones.h ---
    with open(h_path, "r", encoding="utf-8") as f:
        h_text = f.read()

    h_text = re.sub(
        r"#define NUM_ZONE_NAMES \d+",
        f"#define NUM_ZONE_NAMES {len(entries)}",
        h_text
    )
    h_text = re.sub(
        r"extern const unsigned char zone_names\[\d+\]",
        f"extern const unsigned char zone_names[{len(out_bytes)}]",
        h_text
    )

    # Update UTZ_* defines
    def repl_define(m):
        name, idx = m.groups()
        idx = int(idx)
        return f"#define {name} {old_to_new[idx]}" if idx in old_to_new else f"/* {name} {idx} removed */"

    h_text = UTZ_DEFINE_RE.sub(repl_define, h_text)

    with open(h_path, "w", encoding="utf-8") as f:
        f.write(h_text)
    print(f"Updated {h_path}")

if __name__ == "__main__":
    rewrite_zones("zones.c", "zones.h")
