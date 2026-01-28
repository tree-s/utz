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

# Regex to match #define UTZ_* lines
UTZ_DEFINE_RE = re.compile(r"#define\s+(UTZ_[A-Z0-9_]+)\s+(\d+)")

def sanitize_char(c):
    if c == '\\':
        return ' '
    return c if c in ALLOWED_CHARS else ' '

def rewrite_zones(c_path, h_path):
    # --- Process zones.c ---
    with open(c_path, "r", encoding="utf-8") as f:
        text = f.read()

    match = ZONE_ARRAY_RE.search(text)
    if not match:
        raise RuntimeError("zone_names array not found in zones.c")

    body = match.group(1)
    tokens = re.findall(r"'(.)'|(\d+)", body)

    entries = []
    seen_idxs = set()
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
            raise RuntimeError("Expected index byte after NUL")

        if idx in seen_idxs:
            continue
        seen_idxs.add(idx)

        sanitized = [sanitize_char(c) for c in name_chars]
        padded = sanitized[:NAME_LEN] + [' '] * (NAME_LEN - len(sanitized))
        entries.append((padded, idx))

    # Rebuild zone_names array
    new_lines = []
    out_bytes = bytearray()
    for zone_index, (name, idx) in enumerate(entries):
        chars = ",".join(f"'{c}'" for c in name)
        new_lines.append(f"    {chars},'\\0',{idx}, // zone {zone_index}")
        out_bytes.extend(ord(c) for c in name)
        out_bytes.append(0)
        out_bytes.append(idx)

    new_array = f"const unsigned char zone_names[{len(out_bytes)}] = {{\n"
    new_array += "\n".join(new_lines)
    new_array += "\n};"

    new_text = text[:match.start()] + new_array + text[match.end():]

    with open(c_path, "w", encoding="utf-8") as f:
        f.write(new_text)
    print(f"Updated {c_path} — {len(entries)} unique zones, {len(out_bytes)} bytes")

    # --- Update zones.h ---
    with open(h_path, "r", encoding="utf-8") as f:
        h_text = f.read()

    # Update NUM_ZONE_NAMES
    h_text = re.sub(
        r"#define NUM_ZONE_NAMES \d+",
        f"#define NUM_ZONE_NAMES {len(entries)}",
        h_text
    )

    # Update zone_names array size
    h_text = re.sub(
        r"extern const unsigned char zone_names\[\d+\]",
        f"extern const unsigned char zone_names[{len(out_bytes)}]",
        h_text
    )

    # Update UTZ_* defines — only keep idx that are in seen_idxs
    def repl_define(m):
        name, idx = m.groups()
        idx = int(idx)
        return f"#define {name} {idx}" if idx in seen_idxs else f"/* {name} {idx} removed */"

    h_text = UTZ_DEFINE_RE.sub(repl_define, h_text)

    with open(h_path, "w", encoding="utf-8") as f:
        f.write(h_text)
    print(f"Updated {h_path}")

if __name__ == "__main__":
    rewrite_zones("zones.c", "zones.h")
