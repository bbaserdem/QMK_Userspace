/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma GCC optimize("Os")
#include "batuhan.h"
#include "batuhan-glyphs.h"
#include "keymap_dvorak.h"
#include "keymap_turkish_f.h"
#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
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
    [G_ALPHA - KEYMAP_SAFE_RANGE] = {0x03B1, NULL, 0, NULL}, // α
    [G_BETA - KEYMAP_SAFE_RANGE]  = {0x03B2, NULL, 0, NULL}, // β
    [G_GAMMA - KEYMAP_SAFE_RANGE] = {0x03B3, NULL, 0, NULL}, // γ
    [G_DELTA - KEYMAP_SAFE_RANGE] = {0x03B4, NULL, 0, NULL}, // δ
    [G_EPSLN - KEYMAP_SAFE_RANGE] = {0x03B5, NULL, 0, NULL}, // ε
    [G_ZETA - KEYMAP_SAFE_RANGE]  = {0x03B6, NULL, 0, NULL}, // ζ
    [G_ETA - KEYMAP_SAFE_RANGE]   = {0x03B7, NULL, 0, NULL}, // η
    [G_THETA - KEYMAP_SAFE_RANGE] = {0x03B8, NULL, 0, NULL}, // θ
    [G_LAMBD - KEYMAP_SAFE_RANGE] = {0x03BB, NULL, 0, NULL}, // λ
    [G_MU - KEYMAP_SAFE_RANGE]    = {0x03BC, NULL, 0, NULL}, // μ
    [G_XI - KEYMAP_SAFE_RANGE]    = {0x03BE, NULL, 0, NULL}, // ξ
    [G_PI - KEYMAP_SAFE_RANGE]    = {0x03C0, NULL, 0, NULL}, // π
    [G_SIGMA - KEYMAP_SAFE_RANGE] = {0x03C3, NULL, 0, NULL}, // σ
    [G_PHI - KEYMAP_SAFE_RANGE]   = {0x03C6, NULL, 0, NULL}, // φ
    [G_PSI - KEYMAP_SAFE_RANGE]   = {0x03C8, NULL, 0, NULL}, // ψ
    [G_OMEGA - KEYMAP_SAFE_RANGE] = {0x03C9, NULL, 0, NULL}, // ω

    // Greek uppercase letters (specific ones)
    [G_CGAMM - KEYMAP_SAFE_RANGE] = {0x0393, NULL, 0, NULL}, // Γ
    [G_CDELT - KEYMAP_SAFE_RANGE] = {0x0394, NULL, 0, NULL}, // Δ
    [G_CXI - KEYMAP_SAFE_RANGE]   = {0x039E, NULL, 0, NULL}, // Ξ
    [G_CPI - KEYMAP_SAFE_RANGE]   = {0x03A0, NULL, 0, NULL}, // Π
    [G_CSIGM - KEYMAP_SAFE_RANGE] = {0x03A3, NULL, 0, NULL}, // Σ
    [G_CPHI - KEYMAP_SAFE_RANGE]  = {0x03A6, NULL, 0, NULL}, // Φ
    [G_CPSI - KEYMAP_SAFE_RANGE]  = {0x03A8, NULL, 0, NULL}, // Ψ
    [G_COMEG - KEYMAP_SAFE_RANGE] = {0x03A9, NULL, 0, NULL}, // Ω

    // Special symbols
    [G_ELLIP - KEYMAP_SAFE_RANGE] = {0x2026, NULL, 0, NULL}, // …
    [G_PLNCK - KEYMAP_SAFE_RANGE] = {0x210F, NULL, 0, NULL}, // ℏ
    [G_ANGST - KEYMAP_SAFE_RANGE] = {0x212B, NULL, 0, NULL}, // Å
    [G_BTCN - KEYMAP_SAFE_RANGE]  = {0x20BF, NULL, 0, NULL}, // ₿

    // String macros
    [G_PGPK - KEYMAP_SAFE_RANGE]  = {0, NULL, 0, "0B7151C823559DD8A7A04CE36426139E2F4C6CCE"},
    [G_LENY - KEYMAP_SAFE_RANGE]  = {0, lenny_unicode, sizeof(lenny_unicode) / sizeof(uint32_t), NULL},
    [G_TFLIP - KEYMAP_SAFE_RANGE] = {0, tflip_unicode, sizeof(tflip_unicode) / sizeof(uint32_t), NULL},
};

// ASCII character to keycode translation tables
// Maps ASCII characters to the physical keys needed for each layout
// Index by character - 'a' (so 'a' = 0, 'b' = 1, etc.)

// Number keycodes (same across all layouts)
static const uint8_t number_to_keycode[10] = {
    ['0' - '0'] = KC_0, ['1' - '0'] = KC_1, ['2' - '0'] = KC_2, ['3' - '0'] = KC_3, ['4' - '0'] = KC_4, ['5' - '0'] = KC_5, ['6' - '0'] = KC_6, ['7' - '0'] = KC_7, ['8' - '0'] = KC_8, ['9' - '0'] = KC_9,
};

// Use QMK's keymap definitions for proper character mapping
// These keycodes send the correct physical key to produce the desired character
// when the OS is set to the corresponding layout

// For QWERTY - direct mapping
static const uint16_t ascii_to_keycode_qwerty[26] = {
    ['a' - 'a'] = KC_A, ['b' - 'a'] = KC_B, ['c' - 'a'] = KC_C, ['d' - 'a'] = KC_D, ['e' - 'a'] = KC_E, ['f' - 'a'] = KC_F, ['g' - 'a'] = KC_G, ['h' - 'a'] = KC_H, ['i' - 'a'] = KC_I, ['j' - 'a'] = KC_J, ['k' - 'a'] = KC_K, ['l' - 'a'] = KC_L, ['m' - 'a'] = KC_M, ['n' - 'a'] = KC_N, ['o' - 'a'] = KC_O, ['p' - 'a'] = KC_P, ['q' - 'a'] = KC_Q, ['r' - 'a'] = KC_R, ['s' - 'a'] = KC_S, ['t' - 'a'] = KC_T, ['u' - 'a'] = KC_U, ['v' - 'a'] = KC_V, ['w' - 'a'] = KC_W, ['x' - 'a'] = KC_X, ['y' - 'a'] = KC_Y, ['z' - 'a'] = KC_Z,
};

// For Dvorak - use QMK's Dvorak keycodes
static const uint16_t ascii_to_keycode_dvorak[26] = {
    ['a' - 'a'] = DV_A, ['b' - 'a'] = DV_B, ['c' - 'a'] = DV_C, ['d' - 'a'] = DV_D, ['e' - 'a'] = DV_E, ['f' - 'a'] = DV_F, ['g' - 'a'] = DV_G, ['h' - 'a'] = DV_H, ['i' - 'a'] = DV_I, ['j' - 'a'] = DV_J, ['k' - 'a'] = DV_K, ['l' - 'a'] = DV_L, ['m' - 'a'] = DV_M, ['n' - 'a'] = DV_N, ['o' - 'a'] = DV_O, ['p' - 'a'] = DV_P, ['q' - 'a'] = DV_Q, ['r' - 'a'] = DV_R, ['s' - 'a'] = DV_S, ['t' - 'a'] = DV_T, ['u' - 'a'] = DV_U, ['v' - 'a'] = DV_V, ['w' - 'a'] = DV_W, ['x' - 'a'] = DV_X, ['y' - 'a'] = DV_Y, ['z' - 'a'] = DV_Z,
};

// For Turkish-F - use QMK's Turkish-F keycodes
static const uint16_t ascii_to_keycode_turkishf[26] = {
    ['a' - 'a'] = TR_A, ['b' - 'a'] = TR_B, ['c' - 'a'] = TR_C, ['d' - 'a'] = TR_D, ['e' - 'a'] = TR_E, ['f' - 'a'] = TR_F, ['g' - 'a'] = TR_G, ['h' - 'a'] = TR_H, ['i' - 'a'] = TR_IDOT, ['j' - 'a'] = TR_J, ['k' - 'a'] = TR_K, ['l' - 'a'] = TR_L, ['m' - 'a'] = TR_M, ['n' - 'a'] = TR_N, ['o' - 'a'] = TR_O, ['p' - 'a'] = TR_P, ['q' - 'a'] = TR_Q, ['r' - 'a'] = TR_R, ['s' - 'a'] = TR_S, ['t' - 'a'] = TR_T, ['u' - 'a'] = TR_U, ['v' - 'a'] = TR_V, ['w' - 'a'] = TR_W, ['x' - 'a'] = TR_X, ['y' - 'a'] = TR_Y, ['z' - 'a'] = TR_Z,
};

// Helper to get keycode for ASCII character
static uint16_t get_ascii_keycode(char c, uint8_t layout) {
    // Numbers - Dvorak has special number keycodes
    if (c >= '0' && c <= '9') {
        if (layout == LAYOUT_DVORAK) {
            // Use Dvorak number keycodes
            switch (c) {
                case '0':
                    return DV_0;
                case '1':
                    return DV_1;
                case '2':
                    return DV_2;
                case '3':
                    return DV_3;
                case '4':
                    return DV_4;
                case '5':
                    return DV_5;
                case '6':
                    return DV_6;
                case '7':
                    return DV_7;
                case '8':
                    return DV_8;
                case '9':
                    return DV_9;
            }
        } else if (layout == LAYOUT_TURKISHF) {
            // Turkish-F numbers
            switch (c) {
                case '0':
                    return TR_0;
                case '1':
                    return TR_1;
                case '2':
                    return TR_2;
                case '3':
                    return TR_3;
                case '4':
                    return TR_4;
                case '5':
                    return TR_5;
                case '6':
                    return TR_6;
                case '7':
                    return TR_7;
                case '8':
                    return TR_8;
                case '9':
                    return TR_9;
            }
        } else {
            // QWERTY numbers
            return number_to_keycode[c - '0'];
        }
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

            // Send hex digits (only significant digits for Linux)
            bool started = false;
            for (int i = 3; i >= 0; i--) {
                uint8_t digit = (unicode_point >> (i * 4)) & 0xF;
                if (digit != 0 || started || i == 0) { // Start from first non-zero or send at least one zero
                    started       = true;
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
            register_code(KC_LALT); // Option key

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

// Send string with proper layout support
void send_string_with_layout(const char* str) {
    uint8_t layout = userspace_config.bits.layout;

    while (*str) {
        char c = *str;

        // Handle uppercase letters
        if (c >= 'A' && c <= 'Z') {
            register_code(KC_LSFT);
            tap_code(get_ascii_keycode(c, layout));
            unregister_code(KC_LSFT);
        }
        // Handle lowercase letters and numbers
        else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            tap_code(get_ascii_keycode(c, layout));
        }
        // Handle other characters if needed
        str++;
    }
}

// Process glyph keycodes
bool process_record_glyph(uint16_t keycode, keyrecord_t* record) {
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
        return true; // Invalid index
    }

    // No special handling needed - everything goes through glyph table

    const glyph_data_t* glyph = &glyph_table[index];

    // Check what type of glyph it is
    if (glyph->string != NULL) {
        // String macro (PGP key)
        send_string_with_layout(glyph->string);
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
