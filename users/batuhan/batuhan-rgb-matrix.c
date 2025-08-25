/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma GCC optimize("Os")
#include "batuhan-rgb-matrix.h"
#include "color.h"

// Keyboard-specific midpoint for split detection
// This should be overridden in keyboard config if needed
#ifndef RGB_MATRIX_CENTER_X
#    define RGB_MATRIX_CENTER_X 112
#endif
/* Code relating to per-key RGB LED stuff
 */

// Allow hooking into the RGB matrix indications using keymap code

// Modulates the brightness of indicator
RGB helper_dimmer(uint8_t r, uint8_t g, uint8_t b) {
    RGB output;
    output.r = r / 2;
    output.g = g / 2;
    output.b = b / 2;
    return output;
}

// x range typically 0-left to 224-right, y range 0-top to 64-bottom
// side: 0=both, 1=left, 2=right
void helper_painter(uint8_t led_min, uint8_t led_max, RGB col, uint8_t side) {
    for (uint8_t i = led_min; i <= led_max; i++) {
        if (!(g_led_config.flags[i] & LED_FLAG_INDICATOR)) continue;

        bool should_set = false;
        switch (side) {
            case 1: // Left side only
                should_set = (g_led_config.point[i].x < RGB_MATRIX_CENTER_X);
                break;
            case 2: // Right side only
                should_set = (g_led_config.point[i].x > RGB_MATRIX_CENTER_X);
                break;
            case 0: // Both sides
                should_set = true;
                break;
        }

        if (should_set) {
            rgb_matrix_set_color(i, col.r, col.g, col.b);
        }
    }
}

// Allow to turn off global handling
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    return true;
}
// Set RGB state depending on layer
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Load keymap hooks, and allow skipping us if returned false
    if (!rgb_matrix_indicators_advanced_keymap(led_min, led_max)) {
        return false;
    }

    uint8_t thisInd         = 0;
    RGB     thisCol         = {0, 0, 0};
    bool    has_layer_color = false;

    // Grab color info based on active layer
    switch (get_highest_layer(layer_state)) {
        case _GAME: // Set left side as purple
            thisCol         = helper_dimmer(RGB_PURPLE);
            thisInd         = 1;
            has_layer_color = true;
            break;
        case _CHAR: // Set full board as magenta
            thisCol         = helper_dimmer(RGB_MAGENTA);
            thisInd         = 0;
            has_layer_color = true;
            break;
        case _SYMB: // Set right side as cyan
            thisCol         = helper_dimmer(RGB_CYAN);
            thisInd         = 2;
            has_layer_color = true;
            break;
        case _NUMB: // Set left side as blue
            thisCol         = helper_dimmer(RGB_AZURE);
            thisInd         = 1;
            has_layer_color = true;
            break;
        case _NAVI: // Set right side as orange
            thisCol         = helper_dimmer(RGB_ORANGE);
            thisInd         = 2;
            has_layer_color = true;
            break;
        case _FUNC: // Set left side as coral
            thisCol         = helper_dimmer(RGB_CORAL);
            thisInd         = 1;
            has_layer_color = true;
            break;
        case _SETT: // Set right side as chartreuse
            thisCol         = helper_dimmer(RGB_CHARTREUSE);
            thisInd         = 2;
            has_layer_color = true;
            break;
        case _MOUS: // Set left side as blue-green
            thisCol         = helper_dimmer(RGB_SPRINGGREEN);
            thisInd         = 1;
            has_layer_color = true;
            break;
        case _MUSI: // Set full board as yellow
            thisCol         = helper_dimmer(RGB_GOLD);
            thisInd         = 0;
            has_layer_color = true;
            break;
    }

    // Only paint if we have a color for this layer
    if (has_layer_color) {
        helper_painter(led_min, led_max, thisCol, thisInd);
    }

    return true;
}

// Hook into shutdown code to make all perkey LEDs colored on hitting reset
void shutdown_rgbmatrix(bool jump_to_bootloader) {
    if (jump_to_bootloader) {
        // Flash red for bootloader
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_RED);
    } else {
        // Flash orange for reset
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
    }
    // Small delay to ensure it's visible
    wait_ms(100);
}

// Note: Suspend/wake is handled automatically by QMK when RGB_MATRIX_SLEEP is defined
// in config.h. The rgb_matrix_set_suspend_state() is called by quantum.c
