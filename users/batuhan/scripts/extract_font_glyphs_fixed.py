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

# Target font size - LanaPixel is designed for 8x11
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

# Try different font sizes to find the best fit
# Pixel fonts often need exact sizes
best_size = None
for size in [8, 9, 10, 11, 12, 13, 14, 15, 16]:
    try:
        test_font = ImageFont.truetype(str(font_file), size)
        # Test render to check actual dimensions
        test_img = Image.new('1', (20, 20), 1)
        test_draw = ImageDraw.Draw(test_img)
        
        # Get bounding box for a test character
        bbox = test_draw.textbbox((0, 0), "A", font=test_font)
        char_width = bbox[2] - bbox[0]
        char_height = bbox[3] - bbox[1]
        
        print(f"Size {size}: bbox={bbox}, width={char_width}, height={char_height}")
        
        # LanaPixel should fit in 8x11 - prefer size 11 which gives us 6x7 chars
        if size == 11:  # Force size 11 which seems to be the right size
            best_size = size
            best_font = test_font
            best_bbox_offset = (bbox[0], bbox[1])
            break
    except Exception as e:
        print(f"Error at size {size}: {e}")

if not best_size:
    print("Warning: Could not find optimal size, using default")
    best_size = 11
    best_font = ImageFont.truetype(str(font_file), best_size)
    best_bbox_offset = (0, 0)

print(f"\nUsing font size: {best_size}")
print(f"Bbox offset: {best_bbox_offset}")

# Extract glyphs
extracted_count = 0
for char in turkish_f_letters:
    # Create a new image with white background
    img = Image.new('1', (GLYPH_WIDTH, GLYPH_HEIGHT), 1)  # 1-bit image, white background
    draw = ImageDraw.Draw(img)
    
    # Get the exact bounding box for this character
    bbox = draw.textbbox((0, 0), char, font=best_font)
    
    # Calculate position to center the glyph in the 8x11 canvas
    # Account for the bbox offset
    x_offset = -bbox[0]  # Compensate for left bearing
    y_offset = -bbox[1]  # Compensate for top bearing
    
    # Draw the character with proper offset
    draw.text((x_offset, y_offset), char, font=best_font, fill=0)  # Black text on white
    
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
    print(f"Extracted: U+{char_code:04X} ({char}) - bbox: {bbox}")

print(f"\nExtracted {extracted_count} glyphs to: {output_dir}")

# Create a better sample sheet with grid lines
cols = 16
rows = 10
cell_padding = 2
sheet_width = cols * (GLYPH_WIDTH + cell_padding) + cell_padding
sheet_height = rows * (GLYPH_HEIGHT + cell_padding) + cell_padding

sample_sheet = Image.new('1', (sheet_width, sheet_height), 1)
draw = ImageDraw.Draw(sample_sheet)

# Draw grid lines (optional, comment out if not needed)
for i in range(cols + 1):
    x = i * (GLYPH_WIDTH + cell_padding)
    draw.line([(x, 0), (x, sheet_height)], fill=0, width=1)
for i in range(rows + 1):
    y = i * (GLYPH_HEIGHT + cell_padding)
    draw.line([(0, y), (sheet_width, y)], fill=0, width=1)

# Draw characters in grid
sample_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()[]{}+-=<>?ÇĞİÖŞÜçğıöşü€₺"
for i, char in enumerate(sample_chars[:cols*rows]):
    col = i % cols
    row = i // cols
    
    # Calculate position in grid
    x_pos = col * (GLYPH_WIDTH + cell_padding) + cell_padding
    y_pos = row * (GLYPH_HEIGHT + cell_padding) + cell_padding
    
    # Get bbox for proper positioning
    bbox = draw.textbbox((0, 0), char, font=best_font)
    x_offset = x_pos - bbox[0]
    y_offset = y_pos - bbox[1]
    
    draw.text((x_offset, y_offset), char, font=best_font, fill=0)

sample_sheet.save(str(output_dir / "sample_sheet_grid.bmp"), "BMP")
print(f"Sample sheet with grid saved to: {output_dir / 'sample_sheet_grid.bmp'}")