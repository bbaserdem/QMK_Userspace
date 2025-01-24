/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#include "sbp-oled.h"
#include "sbp-oled-extra.h"

// Helper function that draws images
void draw_image(uint8_t row, uint8_t col, const char image[4][42]) {
    // Draw this image iteratively
    for (int i = 0; i < 4; i++) {
        oled_set_cursor(col, row + i);
        oled_write_raw_P(image[i], 42);
    }
}

// Write modifiers to the screen
void render_modifiers(uint8_t row, uint8_t col, uint8_t mods) {
    static const char PROGMEM mod_meta[12] = {0x00,0x01,0x01,0x01,0x01,0x06,0x18,0x60,0x81,0x81,0x81,0x81};
    static const char PROGMEM mod_altL[12] = {0x00,0x80,0x80,0x80,0x40,0x20,0x10,0x08,0x84,0x95,0x8e,0x84};
    static const char PROGMEM mod_altR[12] = {0x00,0x86,0x8f,0x8f,0x46,0x20,0x10,0x08,0x84,0x95,0x8e,0x84};
    static const char PROGMEM mod_ctrl[12] = {0x00,0x00,0xbd,0x42,0xa5,0x99,0x99,0xa5,0x42,0xbd,0x00,0x00};
    static const char PROGMEM mod_shft[12] = {0x00,0x20,0x30,0x28,0xe4,0x02,0x01,0x02,0xe4,0x28,0x30,0x20};
    // Looks like Mods: <OS> <Alt/Gr> <Ctrl> <Shift>
    oled_set_cursor(col, row);
    oled_write("Mods: ", false);
    // Meta
    if (mods & MOD_MASK_GUI) {
        oled_write_raw_P(mod_meta, 12);
        oled_set_cursor(col + 8, row);
    } else {
        oled_write("  ", false);
    }
    // Alt(Gr)
    if (mods & MOD_BIT(KC_RALT)) {
        oled_write_raw_P(mod_altR, 12);
        oled_set_cursor(col + 10, row);
    } else if (mods & MOD_MASK_ALT) {
        oled_write_raw_P(mod_altL, 12);
        oled_set_cursor(col + 10, row);
    } else {
        oled_write("  ", false);
    }
    // Ctrl
    if (mods & MOD_MASK_CTRL) {
        oled_write_raw_P(mod_ctrl, 12);
        oled_set_cursor(col + 12, row);
    } else {
        oled_write("  ", false);
    }
    // Shift
    if (mods & MOD_MASK_SHIFT) {
        oled_write_raw_P(mod_shft, 12);
        oled_set_cursor(col + 14, row);
    } else {
        oled_write("  ", false);
    }
}

// Render the RGB state on the given column and row
void render_rgb(uint8_t row, uint8_t col) {
    static const char PROGMEM rgb_enab[12] = {0x08,0x81,0x3c,0x42,0x99,0xbd,0xbd,0x99,0x42,0x3c,0x81,0x10};
    static const char PROGMEM rgb_disa[12] = {0x08,0x81,0x3c,0x42,0x81,0x81,0x81,0x81,0x42,0x3c,0x81,0x10};
    static char rgb_temp4[4] = {0};
    static char rgb_temp3[3] = {0};

    oled_set_cursor(col, row);
#   ifdef RGB_MATRIX_ENABLE
    if (rgb_matrix_is_enabled()) {
        oled_write_raw_P(rgb_enab, 12);
    } else {
        oled_write_raw_P(rgb_disa, 12);
    }
    oled_set_cursor(col + 2, row);
    oled_write(" hue sat val", false);
    oled_set_cursor(col, row + 1);
    itoa(rgb_matrix_get_mode(), rgb_temp3, 10);
    oled_write(rgb_temp3, false);
    oled_write(" ", false);
    itoa(rgb_matrix_get_hue(), rgb_temp4, 10);
    oled_write(rgb_temp4, false);
    oled_write(" ", false);
    itoa(rgb_matrix_get_sat(), rgb_temp4, 10);
    oled_write(rgb_temp4, false);
    oled_write(" ", false);
    itoa(rgb_matrix_get_val(), rgb_temp4, 10);
    oled_write(rgb_temp4, false);
#   else // RGB_MATRIX_ENABLE
    oled_write("-RGB disabled-", false);
#   endif // RGB_MATRIX_ENABLE
}

void render_status_left(uint8_t row, uint8_t col) {
    // Left side looks like this on the left half
    // (Should be 14 characters per line)
    //  Mods: <OS> <Alt/Gr> <Ctrl> <Shift>
    //  Enc: <8 len str>
    //  Wpm: <wpm here>
    //  Layout: <dvorak/qwerty/tur. f>
    // Right half is whatever layer image needs be
    uint8_t this_mod =   get_mods();
    uint8_t this_layer = get_highest_layer(layer_state);

    // MODIFIERS
    render_modifiers(row + 0, col + 0, this_mod);
    // Encoders
    render_encoder(row + 1, col + 0, 0, this_layer);
    // WPM text
    render_wpm(row + 2, col + 0);
    // Visual layout
    render_keymap(row + 3, col + 0, false);
    // Draw the image after 14'th character
    render_layout(row + 0, col + 14, this_mod, true);
}

void render_status_right(uint8_t row, uint8_t col) {
    // Right half is whatever layer image needs be on the left
    // Right side looks like this on the right half
    // (Should be after the 12'th character; max 14 characters per line)
    //  Mods: <OS> <Alt/Gr> <Ctrl> <Shift>
    //  Enc: <8 len str>
    //  Wpm: <wpm here>
    //  Layout: <dvorak/qwerty/tur. f>
    uint8_t this_mod =   get_mods();
    uint8_t this_layer = get_highest_layer(layer_state);

    // Draw the image
    render_layout(row + 0, col + 0, this_mod, false);
    // Modifiers
    render_modifiers(row + 0, col + 7, this_mod);
    // Encoder
    render_encoder(row + 1, col + 7, 1, this_layer);
    // RGB State (2 rows)
    render_rgb(row + 2, col + 7);
}
