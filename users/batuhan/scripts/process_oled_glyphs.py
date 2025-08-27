#!/usr/bin/env -S uv run --script
#
# /// script
# dependencies = [
#   "pillow",
#   "fonttools",
#   "monobit",
#   "click",
#   "rich",
# ]
# ///

"""
Master OLED Glyph Processing Script
Orchestrates the complete workflow for extracting, processing, and generating
OLED display assets for QMK keyboards.
"""

import os
import subprocess
import sys
from pathlib import Path
from typing import List, Dict, Tuple, Optional
import json
import click
from rich.console import Console
from rich.progress import Progress, SpinnerColumn, TextColumn, BarColumn
from rich.table import Table
from PIL import Image, ImageDraw, ImageFont

console = Console()

# Get repository root
git_root = Path(os.environ.get("GIT_WT_DIR", os.getcwd()))
assets_dir = git_root / "users" / "batuhan" / "assets"
scripts_dir = git_root / "users" / "batuhan" / "scripts"
fonts_dir = assets_dir / "fonts"
glyphs_dir = assets_dir / "glyphs_bmp"
layouts_dir = assets_dir / "layouts"
headers_dir = git_root / "users" / "batuhan" / "src" / "oled"

# Configuration
GLYPH_WIDTH = 8
GLYPH_HEIGHT = 11
FONT_SIZE = 11

# Define all required characters for Turkish F keyboard
REQUIRED_CHARS = {
    'letters': [
        # Turkish and English letters
        "A", "B", "C", "Ç", "D", "E", "F", "G", "Ğ", "H", "I", "İ", "J", "K", "L", "M",
        "N", "O", "Ö", "P", "Q", "R", "S", "Ş", "T", "U", "Ü", "V", "W", "X", "Y", "Z",
        "a", "b", "c", "ç", "d", "e", "f", "g", "ğ", "h", "ı", "i", "j", "k", "l", "m",
        "n", "o", "ö", "p", "q", "r", "s", "ş", "t", "u", "ü", "v", "w", "x", "y", "z",
    ],
    'numbers': ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"],
    'punctuation': [
        " ", "!", '"', "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/",
        ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "{", "|", "}", "~",
    ],
    'symbols': [
        "¬", "±", "°", "£", "¦", "´", "·", "×", "÷",
        "€", "₺",  # Currency
        "¡", "¿",  # Inverted
        "¢", "¥", "§", "©", "®", "µ", "¶",
        "¹", "²", "³", "¼", "½", "¾", "⅜",  # Superscripts/fractions
        "«", "»",  # Guillemets
        """, """,  # Smart quotes
    ],
    'accented': [
        "Â", "Î", "Ô", "Û",  # Accented uppercase
        "â", "î", "ô", "û",  # Accented lowercase
        "À", "Á", "Ä", "Å",
        "à", "á", "ä", "å",
        "ǎ", "ȧ",
    ],
    'special_keys': [
        # These will need custom glyphs
        "⌫", "⏎", "⇥", "⇧", "⌃", "⌥", "⌘",  # Modifier keys
        "↑", "↓", "←", "→",  # Arrow keys
        "⇞", "⇟", "⇱", "⇲",  # Page Up/Down, Home/End
        "⎋", "⌦", "⎀",  # Esc, Delete, Insert
    ]
}


class OLEDGlyphProcessor:
    def __init__(self):
        self.glyphs_dir = glyphs_dir
        self.glyphs_dir.mkdir(parents=True, exist_ok=True)
        self.missing_glyphs = []
        self.extracted_glyphs = []
        
    def step_1_extract_font_glyphs(self):
        """Extract glyphs from font files"""
        console.print("\n[bold cyan]Step 1: Extracting Font Glyphs[/bold cyan]")
        
        font_files = list(fonts_dir.glob("*.ttf")) + list(fonts_dir.glob("*.otb"))
        if not font_files:
            console.print("[red]No font files found![/red]")
            return False
            
        primary_font = fonts_dir / "LanaPixel.ttf"
        if not primary_font.exists():
            console.print(f"[yellow]Primary font not found at {primary_font}, using first available[/yellow]")
            primary_font = font_files[0]
            
        console.print(f"Using font: {primary_font.name}")
        
        # Load font
        try:
            font = ImageFont.truetype(str(primary_font), FONT_SIZE)
        except Exception as e:
            console.print(f"[red]Error loading font: {e}[/red]")
            return False
            
        # Extract all characters
        all_chars = []
        for category in REQUIRED_CHARS.values():
            all_chars.extend(category)
            
        extracted_count = 0
        missing_count = 0
        
        with Progress(
            SpinnerColumn(),
            TextColumn("[progress.description]{task.description}"),
            BarColumn(),
            console=console
        ) as progress:
            task = progress.add_task("Extracting glyphs...", total=len(all_chars))
            
            for char in all_chars:
                # Create image
                img = Image.new('1', (GLYPH_WIDTH, GLYPH_HEIGHT), 1)
                draw = ImageDraw.Draw(img)
                
                # Draw character
                draw.text((0, -2), char, font=font, fill=0)
                
                # Check if character was actually drawn
                if img.getbbox() is None:
                    self.missing_glyphs.append(char)
                    missing_count += 1
                else:
                    # Save glyph
                    try:
                        char_code = ord(char)
                        safe_char = char if char not in ['/', '\\', '"', '*', '?', '<', '>', '|', ':'] else f"chr{char_code}"
                        filename = self.glyphs_dir / f"U+{char_code:04X}_{safe_char}.bmp"
                        img.save(str(filename), "BMP")
                        self.extracted_glyphs.append(char)
                        extracted_count += 1
                    except Exception as e:
                        console.print(f"[yellow]Failed to save {char}: {e}[/yellow]")
                        missing_count += 1
                        
                progress.advance(task)
                
        console.print(f"[green]✓ Extracted {extracted_count} glyphs[/green]")
        if missing_count > 0:
            console.print(f"[yellow]⚠ Missing {missing_count} glyphs (will create custom)[/yellow]")
            
        return True
        
    def step_2_create_custom_glyphs(self):
        """Create custom glyphs for missing characters"""
        console.print("\n[bold cyan]Step 2: Creating Custom Glyphs[/bold cyan]")
        
        if not self.missing_glyphs:
            console.print("[green]No missing glyphs to create![/green]")
            return True
            
        console.print(f"Creating {len(self.missing_glyphs)} custom glyphs...")
        
        # Create simple placeholder glyphs for missing characters
        for char in self.missing_glyphs:
            img = Image.new('1', (GLYPH_WIDTH, GLYPH_HEIGHT), 1)
            draw = ImageDraw.Draw(img)
            
            # Draw a simple box with character code
            draw.rectangle([0, 0, GLYPH_WIDTH-1, GLYPH_HEIGHT-1], outline=0)
            
            # For special keys, draw simple icons
            if char in REQUIRED_CHARS['special_keys']:
                self._draw_special_key_glyph(draw, char)
            else:
                # Draw character code in center
                draw.text((2, 2), "?", fill=0)
                
            try:
                char_code = ord(char)
                safe_char = f"chr{char_code}"
                filename = self.glyphs_dir / f"U+{char_code:04X}_{safe_char}_custom.bmp"
                img.save(str(filename), "BMP")
                console.print(f"  Created custom glyph for {char} (U+{char_code:04X})")
            except Exception as e:
                console.print(f"[red]Failed to create glyph for {char}: {e}[/red]")
                
        return True
        
    def _draw_special_key_glyph(self, draw, char):
        """Draw simple icons for special keys"""
        # Simple representations for special keys
        icons = {
            "⌫": [(6, 2, 2, 5), (2, 5, 6, 8)],  # Backspace arrow
            "⏎": [(2, 2, 6, 2), (2, 2, 2, 6), (1, 5, 2, 6)],  # Enter arrow
            "⇥": [(1, 5, 5, 5), (4, 4, 5, 5), (4, 5, 5, 6)],  # Tab arrow
            "↑": [(4, 2, 4, 8), (2, 4, 4, 2), (4, 2, 6, 4)],  # Up arrow
            "↓": [(4, 2, 4, 8), (2, 6, 4, 8), (4, 8, 6, 6)],  # Down arrow
            "←": [(2, 5, 7, 5), (2, 5, 4, 3), (2, 5, 4, 7)],  # Left arrow
            "→": [(1, 5, 6, 5), (4, 3, 6, 5), (4, 7, 6, 5)],  # Right arrow
        }
        
        if char in icons:
            for line in icons[char]:
                draw.line(line, fill=0)
        else:
            # Default: draw a small box
            draw.rectangle([2, 2, 5, 8], outline=0)
            
    def step_3_verify_glyphs(self):
        """Verify all required glyphs are present"""
        console.print("\n[bold cyan]Step 3: Verifying Glyph Coverage[/bold cyan]")
        
        # Count glyphs by category
        coverage = {}
        for category, chars in REQUIRED_CHARS.items():
            found = 0
            for char in chars:
                char_code = ord(char)
                pattern = f"U+{char_code:04X}_*.bmp"
                if list(self.glyphs_dir.glob(pattern)):
                    found += 1
            coverage[category] = (found, len(chars))
            
        # Display coverage table
        table = Table(title="Glyph Coverage Report")
        table.add_column("Category", style="cyan")
        table.add_column("Coverage", justify="right")
        table.add_column("Percentage", justify="right")
        
        total_found = 0
        total_required = 0
        
        for category, (found, required) in coverage.items():
            percentage = (found / required * 100) if required > 0 else 0
            color = "green" if percentage == 100 else "yellow" if percentage > 80 else "red"
            table.add_row(
                category.title(),
                f"{found}/{required}",
                f"[{color}]{percentage:.1f}%[/{color}]"
            )
            total_found += found
            total_required += required
            
        total_percentage = (total_found / total_required * 100) if total_required > 0 else 0
        color = "green" if total_percentage == 100 else "yellow" if total_percentage > 80 else "red"
        table.add_row(
            "[bold]Total[/bold]",
            f"[bold]{total_found}/{total_required}[/bold]",
            f"[bold {color}]{total_percentage:.1f}%[/bold {color}]"
        )
        
        console.print(table)
        return True
        
    def step_4_generate_sample_sheet(self):
        """Generate a sample sheet showing all glyphs"""
        console.print("\n[bold cyan]Step 4: Generating Sample Sheet[/bold cyan]")
        
        # Create a large image to show all glyphs
        cols = 16
        rows = 16
        sheet = Image.new('1', (cols * (GLYPH_WIDTH + 2), rows * (GLYPH_HEIGHT + 2)), 1)
        
        # Get all glyph files
        glyph_files = sorted(self.glyphs_dir.glob("U+*.bmp"))
        
        for i, glyph_file in enumerate(glyph_files[:cols*rows]):
            try:
                glyph = Image.open(glyph_file)
                x = (i % cols) * (GLYPH_WIDTH + 2) + 1
                y = (i // cols) * (GLYPH_HEIGHT + 2) + 1
                sheet.paste(glyph, (x, y))
            except Exception as e:
                console.print(f"[yellow]Failed to add {glyph_file.name}: {e}[/yellow]")
                
        output_file = self.glyphs_dir / "complete_sample_sheet.bmp"
        sheet.save(str(output_file), "BMP")
        console.print(f"[green]✓ Sample sheet saved to {output_file}[/green]")
        
        return True
        
    def run(self):
        """Run the complete processing pipeline"""
        console.print("[bold magenta]OLED Glyph Processing Pipeline[/bold magenta]")
        console.print("=" * 50)
        
        steps = [
            ("Extract Font Glyphs", self.step_1_extract_font_glyphs),
            ("Create Custom Glyphs", self.step_2_create_custom_glyphs),
            ("Verify Glyph Coverage", self.step_3_verify_glyphs),
            ("Generate Sample Sheet", self.step_4_generate_sample_sheet),
        ]
        
        for step_name, step_func in steps:
            if not step_func():
                console.print(f"[red]✗ {step_name} failed![/red]")
                return False
                
        console.print("\n[bold green]✓ Pipeline completed successfully![/bold green]")
        
        # Next steps
        console.print("\n[bold cyan]Next Steps:[/bold cyan]")
        console.print("1. Review generated glyphs in:", glyphs_dir)
        console.print("2. Edit any custom glyphs that need refinement")
        console.print("3. Run layout composition script (Task 4)")
        console.print("4. Generate header files (Task 5)")
        
        return True


@click.command()
@click.option('--step', type=int, help='Run only a specific step (1-4)')
@click.option('--verify-only', is_flag=True, help='Only verify existing glyphs')
def main(step, verify_only):
    """Master OLED Glyph Processing Script"""
    processor = OLEDGlyphProcessor()
    
    if verify_only:
        processor.step_3_verify_glyphs()
    elif step:
        steps = {
            1: processor.step_1_extract_font_glyphs,
            2: processor.step_2_create_custom_glyphs,
            3: processor.step_3_verify_glyphs,
            4: processor.step_4_generate_sample_sheet,
        }
        if step in steps:
            steps[step]()
        else:
            console.print(f"[red]Invalid step: {step}[/red]")
    else:
        processor.run()


if __name__ == "__main__":
    main()