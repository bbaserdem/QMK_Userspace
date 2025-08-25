/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma GCC optimize("Os")
#include "batuhan.h"
#include "batuhan-glyphs.h"
#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
#endif

/* Dynamic glyph system implementation
 * Handles unicode and string entry based on current software layout
 */

// Unicode arrays for complex glyphs
static const uint32_t lenny_unicode[] = {
    0x0028, // (
    0x0020, // space
    0x0361, // ͡ combining double inverted breve
    0x00B0, // °
    0x0020, // space
    0x035C, // ͜ combining double breve below
    0x0296, // ʖ
    0x0020, // space
    0x0361, // ͡ combining double inverted breve
    0x00B0, // °
    0x0029, // )
};

static const uint32_t tflip_unicode[] = {
    0x253B, // ┻
    0x2501, // ━
    0x253B, // ┻
    0xFE35, // ︵
    0x0020, // space
    0x005C, // backslash
    0x0028, // (
    0x00B0, // °
    0x25A1, // □
    0x00B0, // °
    0x0029, // )
    0x002F, // /
    0x0020, // space
    0xFE35, // ︵
    0x0020, // space
    0x253B, // ┻
    0x2501, // ━
    0x253B, // ┻
};

// Glyph data table - maps keycodes to unicode/strings
static const glyph_data_t glyph_table[] = {
    // Greek lowercase letters
    [G_ALPHA - KEYMAP_SAFE_RANGE] = {0x03B1, NULL, 0, NULL},    // α
    [G_BETA - KEYMAP_SAFE_RANGE]  = {0x03B2, NULL, 0, NULL},    // β
    [G_GAMMA - KEYMAP_SAFE_RANGE] = {0x03B3, NULL, 0, NULL},    // γ
    [G_DELTA - KEYMAP_SAFE_RANGE] = {0x03B4, NULL, 0, NULL},    // δ
    [G_EPSLN - KEYMAP_SAFE_RANGE] = {0x03B5, NULL, 0, NULL},    // ε
    [G_ZETA - KEYMAP_SAFE_RANGE]  = {0x03B6, NULL, 0, NULL},    // ζ
    [G_ETA - KEYMAP_SAFE_RANGE]   = {0x03B7, NULL, 0, NULL},    // η
    [G_THETA - KEYMAP_SAFE_RANGE] = {0x03B8, NULL, 0, NULL},    // θ
    [G_LAMBD - KEYMAP_SAFE_RANGE] = {0x03BB, NULL, 0, NULL},    // λ
    [G_MU - KEYMAP_SAFE_RANGE]    = {0x03BC, NULL, 0, NULL},    // μ
    [G_XI - KEYMAP_SAFE_RANGE]    = {0x03BE, NULL, 0, NULL},    // ξ
    [G_PI - KEYMAP_SAFE_RANGE]    = {0x03C0, NULL, 0, NULL},    // π
    [G_SIGMA - KEYMAP_SAFE_RANGE] = {0x03C3, NULL, 0, NULL},    // σ
    [G_PHI - KEYMAP_SAFE_RANGE]   = {0x03C6, NULL, 0, NULL},    // φ
    [G_PSI - KEYMAP_SAFE_RANGE]   = {0x03C8, NULL, 0, NULL},    // ψ
    [G_OMEGA - KEYMAP_SAFE_RANGE] = {0x03C9, NULL, 0, NULL},    // ω
    
    // Greek uppercase letters (specific ones)
    [G_CGAMM - KEYMAP_SAFE_RANGE] = {0x0393, NULL, 0, NULL},    // Γ
    [G_CDELT - KEYMAP_SAFE_RANGE] = {0x0394, NULL, 0, NULL},    // Δ
    [G_CXI - KEYMAP_SAFE_RANGE]   = {0x039E, NULL, 0, NULL},    // Ξ
    [G_CPI - KEYMAP_SAFE_RANGE]   = {0x03A0, NULL, 0, NULL},    // Π
    [G_CSIGM - KEYMAP_SAFE_RANGE] = {0x03A3, NULL, 0, NULL},    // Σ
    [G_CPHI - KEYMAP_SAFE_RANGE]  = {0x03A6, NULL, 0, NULL},    // Φ
    [G_CPSI - KEYMAP_SAFE_RANGE]  = {0x03A8, NULL, 0, NULL},    // Ψ
    [G_COMEG - KEYMAP_SAFE_RANGE] = {0x03A9, NULL, 0, NULL},    // Ω
    
    // Special symbols
    [G_ELLIP - KEYMAP_SAFE_RANGE] = {0x2026, NULL, 0, NULL},    // …
    [G_PLNCK - KEYMAP_SAFE_RANGE] = {0x210F, NULL, 0, NULL},    // ℏ
    [G_ANGST - KEYMAP_SAFE_RANGE] = {0x212B, NULL, 0, NULL},    // Å
    [G_BTCN - KEYMAP_SAFE_RANGE]  = {0x20BF, NULL, 0, NULL},    // ₿
    
    // String macros
    [G_PGPK - KEYMAP_SAFE_RANGE]  = {0, NULL, 0, "0B7151C823559DD8A7A04CE36426139E2F4C6CCE"},
    [G_LENY - KEYMAP_SAFE_RANGE]  = {0, lenny_unicode, sizeof(lenny_unicode)/sizeof(uint32_t), NULL},
    [G_TFLIP - KEYMAP_SAFE_RANGE] = {0, tflip_unicode, sizeof(tflip_unicode)/sizeof(uint32_t), NULL},
};

// ASCII character to keycode translation tables
// Maps ASCII characters to the physical keys needed for each layout
// Index by character - 'a' (so 'a' = 0, 'b' = 1, etc.)

// Number keycodes (same across all layouts)
static const uint8_t number_to_keycode[10] = {
    ['0' - '0'] = KC_0,
    ['1' - '0'] = KC_1,
    ['2' - '0'] = KC_2,
    ['3' - '0'] = KC_3,
    ['4' - '0'] = KC_4,
    ['5' - '0'] = KC_5,
    ['6' - '0'] = KC_6,
    ['7' - '0'] = KC_7,
    ['8' - '0'] = KC_8,
    ['9' - '0'] = KC_9,
};

// For QWERTY layout (direct mapping, but explicit to avoid assumptions)
static const uint8_t ascii_to_keycode_qwerty[26] = {
    ['a' - 'a'] = KC_A,
    ['b' - 'a'] = KC_B,
    ['c' - 'a'] = KC_C,
    ['d' - 'a'] = KC_D,
    ['e' - 'a'] = KC_E,
    ['f' - 'a'] = KC_F,
    ['g' - 'a'] = KC_G,
    ['h' - 'a'] = KC_H,
    ['i' - 'a'] = KC_I,
    ['j' - 'a'] = KC_J,
    ['k' - 'a'] = KC_K,
    ['l' - 'a'] = KC_L,
    ['m' - 'a'] = KC_M,
    ['n' - 'a'] = KC_N,
    ['o' - 'a'] = KC_O,
    ['p' - 'a'] = KC_P,
    ['q' - 'a'] = KC_Q,
    ['r' - 'a'] = KC_R,
    ['s' - 'a'] = KC_S,
    ['t' - 'a'] = KC_T,
    ['u' - 'a'] = KC_U,
    ['v' - 'a'] = KC_V,
    ['w' - 'a'] = KC_W,
    ['x' - 'a'] = KC_X,
    ['y' - 'a'] = KC_Y,
    ['z' - 'a'] = KC_Z,
};

// For Dvorak layout in OS (QMK sends QWERTY positions)
// When OS expects Dvorak, we need to send the QWERTY position that produces the desired character
static const uint8_t ascii_to_keycode_dvorak[26] = {
    ['a' - 'a'] = KC_A,    // a -> a
    ['b' - 'a'] = KC_N,    // b -> n
    ['c' - 'a'] = KC_I,    // c -> i
    ['d' - 'a'] = KC_E,    // d -> e
    ['e' - 'a'] = KC_D,    // e -> d
    ['f' - 'a'] = KC_Y,    // f -> y
    ['g' - 'a'] = KC_U,    // g -> u
    ['h' - 'a'] = KC_J,    // h -> j
    ['i' - 'a'] = KC_G,    // i -> g
    ['j' - 'a'] = KC_C,    // j -> c
    ['k' - 'a'] = KC_V,    // k -> v
    ['l' - 'a'] = KC_P,    // l -> p
    ['m' - 'a'] = KC_M,    // m -> m
    ['n' - 'a'] = KC_L,    // n -> l
    ['o' - 'a'] = KC_S,    // o -> s
    ['p' - 'a'] = KC_R,    // p -> r
    ['q' - 'a'] = KC_X,    // q -> x
    ['r' - 'a'] = KC_O,    // r -> o
    ['s' - 'a'] = KC_SCLN, // s -> ;
    ['t' - 'a'] = KC_K,    // t -> k
    ['u' - 'a'] = KC_G,    // u -> g
    ['v' - 'a'] = KC_DOT,  // v -> .
    ['w' - 'a'] = KC_COMM, // w -> ,
    ['x' - 'a'] = KC_B,    // x -> b
    ['y' - 'a'] = KC_F,    // y -> f
    ['z' - 'a'] = KC_SLSH, // z -> /
};

// For Turkish-F layout in OS
static const uint8_t ascii_to_keycode_turkishf[26] = {
    ['a' - 'a'] = KC_U,    // a -> u (Turkish-F)
    ['b' - 'a'] = KC_H,    // b -> h
    ['c' - 'a'] = KC_J,    // c -> j
    ['d' - 'a'] = KC_K,    // d -> k
    ['e' - 'a'] = KC_I,    // e -> i
    ['f' - 'a'] = KC_F,    // f -> f
    ['g' - 'a'] = KC_T,    // g -> t
    ['h' - 'a'] = KC_P,    // h -> p
    ['i' - 'a'] = KC_R,    // i -> r (ı in Turkish-F)
    ['j' - 'a'] = KC_MINS, // j -> - (ö in Turkish-F)
    ['k' - 'a'] = KC_N,    // k -> n
    ['l' - 'a'] = KC_S,    // l -> s
    ['m' - 'a'] = KC_SLSH, // m -> /
    ['n' - 'a'] = KC_M,    // n -> m
    ['o' - 'a'] = KC_E,    // o -> e
    ['p' - 'a'] = KC_COMM, // p -> ,
    ['q' - 'a'] = KC_X,    // q -> x
    ['r' - 'a'] = KC_O,    // r -> o
    ['s' - 'a'] = KC_L,    // s -> l
    ['t' - 'a'] = KC_G,    // t -> g
    ['u' - 'a'] = KC_A,    // u -> a
    ['v' - 'a'] = KC_DOT,  // v -> .
    ['w' - 'a'] = KC_V,    // w -> v
    ['x' - 'a'] = KC_SCLN, // x -> ; (ş in Turkish-F)
    ['y' - 'a'] = KC_D,    // y -> d
    ['z' - 'a'] = KC_Z,    // z -> z
};

// Helper to get keycode for ASCII character
static uint8_t get_ascii_keycode(char c, uint8_t layout) {
    // Numbers are the same across layouts
    if (c >= '0' && c <= '9') {
        return number_to_keycode[c - '0'];
    }
    
    // Lowercase letters need translation
    if (c >= 'a' && c <= 'z') {
        switch (layout) {
            case LAYOUT_DVORAK:
                return ascii_to_keycode_dvorak[c - 'a'];
            case LAYOUT_TURKISHF:
                return ascii_to_keycode_turkishf[c - 'a'];
            case LAYOUT_QWERTY:
            default:
                return ascii_to_keycode_qwerty[c - 'a'];
        }
    }
    
    // Uppercase letters (same keycodes as lowercase, shift is handled separately)
    if (c >= 'A' && c <= 'Z') {
        switch (layout) {
            case LAYOUT_DVORAK:
                return ascii_to_keycode_dvorak[c - 'A'];
            case LAYOUT_TURKISHF:
                return ascii_to_keycode_turkishf[c - 'A'];
            case LAYOUT_QWERTY:
            default:
                return ascii_to_keycode_qwerty[c - 'A'];
        }
    }
    
    // Other characters would need their own mappings
    return KC_NO;
}

// Send unicode based on OS and layout
void send_unicode_glyph(uint32_t unicode_point) {
    if (unicode_point == 0) return;
    
    uint8_t layout = userspace_config.bits.layout;
    
    // Get the detected OS
#ifdef OS_DETECTION_ENABLE
    os_variant_t os = detected_host_os();
#else
    // Default to Linux if OS detection is disabled
    os_variant_t os = OS_LINUX;
#endif
    
    // Different unicode entry methods per OS
    switch (os) {
        case OS_LINUX:
        case OS_UNSURE:
            // Linux: Ctrl+Shift+U, then hex code, then space/enter
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(get_ascii_keycode('u', layout));
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            
            // Send hex digits
            for (int i = 3; i >= 0; i--) {
                uint8_t digit = (unicode_point >> (i * 4)) & 0xF;
                if (digit != 0 || i == 0) {  // At least one zero
                    char hex_char = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
                    tap_code(get_ascii_keycode(hex_char, layout));
                }
            }
            
            // Confirm with space
            tap_code(KC_SPC);
            break;
            
        case OS_WINDOWS:
            // Windows: Alt+Numpad Plus, then hex code (on numpad)
            // Note: This requires Registry edit to enable hex numpad
            // Alternative: Use WinCompose or similar
            register_code(KC_LALT);
            tap_code(KC_KP_PLUS);
            
            // Send hex digits using numpad
            for (int i = 3; i >= 0; i--) {
                uint8_t digit = (unicode_point >> (i * 4)) & 0xF;
                if (digit != 0 || i == 0) {
                    if (digit < 10) {
                        tap_code(KC_KP_0 + digit);
                    } else {
                        // For A-F, we need to use the regular keys with Alt held
                        char hex_char = 'a' + (digit - 10);
                        tap_code(get_ascii_keycode(hex_char, layout));
                    }
                }
            }
            
            unregister_code(KC_LALT);
            break;
            
        case OS_MACOS:
        case OS_IOS:
            // macOS: Option+hex code (requires Unicode Hex Input keyboard)
            // User must enable Unicode Hex Input in System Preferences
            register_code(KC_LALT);  // Option key
            
            // Send hex digits
            for (int i = 3; i >= 0; i--) {
                uint8_t digit = (unicode_point >> (i * 4)) & 0xF;
                // macOS needs all 4 digits
                char hex_char = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
                tap_code(get_ascii_keycode(hex_char, layout));
            }
            
            unregister_code(KC_LALT);
            break;
    }
}

// Send PGP key (pure hex string)
void send_pgp_key(void) {
    // PGP key is pure hex characters
    const char* pgp = "0B7151C823559DD8A7A04CE36426139E2F4C6CCE";
    uint8_t layout = userspace_config.bits.layout;
    
    while (*pgp) {
        // For uppercase hex letters in PGP key, hold shift
        if (*pgp >= 'A' && *pgp <= 'F') {
            register_code(KC_LSFT);
            tap_code(get_ascii_keycode(*pgp, layout));
            unregister_code(KC_LSFT);
        } else {
            // Numbers and lowercase (though PGP key is all uppercase)
            tap_code(get_ascii_keycode(*pgp, layout));
        }
        pgp++;
    }
}

// Process glyph keycodes
bool process_record_glyph(uint16_t keycode, keyrecord_t *record) {
    // Only handle our keycode range
    if (keycode < KEYMAP_SAFE_RANGE || keycode >= GLYPH_SAFE_RANGE) {
        return true;
    }
    
    // Only process on key press
    if (!record->event.pressed) {
        return false;
    }
    
    // Get glyph data
    uint16_t index = keycode - KEYMAP_SAFE_RANGE;
    if (index >= sizeof(glyph_table) / sizeof(glyph_table[0])) {
        return true;  // Invalid index
    }
    
    // Handle PGP key specially
    if (keycode == G_PGPK) {
        send_pgp_key();
        return false;
    }
    
    const glyph_data_t* glyph = &glyph_table[index];
    
    // Check what type of glyph it is
    if (glyph->string != NULL) {
        // String macro (only PGP key uses this now)
        // PGP key should have been handled above, but just in case
        send_string(glyph->string);
    } else if (glyph->unicode_array != NULL) {
        // Unicode array (Lenny, table flip)
        for (uint8_t i = 0; i < glyph->array_len; i++) {
            send_unicode_glyph(glyph->unicode_array[i]);
        }
    } else if (glyph->unicode != 0) {
        // Single unicode character
        send_unicode_glyph(glyph->unicode);
    }
    
    return false;
}