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
primary_font_file = git_root / "users" / "batuhan" / "assets" / "fonts" / "Philips_YES_T.otb"
fallback_font_file = git_root / "users" / "batuhan" / "assets" / "fonts" / "LanaPixel.ttf"
output_dir = git_root / "users" / "batuhan" / "assets" / "glyphs_bmp"
output_dir.mkdir(parents=True, exist_ok=True)

# EXACT target dimensions - 8x10 for Philips YES T font
GLYPH_WIDTH = 8
GLYPH_HEIGHT = 10

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

print(f"Loading fonts:")
print(f"  Primary: {primary_font_file}")
print(f"  Fallback: {fallback_font_file}")

# Load fonts - try different sizes for the primary font
primary_font = None
for size in [8, 9, 10, 11, 12, 13, 14, 15, 16]:
    try:
        test_font = ImageFont.truetype(str(primary_font_file), size)
        # Test with a character to see actual size
        test_img = Image.new('1', (20, 20), 1)
        test_draw = ImageDraw.Draw(test_img)
        bbox = test_draw.textbbox((0, 0), "A", font=test_font)
        char_height = bbox[3] - bbox[1]
        char_width = bbox[2] - bbox[0]
        print(f"  Philips YES T size {size}: {char_width}x{char_height}")
        # Philips YES T should be 8x10 or close to it
        if char_width <= 8 and char_height <= 10:
            primary_font = test_font
            primary_size = size
            print(f"  → Selected size {size} for Philips YES T")
            break
    except Exception as e:
        pass

if not primary_font:
    print("Warning: Could not load primary font optimally, using size 10")
    primary_font = ImageFont.truetype(str(primary_font_file), 10)
    primary_size = 10

# Load fallback font (LanaPixel at size 11)
fallback_font = ImageFont.truetype(str(fallback_font_file), 11)
print(f"  LanaPixel loaded at size 11 (will clip bottom row)")

print(f"\nExtracting glyphs with dimensions: {GLYPH_WIDTH}x{GLYPH_HEIGHT} pixels\n")

# Helper function to check if a glyph is just a rectangle (missing glyph)
def is_rectangle_glyph(img, bbox):
    """Check if the rendered glyph is just a rectangle (missing character indicator)"""
    # Extract the glyph region
    pixels = img.load()
    
    # Check if it's a filled rectangle pattern (usually missing glyphs are solid blocks)
    # Count black pixels in the bounding box area
    black_pixels = 0
    total_pixels = 0
    
    for y in range(bbox[1], min(bbox[3], 20)):
        for x in range(bbox[0], min(bbox[2], 20)):
            total_pixels += 1
            if pixels[x, y] == 0:  # Black pixel
                black_pixels += 1
    
    # If it's mostly filled (>80%), it's likely a missing glyph rectangle
    if total_pixels > 0 and black_pixels / total_pixels > 0.8:
        return True
    
    # Also check for hollow rectangle pattern
    # Check if all edges are black but interior might be white
    is_hollow = True
    for x in range(bbox[0], min(bbox[2], 20)):
        # Check top and bottom edges
        if pixels[x, bbox[1]] != 0 or pixels[x, min(bbox[3]-1, 19)] != 0:
            is_hollow = False
            break
    
    if is_hollow:
        for y in range(bbox[1], min(bbox[3], 20)):
            # Check left and right edges
            if pixels[bbox[0], y] != 0 or pixels[min(bbox[2]-1, 19), y] != 0:
                is_hollow = False
                break
    
    return is_hollow

# Helper function to render a character with a font
def render_glyph(char, font, font_name=""):
    # Create a temporary larger canvas
    temp_img = Image.new('1', (20, 20), 1)  # White background
    temp_draw = ImageDraw.Draw(temp_img)
    
    # Try to render the character
    try:
        # Get bounding box
        bbox = temp_draw.textbbox((0, 0), char, font=font)
        if bbox[2] - bbox[0] == 0 or bbox[3] - bbox[1] == 0:
            return None  # Character not available in this font
        
        # Draw the character
        temp_draw.text((0, 0), char, font=font, fill=0)
        
        # Check if it's a missing glyph (rectangle)
        if font_name == "Philips" and is_rectangle_glyph(temp_img, bbox):
            return None  # Missing glyph, try fallback
        
        # Create final 8x10 image
        final_img = Image.new('1', (GLYPH_WIDTH, GLYPH_HEIGHT), 1)
        
        # For LanaPixel (8x11), we clip the bottom row
        if font_name == "LanaPixel":
            # Crop to 8x10 (removing bottom row)
            char_crop = temp_img.crop((bbox[0], bbox[1], 
                                      min(bbox[2], bbox[0] + GLYPH_WIDTH), 
                                      min(bbox[3], bbox[1] + GLYPH_HEIGHT)))
        else:
            # For Philips YES T, use as is
            char_crop = temp_img.crop((bbox[0], bbox[1], 
                                      min(bbox[2], bbox[0] + GLYPH_WIDTH), 
                                      min(bbox[3], bbox[1] + GLYPH_HEIGHT)))
        
        # Calculate centering
        crop_width = char_crop.size[0]
        crop_height = char_crop.size[1]
        x_offset = (GLYPH_WIDTH - crop_width) // 2 if crop_width < GLYPH_WIDTH else 0
        y_offset = (GLYPH_HEIGHT - crop_height) // 2 if crop_height < GLYPH_HEIGHT else 0
        
        # Paste centered
        final_img.paste(char_crop, (x_offset, y_offset))
        
        return final_img
    except Exception as e:
        return None

# Extract glyphs
extracted_count = 0
primary_count = 0
fallback_count = 0

for char in turkish_f_letters:
    # Try primary font first
    glyph_img = render_glyph(char, primary_font, "Philips")
    used_font = "Philips"
    
    # If not available, try fallback font
    if glyph_img is None:
        glyph_img = render_glyph(char, fallback_font, "LanaPixel")
        used_font = "LanaPixel"
    
    if glyph_img is None:
        print(f"✗ U+{ord(char):04X} ({char}) - Not found in either font")
        continue
    
    # Create safe filename
    try:
        char_code = ord(char) if len(char) == 1 else ord(char[0])
        safe_char = char if char not in ['/', '\\', '"', '*', '?', '<', '>', '|', ':'] else f"chr{char_code}"
        filename = output_dir / f"U+{char_code:04X}_{safe_char}.bmp"
    except:
        continue
    
    # Save as BMP - exactly 8x10 pixels
    glyph_img.save(str(filename), "BMP")
    extracted_count += 1
    
    if used_font == "Philips":
        primary_count += 1
        print(f"✓ U+{char_code:04X} ({char}) - {GLYPH_WIDTH}x{GLYPH_HEIGHT}px [Philips]")
    else:
        fallback_count += 1
        print(f"✓ U+{char_code:04X} ({char}) - {GLYPH_WIDTH}x{GLYPH_HEIGHT}px [LanaPixel]")

print(f"\nExtracted {extracted_count} glyphs to: {output_dir}")
print(f"  Primary font (Philips YES T): {primary_count} glyphs")
print(f"  Fallback font (LanaPixel): {fallback_count} glyphs")
print(f"All glyphs are EXACTLY {GLYPH_WIDTH}x{GLYPH_HEIGHT} pixels")

# Create a sample sheet
cols = 16
rows = 10
sample_sheet = Image.new('1', (cols * GLYPH_WIDTH, rows * GLYPH_HEIGHT), 1)

# Draw sample characters
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

sample_sheet.save(str(output_dir / "sample_sheet_8x10.bmp"), "BMP")
print(f"\nSample sheet saved to: {output_dir / 'sample_sheet_8x10.bmp'}")
print(f"Grid: {cols} columns x {rows} rows, each cell exactly {GLYPH_WIDTH}x{GLYPH_HEIGHT} pixels")