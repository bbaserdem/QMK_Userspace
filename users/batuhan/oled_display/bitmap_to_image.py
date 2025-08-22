import os

import monobit

# Set your font file path here
font_file = "your-font.otb"
# Output directory for extracted glyphs
output_dir = "glyphs_bmp"
os.makedirs(output_dir, exist_ok=True)

# Turkish F Keyboard letters (uppercase and lowercase)
turkish_f_letters = [
    # English and Turkish alphabet (A-Z, a-z) covered, plus Turkish specifics
    "A",
    "B",
    "C",
    "Ç",
    "D",
    "E",
    "F",
    "G",
    "Ğ",
    "H",
    "I",
    "İ",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "Ö",
    "P",
    "R",
    "S",
    "Ş",
    "T",
    "U",
    "Ü",
    "V",
    "Y",
    "Z",
    "a",
    "b",
    "c",
    "ç",
    "d",
    "e",
    "f",
    "g",
    "ğ",
    "h",
    "ı",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "ö",
    "p",
    "r",
    "s",
    "ş",
    "t",
    "u",
    "ü",
    "v",
    "y",
    "z",
]
letters_set = set(turkish_f_letters)

font = monobit.load(font_file)[0]

# Iterate through all codepoints in font
for glyph in font.glyphs:
    char = glyph.char
    codepoint = glyph.codepoint
    # Export all glyphs or just those present in Turkish F keyboard
    if char and (char in letters_set or not char.isprintable()):
        filename = (
            f"{output_dir}/U+{ord(char):04X}_{char}.bmp"
            if char
            else f"{output_dir}/glyph_{codepoint}.bmp"
        )
        glyph.as_image().save(filename, "BMP")

print(f"Exported glyphs to: {output_dir}")
