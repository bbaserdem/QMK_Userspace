- there should be a script that launches the other scripts in sequence
- scripts should be in python

## 1. Extract LanaPixel Glyphs

- **1.1. Download and Prepare LanaPixel Font**
  - Download the font file (TTF/OTB/BDF).
  - Convert or rasterize at 8x11 pixels per glyph if necessary.[1]

- **1.2. Batch Export Glyphs**
  - Use a font processing tool (e.g., monobit, FontForge) to script extraction of each glyph to an individual 8x11 BMP file.
  - Name files by Unicode or intended keycode for easier mapping in later steps.

***

## 2. Create and Fill Missing/Custom Glyphs

- **2.1. Identify Required Non-Standard Glyphs**
  - List all special keys and symbols needed (dead keys, Insert, End, Home, PgUp, PgDn, etc.).
  - Check extracted glyphs for any missing ones.

- **2.2. Draw/Design Custom Glyphs**
  - Design missing glyphs as 8x11 BMP files using a pixel editor or programmatic method.

- **2.3. Integrate Custom Glyphs**
  - Add these files into the glyph directory, ensuring filename compatibility with automated processing scripts.

***

## 3. Glyph Arrangement and Parsing

- **3.1. Define Keyboard Layout Variants**
  - Map out layouts: Dvorak, QWERTY, Turkish-F ×
    - Layers: Normal, Shifted, AltGr, Shift+AltGr ×
    - Zones: Left half, Right half, Thumb cluster

- **3.2. Compose/Oversample Layout Images**
  - For each (layout × layer × zone), generate:
    - 32x53 pixel composite images for halves (glyphs with inter-column spacing).
    - 32x10 pixel images for thumb cluster.
  - Programmatically dither/detect empty rows and nudge glyphs as needed for optimal fit, or crop a minimal content row for “overflow” cases.

- **3.3. Generate Sprite Sheets or Individual Images**
  - Output images for each combination, with systematic naming for easy parsing.

***

## 4. Header File Generation (.h)

- **4.1. Parse Images into Progmem Arrays**
  - Convert each composite image into byte arrays suitable for storage in PROGMEM (for AVR/ARM, etc.).
  - Create a script to auto-generate C headers defining these arrays (one array per layout/layer/zone).

- **4.2. Optimize Array Representation**
  - Add macros or metadata (width, height, encoding order) as needed for fast lookup and rendering.

***

## 5. OLED Writer Program (Glyph Drawing)

- **5.1. Implement OLED Image Drawing Functions**
  - Write reusable C/C++ functions to blit an image array at a given pixel offset on screen.
  - Handle monochrome (SSD1306, SH1106) and color displays (where bits-per-pixel and byte-order may differ).

- **5.2. Test Rendering Engines**
  - Validate rendering for correct alignment, blank row detection, and scrolling/clipping handling.

***

## 6. Refactor Status/Settings Display

- **6.1. Audit Old Display Code**
  - Identify all areas showing settings: RGB, WPM, modifiers, top layer, encoder, etc.

- **6.2. Swap In Custom Font Rendering**
  - Replace built-in font calls with custom glyph drawing functions where appropriate.

- **6.3. Standardize Display Updates**
  - Modularize display code for easy adaptation to new layouts, custom graphics, or information hierarchy.

***

## 7. Display Adapter Templates

- **7.1. Write Display Configuration Templates**
  - For each hardware case (1×32x128, 2×32x128, 1×64x128, 2×64x128, 135×240 color TFT):
    - Automate layout calculations (pixel positions, splits).
    - Create template/dummy renderers to display the keyboard layout and states.

- **7.2. Dynamic Layout Selection**
  - Implement/prepare code to pick and draw appropriate layout at runtime/compile-time depending on display detected.

- **7.3. Add Support for Color TFT**
  - Segment color/font conversions and palette management if using colored fonts/images.

***

## 8. Automation and Batch Processing

- **8.1. Script End-to-End Workflow**
  - Automate font extraction, composition, image conversion, and header generation in a reproducible script or build process (Python preferred for image/font handling, Make/CMake for firmware build).

- **8.2. Document and Modularize**
  - Document scripts for maintainability.
  - Modularize so that adding/removing a layout/layer or changing a glyph source is easy.

***

### Implementation Notes

- Use a scripting language (Python recommended) for all font/image manipulations and auto-generation of headers.
- Consider a repo structure like:
  ```
  /glyphs/          # source bmps
  /composite/       # layout/zone images
  /headers/         # generated .h files
  /scripts/         # all automation
  ```
- Save time by using consistent, predictable file naming and directory layout throughout.
- For display driver adaptations, abstract the “draw from progmem array” call so you can plug in different hardware backends easily.
