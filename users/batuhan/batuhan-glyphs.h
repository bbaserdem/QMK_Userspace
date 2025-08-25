/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include "batuhan.h"

/* Dynamic glyph system for layout-aware unicode and string entry
 * Supports Dvorak, Turkish-F, and QWERTY layouts
 */

// Custom keycodes for glyphs (31 total)
enum glyph_keycodes {
    // Greek lowercase letters (16)
    G_ALPHA = KEYMAP_SAFE_RANGE,   // α
    G_BETA,                         // β
    G_GAMMA,                        // γ
    G_DELTA,                        // δ
    G_EPSLN,                        // ε
    G_ZETA,                         // ζ
    G_ETA,                          // η
    G_THETA,                        // θ
    G_LAMBD,                        // λ
    G_MU,                           // μ
    G_XI,                           // ξ
    G_PI,                           // π
    G_SIGMA,                        // σ
    G_PHI,                          // φ
    G_PSI,                          // ψ
    G_OMEGA,                        // ω
    
    // Greek uppercase letters (8 specific ones)
    G_CGAMM,                        // Γ
    G_CDELT,                        // Δ
    G_CXI,                          // Ξ
    G_CPI,                          // Π
    G_CSIGM,                        // Σ
    G_CPHI,                         // Φ
    G_CPSI,                         // Ψ
    G_COMEG,                        // Ω
    
    // Special symbols (4)
    G_ELLIP,                        // …
    G_PLNCK,                        // ℏ
    G_ANGST,                        // Å
    G_BTCN,                         // ₿
    
    // String macros (3)
    G_PGPK,                         // PGP key
    G_LENY,                         // ( ͡° ͜ʖ ͡°)
    G_TFLIP,                        // ┻━┻︵ \(°□°)/ ︵ ┻━┻
    
    GLYPH_SAFE_RANGE
};

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