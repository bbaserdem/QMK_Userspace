● Product Requirements Document: QMK YAML-Based Keymap Generation System

  Executive Summary

  Create a procedurally generated keymap workflow for QMK firmware that generates supplementary C files from a YAML
  configuration, working alongside existing hand-built files without replacing them.

  Core Requirement

  The generated files must be SUPPLEMENTARY, not REPLACEMENT files. The system should generate additional configuration
  files that can be reviewed and selectively integrated later, NOT immediately compile-ready code.

  Problem Statement

  The user has hand-crafted QMK configuration files that work but wants to explore moving configuration to a YAML-based
  single source of truth. The migration should be gradual and controlled, allowing review of generated output before
  integration.

  Critical Constraints

  1. DO NOT MODIFY EXISTING FILES

  - Never change hand-built files to make generated code compile
  - The only permitted changes are:
    - Include lines in .c and .h files (to reference generated files)
    - rules.mk modifications (to build generated files)
    - The generation script itself

  2. GENERATED FILES ARE SUPPLEMENTARY

  - Generated files should provide the SAME definitions as hand-built files
  - Compilation conflicts are EXPECTED and INTENTIONAL
  - The user will review and migrate selectively, not immediately

  3. COMPILATION IS NOT THE GOAL

  - Do NOT try to make the code compile
  - Do NOT fix "errors" by modifying definitions
  - Do NOT remove conflicting code
  - The user KNOWS it won't compile and that's the POINT

  Technical Specifications

  Input: YAML Configuration (keymap.yaml)

  Single source of truth containing:
  - Layer definitions with 6-column keyboard matrices
  - Custom keycodes (base codes, mod-taps, layer-taps, layer-switches)
  - Glyph/Unicode mappings (single and multi-codepoint)
  - RGB layer colors
  - Metadata

  Output: Generated C/H Files

  1. generated-layout.h

  Should contain:
  - Layer enum matching the original (same layer names and order)
  - Layout defines for each layer:
    - Full layers (_BASE, _DVOR, _GAME, _CHAR): Use L/R prefixes (e.g., BL1_5, BR1_5)
    - Half layers (_SYMB, _NUMB, _NAVI, _FUNC, _SETT, _MOUS): Use two-letter prefixes without L/R (e.g., SY1_5, NU1_5)
  - Music layer (_MUSI) special handling

  2. generated-keycodes.h

  Should contain:
  - Custom keycode enum with G_FIRST properly ordered
  - Mod-tap definitions (from YAML)
  - Layer-tap definitions (from YAML)
  - Layer-switch definitions (from YAML)
  - NO hardcoded values - everything from YAML

  3. generated-glyphs.c

  Should contain:
  - Unicode arrays for multi-codepoint glyphs
  - Glyph data table mapping keycodes to unicode/strings
  - NO typedef (uses existing from batuhan-glyphs.h)
  - Uses G_FIRST for indexing

  4. generated-colors.h

  Should contain:
  - RGB color definitions for each layer
  - Both RGB_ and HSV_ versions
  - Read from YAML rgb_color field

  Implementation Details

  YAML Structure Requirements

  - 6 columns per keyboard row (no encoder positions in matrix)
  - Half layers only define their active side
  - No empty matrices for inactive sides
  - All configuration data in YAML, no hardcoding

  Generation Script Behavior

  1. Read ALL data from YAML
  2. Generate defines that MATCH existing patterns
  3. Do NOT try to avoid conflicts
  4. Do NOT add extra features (no wrappers, masks, KC_TRNS/KC_NO patterns)
  5. Do NOT hardcode configuration values

  Prefix Generation Rules

  - Full layers: First letter after underscore (e.g., _BASE → _B)
  - Half layers: First two letters after underscore (e.g., _SYMB → _SY)
  - This should be computed, not hardcoded

  Expected Outcome

  The generated files will create compilation conflicts with existing hand-built files. This is INTENTIONAL. The user
  will:
  1. Review the generated output
  2. Compare with hand-built files
  3. Selectively migrate to generated definitions
  4. Eventually remove hand-built definitions once satisfied

  What NOT to Do

  - DO NOT try to make it compile
  - DO NOT modify hand-built files to fix conflicts
  - DO NOT remove or comment out conflicting definitions
  - DO NOT change keycode names to avoid conflicts
  - DO NOT act on compilation errors

  Success Criteria

  1. Generated files correctly parse YAML structure
  2. Generated definitions match the pattern of hand-built files
  3. All data comes from YAML, not hardcoded
  4. Conflicts exist (proving the files are truly supplementary)
  5. User can review and choose how to migrate

  User Intent

  The user is an experienced developer who:
  - Knows the code won't compile with both files
  - Wants to review generated output before using it
  - Will handle the migration themselves
  - Does NOT want automatic "fixes"
  - Does NOT want the assistant to make it compile
