#!/usr/bin/env -S uv run --script
#
# /// script
# dependencies = [
#   "pillow",
#   "fonttools",
# ]
# ///

import os
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

# Get repository root from environment variable
git_root = Path(os.environ.get("GIT_WT_DIR", os.getcwd()))

# Font configuration
font_file = git_root / "users" / "batuhan" / "assets" / "fonts" / "LanaPixel_BitmapOnly.ttf"
output_dir = git_root / "users" / "batuhan" / "assets" / "glyphs_bmp"
output_dir.mkdir(parents=True, exist_ok=True)

# Target font size (LanaPixel is 8x11)
FONT_SIZE = 11  # This might need adjustment
GLYPH_WIDTH = 8
GLYPH_HEIGHT = 11

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

print(f"Loading font from: {font_file}")

# Load the font
try:
    font = ImageFont.truetype(str(font_file), FONT_SIZE)
except Exception as e:
    print(f"Error loading font: {e}")
    # Try different sizes
    for size in [8, 9, 10, 11, 12, 13, 14]:
        try:
            font = ImageFont.truetype(str(font_file), size)
            print(f"Successfully loaded font at size {size}")
            FONT_SIZE = size
            break
        except:
            pass

# Extract glyphs
extracted_count = 0
for char in turkish_f_letters:
    # Create a new image with white background
    img = Image.new('1', (GLYPH_WIDTH, GLYPH_HEIGHT), 1)  # 1-bit image, white background
    draw = ImageDraw.Draw(img)
    
    # Draw the character
    # We need to position it correctly - pixel fonts often need specific positioning
    draw.text((0, -2), char, font=font, fill=0)  # Black text on white
    
    # Create safe filename
    try:
        char_code = ord(char) if len(char) == 1 else ord(char[0])  # Handle multi-byte chars
        safe_char = char if char not in ['/', '\\', '"', '*', '?', '<', '>', '|', ':'] else f"chr{char_code}"
        filename = output_dir / f"U+{char_code:04X}_{safe_char}.bmp"
    except:
        continue  # Skip problematic characters
    
    # Save as BMP
    img.save(str(filename), "BMP")
    extracted_count += 1
    print(f"Extracted: U+{char_code:04X} ({char})")

print(f"\nExtracted {extracted_count} glyphs to: {output_dir}")
print(f"Font size used: {FONT_SIZE}")

# Also save a sample sheet to verify the glyphs look correct
sample_sheet = Image.new('1', (GLYPH_WIDTH * 16, GLYPH_HEIGHT * 8), 1)
draw = ImageDraw.Draw(sample_sheet)

# Draw a grid of common characters
sample_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()[]{}+-=<>?"
for i, char in enumerate(sample_chars[:128]):  # Limit to 128 chars (8x16 grid)
    x = (i % 16) * GLYPH_WIDTH
    y = (i // 16) * GLYPH_HEIGHT
    draw.text((x, y - 2), char, font=font, fill=0)

sample_sheet.save(str(output_dir / "sample_sheet.bmp"), "BMP")
print(f"Sample sheet saved to: {output_dir / 'sample_sheet.bmp'}")