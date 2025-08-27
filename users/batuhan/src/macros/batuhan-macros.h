/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
// clang-format off
#pragma once
#include "../../batuhan.h"

/* Dynamic glyph system for layout-aware unicode and string entry
 * Supports Dvorak, Turkish-F, and QWERTY layouts
 */

// Custom keycodes for glyphs are now defined in generated-keycodes.h
// The enum glyph_keycodes has been moved to generated-keycodes.h
// GLYPH_SAFE_RANGE is also defined there

// Glyph data structure
typedef struct {
    uint32_t unicode;              // Unicode codepoint (0 if array or string)
    const uint32_t* unicode_array; // Array of unicode codepoints (NULL if single or string)
    uint8_t array_len;             // Length of unicode array
    const char* string;            // String macro (NULL if unicode)
} glyph_data_t;

// Process function for glyphs
bool process_record_glyph(uint16_t keycode, keyrecord_t *record);

// Send a unicode character based on current layout
void send_unicode_glyph(uint32_t unicode_point);
void send_string_with_layout(const char* str);

// External glyph table defined in batuhan-glyphs.c
extern const glyph_data_t glyph_table[];
extern const size_t glyph_table_size;
