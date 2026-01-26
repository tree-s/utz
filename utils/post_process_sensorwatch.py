import re

# Fixed length of zone names (for display or truncation)
NAME_LEN = 6

# Allowed characters (from your Custom_LCD_Character_Set)
ALLOWED_CHARS = (
    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ "
)

# Regex to match the zone_names array
ZONE_ARRAY_RE = re.compile(
    r'const unsigned char zone_names\[\d+\]\s*=\s*\{(.*?)\};',
    re.S
)


def sanitize_char(c):
    """Return the character if allowed and not a literal backslash, else space"""
    if c == '\\':
        return ' '
    return c if c in ALLOWED_CHARS else ' '


def rewrite_zone_names(zones_c_path):
    with open(zones_c_path, "r", encoding="utf-8") as f:
        text = f.read()

    match = ZONE_ARRAY_RE.search(text)
    if not match:
        raise RuntimeError("zone_names array not found")

    # Extract array body
    body = match.group(1)
    # Match either char literals or integer bytes
    tokens = re.findall(r"'(.)'|(\d+)", body)

    entries = []
    i = 0
    while i < len(tokens):
        # Read characters until we hit the NUL (0)
        name_chars = []
        while i < len(tokens) and tokens[i][1] == '':
            name_chars.append(tokens[i][0])
            i += 1

        # Skip the 0 (NUL terminator)
        if i < len(tokens) and tokens[i][1] == '0':
            i += 1
        else:
            raise RuntimeError("Expected NUL byte after zone name")

        # Read index byte
        if i < len(tokens) and tokens[i][1] != '':
            idx = int(tokens[i][1])
            i += 1
        else:
            raise RuntimeError("Expected index byte after NUL")

        # Sanitize characters
        sanitized = [sanitize_char(c) for c in name_chars]
        # Pad or truncate
        padded = sanitized[:NAME_LEN] + [' '] * (NAME_LEN - len(sanitized))
        entries.append((padded, idx))

    # Build new array
    new_lines = []
    out_bytes = bytearray()
    for zone_index, (name, idx) in enumerate(entries):
        chars = ",".join(f"'{c}'" for c in name)
        new_lines.append(f"    {chars},'\\0',{idx}, // zone {zone_index}")
        out_bytes.extend([ord(c) for c in name])
        out_bytes.append(0)  # NUL terminator
        out_bytes.append(idx)

    new_array = f"const unsigned char zone_names[{len(out_bytes)}] = {{\n"
    new_array += "\n".join(new_lines)
    new_array += "\n};"

    # Replace the old array in zones.c
    new_text = text[:match.start()] + new_array + text[match.end():]

    with open(zones_c_path, "w", encoding="utf-8") as f:
        f.write(new_text)

    print(f"Updated zone_names[] — new size: {len(out_bytes)} bytes")


if __name__ == "__main__":
    rewrite_zone_names("zones.c")
