/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma GCC optimize("Os")
#include "sbp-rgb-matrix.h"
#include "color.h"

#define X_DIV 224 / 2
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

// x range from 0-left to 224-right
// y range from 0-top  to  64-bottom
void helper_painter(uint8_t led_min, uint8_t led_max, RGB col, uint8_t side) {
    if (side == 1) {
        // Left
        for (uint8_t i = led_min; i <= led_max; i++) {
            if ((g_led_config.point[i].x < X_DIV) && (g_led_config.flags[i] & LED_FLAG_INDICATOR)) {
                rgb_matrix_set_color(i, col.r, col.g, col.b);
            }
        }
    } else if (side == 2) {
        // Right
        for (uint8_t i = led_min; i <= led_max; i++) {
            if ((g_led_config.point[i].x > X_DIV) && (g_led_config.flags[i] & LED_FLAG_INDICATOR)) {
                rgb_matrix_set_color(i, col.r, col.g, col.b);
            }
        }
    } else if (side == 0) {
        // Both
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_INDICATOR) {
                rgb_matrix_set_color(i, col.r, col.g, col.b);
            }
        }
    }
}

// Allow to turn off global handling
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    return false;
}
// Set RGB state depending on layer
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t thisInd = 3;
    RGB     thisCol;

    // Load keymap hooks, and allow skipping us if returned true
    if (rgb_matrix_indicators_advanced_keymap(led_min, led_max)) {
        return;
    }

    // Grab color info
    switch (get_highest_layer(layer_state)) {
        case _GAME: // Set left side as purple
            thisCol = helper_dimmer(RGB_PURPLE);
            thisInd = 0;
            break;
        case _CHAR: // Set full board as magenta
            thisCol = helper_dimmer(RGB_MAGENTA);
            thisInd = 0;
            break;
        case _SYMB: // Set right side as cyan
            thisCol = helper_dimmer(RGB_CYAN);
            thisInd = 2;
            break;
        case _NUMB: // Set left side as blue
            thisCol = helper_dimmer(RGB_AZURE);
            thisInd = 1;
            break;
        case _NAVI: // Set right side as orange
            thisCol = helper_dimmer(RGB_ORANGE);
            thisInd = 2;
            break;
        case _FUNC: // Set left side as coral
            thisCol = helper_dimmer(RGB_CORAL);
            thisInd = 1;
            break;
        case _KEYB: // Set right side as chartreuse
            thisCol = helper_dimmer(RGB_CHARTREUSE);
            thisInd = 2;
            break;
        case _MOUS: // Set left side as blue-green
            thisCol = helper_dimmer(RGB_SPRINGGREEN);
            thisInd = 1;
            break;
        case _MUSI: // Set full board as yellow
            thisCol = helper_dimmer(RGB_GOLD);
            thisInd = 0;
            break;
    }
    helper_painter(led_min, led_max, thisCol, thisInd);
}

// Hook into shutdown code to make all perkey LED's red on hitting reset
void shutdown_rgbmatrix(void) {
    // Flash all the key LED's red on shutdown
    uint16_t timer_start = timer_read();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_RED);
    // Delay until this registers
    while (timer_elapsed(timer_start) < 250) {
        wait_ms(1);
    }
}

// Hook into suspend code
void suspend_power_down_rgbmatrix(void) {
    rgb_matrix_set_suspend_state(true);
}
void suspend_wakeup_init_rgbmatrix(void) {
    rgb_matrix_set_suspend_state(false);
}
