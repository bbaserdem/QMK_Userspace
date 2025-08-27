#!/usr/bin/env -S uv run --script
#
# /// script
# dependencies = [
#   "monobit",
#   "pillow",
# ]
# ///

import os
from pathlib import Path

import monobit

# Get repository root from environment variable
git_root = Path(os.environ.get("GIT_WT_DIR", os.getcwd()))

# Set your font file path here
font_file = git_root / "users" / "batuhan" / "assets" / "fonts" / "LanaPixel_BitmapOnly.ttf"
# Output directory for extracted glyphs
output_dir = git_root / "users" / "batuhan" / "assets" / "glyphs_bmp"
output_dir.mkdir(parents=True, exist_ok=True)

# Turkish F Keyboard all characters (regular, shifted, and AltGr)
# fmt: off
turkish_f_letters = [
    # Turkish and English letters (uppercase and lowercase)
    "A", "B", "C", "Ç", "D", "E", "F", "G", "Ğ", "H", "I", "İ", "J", "K", "L", "M",
    "N", "O", "Ö", "P", "Q", "R", "S", "Ş", "T", "U", "Ü", "V", "W", "X", "Y", "Z",
    "a", "b", "c", "ç", "d", "e", "f", "g", "ğ", "h", "ı", "i", "j", "k", "l", "m",
    "n", "o", "ö", "p", "q", "r", "s", "ş", "t", "u", "ü", "v", "w", "x", "y", "z",
    
    # Numbers
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    
    # Basic punctuation and symbols
    " ", "!", '"', "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/",
    ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "{", "|", "}", "~",
    
    # Additional symbols from shifted keys
    "¬", "±", "°", "£", "¦", "´", "·", "×", "÷",
    
    # AltGr accessible characters
    "€", "₺",  # Currency symbols
    "¡", "¿",  # Inverted punctuation
    "¢", "¥", "§", "©", "®", "µ", "¶",  # Various symbols
    "¹", "²", "³", "¼", "½", "¾", "⅜",  # Superscripts and fractions
    "«", "»",  # Guillemets (angle quotes)
    """, """,  # Smart quotes
    "Â", "Î", "Ô", "Û",  # Accented uppercase
    "â", "î", "ô", "û",  # Accented lowercase
    "À", "Á", "Ä", "Å",  # More accented uppercase
    "à", "á", "ä", "å",  # More accented lowercase
    "ǎ", "ȧ",  # Special accented characters
]
# fmt: on
letters_set = set(turkish_f_letters)

print(f"Loading font from: {font_file}")
font = monobit.load(str(font_file))[0]

print(f"Font dimensions: {font.cell_size}")

# Counter for extracted glyphs
extracted_count = 0

# Iterate through all codepoints in font
for glyph in font.glyphs:
    char = glyph.char
    codepoint = glyph.codepoint
    # Export all glyphs or just those present in Turkish F keyboard
    if char and (char in letters_set or not char.isprintable()):
        # Create safe filename - replace problematic characters
        safe_char = char if char not in ['/', '\\', '"', '*', '?', '<', '>', '|', ':'] else f"chr{ord(char)}"
        filename = (
            output_dir / f"U+{ord(char):04X}_{safe_char}.bmp"
            if char
            else output_dir / f"glyph_{codepoint}.bmp"
        )
        glyph.as_image().save(str(filename), "BMP")
        extracted_count += 1
        print(f"Extracted: U+{ord(char):04X} ({char})")

print(f"\nExtracted {extracted_count} glyphs to: {output_dir}")
print(f"Font cell size: {font.cell_size}")