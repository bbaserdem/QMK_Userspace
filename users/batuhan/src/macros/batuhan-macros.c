/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
// clang-format off
#pragma GCC optimize("Os")
#include "../../batuhan.h"
#include "batuhan-macros.h"
#include "keymap_dvorak.h"
#include "keymap_turkish_f.h"
#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
#endif

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

// Use QMK's keymap definitions for proper character mapping
// These keycodes send the correct physical key to produce the desired character
// when the OS is set to the corresponding layout

// For QWERTY - direct mapping
static const uint16_t ascii_to_keycode_qwerty[26] = {
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

// For Dvorak - use QMK's Dvorak keycodes
static const uint16_t ascii_to_keycode_dvorak[26] = {
    ['a' - 'a'] = DV_A,
    ['b' - 'a'] = DV_B,
    ['c' - 'a'] = DV_C,
    ['d' - 'a'] = DV_D,
    ['e' - 'a'] = DV_E,
    ['f' - 'a'] = DV_F,
    ['g' - 'a'] = DV_G,
    ['h' - 'a'] = DV_H,
    ['i' - 'a'] = DV_I,
    ['j' - 'a'] = DV_J,
    ['k' - 'a'] = DV_K,
    ['l' - 'a'] = DV_L,
    ['m' - 'a'] = DV_M,
    ['n' - 'a'] = DV_N,
    ['o' - 'a'] = DV_O,
    ['p' - 'a'] = DV_P,
    ['q' - 'a'] = DV_Q,
    ['r' - 'a'] = DV_R,
    ['s' - 'a'] = DV_S,
    ['t' - 'a'] = DV_T,
    ['u' - 'a'] = DV_U,
    ['v' - 'a'] = DV_V,
    ['w' - 'a'] = DV_W,
    ['x' - 'a'] = DV_X,
    ['y' - 'a'] = DV_Y,
    ['z' - 'a'] = DV_Z,
};

// For Turkish-F - use QMK's Turkish-F keycodes
static const uint16_t ascii_to_keycode_turkishf[26] = {
    ['a' - 'a'] = TR_A,
    ['b' - 'a'] = TR_B,
    ['c' - 'a'] = TR_C,
    ['d' - 'a'] = TR_D,
    ['e' - 'a'] = TR_E,
    ['f' - 'a'] = TR_F,
    ['g' - 'a'] = TR_G,
    ['h' - 'a'] = TR_H,
    ['i' - 'a'] = TR_IDOT,
    ['j' - 'a'] = TR_J,
    ['k' - 'a'] = TR_K,
    ['l' - 'a'] = TR_L,
    ['m' - 'a'] = TR_M,
    ['n' - 'a'] = TR_N,
    ['o' - 'a'] = TR_O,
    ['p' - 'a'] = TR_P,
    ['q' - 'a'] = TR_Q,
    ['r' - 'a'] = TR_R,
    ['s' - 'a'] = TR_S,
    ['t' - 'a'] = TR_T,
    ['u' - 'a'] = TR_U,
    ['v' - 'a'] = TR_V,
    ['w' - 'a'] = TR_W,
    ['x' - 'a'] = TR_X,
    ['y' - 'a'] = TR_Y,
    ['z' - 'a'] = TR_Z,
};

// Helper to get keycode for ASCII character
static uint16_t get_ascii_keycode(char c, uint8_t layout) {
    // Numbers - Dvorak has special number keycodes
    if (c >= '0' && c <= '9') {
        if (layout == LAYOUT_DVORAK) {
            // Use Dvorak number keycodes
            switch (c) {
                case '0': return DV_0;
                case '1': return DV_1;
                case '2': return DV_2;
                case '3': return DV_3;
                case '4': return DV_4;
                case '5': return DV_5;
                case '6': return DV_6;
                case '7': return DV_7;
                case '8': return DV_8;
                case '9': return DV_9;
            }
        } else if (layout == LAYOUT_TURKISHF) {
            // Turkish-F numbers
            switch (c) {
                case '0': return TR_0;
                case '1': return TR_1;
                case '2': return TR_2;
                case '3': return TR_3;
                case '4': return TR_4;
                case '5': return TR_5;
                case '6': return TR_6;
                case '7': return TR_7;
                case '8': return TR_8;
                case '9': return TR_9;
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
            tap_code16_delay(get_ascii_keycode('u', layout), 10);  // Fast tap
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);

            // Send hex digits (only significant digits for Linux)
            bool started = false;
            for (int i = 3; i >= 0; i--) {
                uint8_t digit = (unicode_point >> (i * 4)) & 0xF;
                if (digit != 0 || started || i == 0) {  // Start from first non-zero or send at least one zero
                    started = true;
                    char hex_char = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
                    tap_code16_delay(get_ascii_keycode(hex_char, layout), 10);  // Fast tap
                }
            }

            // Confirm with space
            tap_code16_delay(KC_SPC, 10);  // Fast tap
            break;

        case OS_WINDOWS:
            // Windows: Alt+Numpad Plus, then hex code (on numpad)
            // Note: This requires Registry edit to enable hex numpad
            // Alternative: Use WinCompose or similar
            register_code(KC_LALT);
            tap_code16_delay(KC_KP_PLUS, 10);

            // Send hex digits using numpad
            for (int i = 3; i >= 0; i--) {
                uint8_t digit = (unicode_point >> (i * 4)) & 0xF;
                if (digit != 0 || i == 0) {
                    if (digit < 10) {
                        tap_code16_delay(KC_KP_0 + digit, 10);
                    } else {
                        // For A-F, we need to use the regular keys with Alt held
                        char hex_char = 'a' + (digit - 10);
                        tap_code16_delay(get_ascii_keycode(hex_char, layout), 10);
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
                tap_code16_delay(get_ascii_keycode(hex_char, layout), 10);
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
            tap_code16_delay(get_ascii_keycode(c, layout), 10);
            unregister_code(KC_LSFT);
        }
        // Handle lowercase letters and numbers
        else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            tap_code16_delay(get_ascii_keycode(c, layout), 10);
        }
        // Handle other characters if needed
        str++;
    }
}

// Process glyph keycodes
bool process_record_glyph(uint16_t keycode, keyrecord_t *record) {
    // Only handle our keycode range
    if (keycode < G_FIRST || keycode > G_LAST) {
        return true;
    }

    // Only process on key press
    if (!record->event.pressed) {
        return false;
    }

    // Get glyph data
    uint16_t index = keycode - G_FIRST;

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
            wait_ms(10);  // Small delay between characters
        }
    } else if (glyph->unicode != 0) {
        // Single unicode character
        send_unicode_glyph(glyph->unicode);
    }

    return false;
}
