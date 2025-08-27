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
font_file = git_root / "users" / "batuhan" / "assets" / "fonts" / "LanaPixel.ttf"
output_dir = git_root / "users" / "batuhan" / "assets" / "glyphs_bmp"
output_dir.mkdir(parents=True, exist_ok=True)

# EXACT target dimensions for QMK OLED
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

# Use size 11 which seems to work best for LanaPixel
FONT_SIZE = 11
font = ImageFont.truetype(str(font_file), FONT_SIZE)

print(f"Using font size: {FONT_SIZE}")
print(f"Creating glyphs with EXACT dimensions: {GLYPH_WIDTH}x{GLYPH_HEIGHT} pixels\n")

# Extract glyphs
extracted_count = 0
for char in turkish_f_letters:
    # Create a temporary larger canvas to draw the character
    temp_img = Image.new('1', (20, 20), 1)  # White background
    temp_draw = ImageDraw.Draw(temp_img)
    
    # Get the exact bounding box for this character
    bbox = temp_draw.textbbox((0, 0), char, font=font)
    
    # Calculate the actual size of the character
    char_width = bbox[2] - bbox[0]
    char_height = bbox[3] - bbox[1]
    
    # Draw the character on the temporary canvas
    temp_draw.text((0, 0), char, font=font, fill=0)  # Black text
    
    # Now create the final 8x11 image
    final_img = Image.new('1', (GLYPH_WIDTH, GLYPH_HEIGHT), 1)  # White background
    
    # Calculate centering offsets
    # For horizontal: center if it fits, otherwise left-align
    if char_width <= GLYPH_WIDTH:
        x_offset = (GLYPH_WIDTH - char_width) // 2
    else:
        x_offset = 0
    
    # For vertical: try to center in the 11-pixel height
    # Adjust for baseline - most chars should sit on a baseline around pixel 8
    # This leaves room for descenders (g, j, p, q, y) and ascenders
    if bbox[1] < 0:  # Has ascender (like Ğ, İ)
        y_offset = -bbox[1]  # Align to top
    elif bbox[3] > 8:  # Has descender (like g, j, p, q, y)
        y_offset = GLYPH_HEIGHT - (bbox[3] - bbox[1]) - 1  # Leave room at bottom
    else:  # Normal character
        # Place baseline at pixel 7-8 (leaves 3-4 pixels for descenders)
        y_offset = 7 - bbox[3]
    
    # Crop the character from temp image and paste to final image
    char_crop = temp_img.crop((bbox[0], bbox[1], min(bbox[2], bbox[0] + GLYPH_WIDTH), min(bbox[3], bbox[1] + GLYPH_HEIGHT)))
    final_img.paste(char_crop, (x_offset, y_offset))
    
    # Create safe filename
    try:
        char_code = ord(char) if len(char) == 1 else ord(char[0])
        safe_char = char if char not in ['/', '\\', '"', '*', '?', '<', '>', '|', ':'] else f"chr{char_code}"
        filename = output_dir / f"U+{char_code:04X}_{safe_char}.bmp"
    except:
        continue
    
    # Save as BMP - this will be EXACTLY 8x11 pixels
    final_img.save(str(filename), "BMP")
    extracted_count += 1
    
    # Verify the saved image dimensions
    saved_img = Image.open(str(filename))
    if saved_img.size != (GLYPH_WIDTH, GLYPH_HEIGHT):
        print(f"WARNING: {char} saved with wrong size: {saved_img.size}")
    else:
        print(f"✓ U+{char_code:04X} ({char}) - {GLYPH_WIDTH}x{GLYPH_HEIGHT}px")

print(f"\nExtracted {extracted_count} glyphs to: {output_dir}")
print(f"All glyphs are EXACTLY {GLYPH_WIDTH}x{GLYPH_HEIGHT} pixels")

# Create a sample sheet to verify alignment
cols = 16
rows = 10
sample_sheet = Image.new('1', (cols * GLYPH_WIDTH, rows * GLYPH_HEIGHT), 1)

# Draw sample characters directly on the grid
sample_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()[]{}+-=<>?ÇĞİÖŞÜçğıöşü€₺gjpqy"
for i, char in enumerate(sample_chars[:cols*rows]):
    col = i % cols
    row = i // cols
    
    # Load the saved BMP for this character
    try:
        char_code = ord(char) if len(char) == 1 else ord(char[0])
        safe_char = char if char not in ['/', '\\', '"', '*', '?', '<', '>', '|', ':'] else f"chr{char_code}"
        char_file = output_dir / f"U+{char_code:04X}_{safe_char}.bmp"
        
        if char_file.exists():
            char_img = Image.open(str(char_file))
            # Paste at exact grid position
            x_pos = col * GLYPH_WIDTH
            y_pos = row * GLYPH_HEIGHT
            sample_sheet.paste(char_img, (x_pos, y_pos))
    except:
        pass

sample_sheet.save(str(output_dir / "sample_sheet_8x11.bmp"), "BMP")
print(f"\nSample sheet saved to: {output_dir / 'sample_sheet_8x11.bmp'}")
print(f"Grid: {cols} columns x {rows} rows, each cell exactly {GLYPH_WIDTH}x{GLYPH_HEIGHT} pixels")