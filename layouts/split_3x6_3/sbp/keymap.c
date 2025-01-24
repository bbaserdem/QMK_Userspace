/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#include QMK_KEYBOARD_H
#include "bbaserdem.h"

#ifdef KEYBOARD_crkbd_rev1
#   include "bb-oled-extra.h"
#endif // KEYBOARD_crkbd_rev1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_wrapper(
        BB_ENC0,_BL1_5_,_BR1_5_,BB_ENC1,
        _BL2_1_,_BL2_5_,_BR2_5_,_BR2_1_,
        _BL3_1_,_BL3_5_,_BR3_5_,_BR3_1_,
                _BL4_3_,_BR4_3_
    ),
    [_DVOR] = LAYOUT_split_3x6_3_wrapper(
        BB_ENC0,_DL1_5_,_DR1_5_,BB_ENC1,
        _DL2_1_,_DL2_5_,_DR2_5_,_DR2_1_,
        _DL3_1_,_DL3_5_,_DR3_5_,_DR3_1_,
                _DL4_3_,_DR4_3_
    ),
    [_GAME] = LAYOUT_split_3x6_3_wrapper(
        _______,_GL1_5_,_GR1_5_,_______,
        _GL2_1_,_GL2_5_,_GR2_5_,_GR2_1_,
        _GL3_1_,_GL3_5_,_GR3_5_,_GR3_1_,
                _GL4_3_,_GR4_3_
    ),
    [_CHAR] = LAYOUT_split_3x6_3_wrapper(
        _______,_CL1_5_,_CR1_5_,_______,
        xxx1xxx,_CL2_5_,_CR2_5_,xxx1xxx,
        xxx1xxx,_CL3_5_,_CR3_5_,xxx1xxx,
                _CL4_3_,_CR4_3_
    ),
    [_SYMB] = LAYOUT_split_3x6_3_wrapper(
        ___6___,_SY1_5_,_______,
        ___6___,_SY2_5_,_SY2_1_,
        ___6___,_SY3_5_,_SY3_1_,
        ___3___,_SY4_3_
    ),
    [_NUMB] = LAYOUT_split_3x6_3_wrapper(
        _______,_NU1_5_,___6___,
        _NU2_1_,_NU2_5_,___6___,
        _NU3_1_,_NU3_5_,___6___,
                _NU4_3_,___3___
    ),
    [_NAVI] = LAYOUT_split_3x6_3_wrapper(
        ___6___,_NA1_5_,_______,
        ___6___,_NA2_5_,xxx1xxx,
        ___6___,_NA3_5_,xxx1xxx,
        ___3___,_NA4_3_
    ),
    [_FUNC] = LAYOUT_split_3x6_3_wrapper(
        _______,_FU1_5_,___6___,
        xxx1xxx,_FU2_5_,___6___,
        xxx1xxx,_FU3_5_,___6___,
                _FU4_3_,___3___
    ),
    [_KEYB] = LAYOUT_split_3x6_3_wrapper(
        ___6___,_KE1_5_,_______,
        ___6___,_KE2_5_,xxx1xxx,
        ___6___,_KE3_5_,xxx1xxx,
        ___3___,_KE4_3_
    ),
    [_MOUS] = LAYOUT_split_3x6_3_wrapper(
        _______,_MO1_5_,___6___,
        xxx1xxx,_MO2_5_,___6___,
        xxx1xxx,_MO3_5_,___6___,
                _MO4_3_,___3___
    ),
    [_MUSI] = LAYOUT_split_3x6_3_wrapper(
            _MU_12_,
            _MU_12_,
            _MU_12_,
        _MUL_3_,_MUR_3_
    )
};

// Waffle-corne rev1 specific things
#ifdef KEYBOARD_crkbd_rev1

// Enable the music mapping feature
#   ifdef AUDIO_ENABLE
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_split_3x6_3(
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
                 0,  0,  0,  0,  0,  0
);
#   endif // AUDIO_ENABLE

// Set LED info
void matrix_init_keymap(void) {
#   ifdef RGB_MATRIX_ENABLE
    // Led locations are different on waffle corne; need to be fixed
    g_led_config = (led_config_t) { {
        // Logical Layout
        // 0  1  2  3  4  5  COLS
        // -LEFT             ROWS
        // 16 17 18 19 20 21   0
        // 15 14 13 12 11 10   1
        // 04 05 06 07 08 09   2
        //          03 02 01   3
        // -Right
        // 21 20 19 18 17 16   4
        // 10 11 12 13 14 15   5
        // 09 08 07 06 05 04   6
        //          01 02 03   7
        {  15,  16,  17,  18,  19,   20},
        {  14,  13,  12,  11,  10,   9 },
        {   3,   4,   5,   6,   7,   8 },
        { NO_LED, NO_LED, NO_LED,   2,   1,   0 },
        {  47,  46,  45,  44,  43,  42 },
        {  36,  37,  38,  39,  40,  41 },
        {  35,  34,  33,  32,  31,  30 },
        { NO_LED, NO_LED, NO_LED,  27,  28,  29 }
    }, {
        // Physical Layout
        //      LEFT                    RIGHT
        // 16 17 18 19 20 21       16 17 18 19 20 21
        //    24    23    22       24    23    22
        // 15 14 13 12 11 10       15 14 13 12 11 10
        //    25                               27
        // 04 05 06 07 08 09       04 05 06 07 08 09
        //          26    27       25    26
        //           03 02 01     03 02 01
        {  95,  63 }, {  80,  58 }, {  60,  55 },
        {   0,  41 }, {  16,  42 }, {  33,  37 }, {  50,  35 }, {  68,  37 }, {  85,  39 },
        {  85,  21 }, {  68,  19 }, {  50,  13 }, {  33,  20 }, {  16,  24 }, {   0,  24 },
        {   0,   7 }, {  16,   7 }, {  33,   3 }, {  50,   0 }, {  68,   2 }, {  85,   4 },
        {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 },
        { 164,  55 }, { 144,  58 }, { 129,  63 },
        { 139,  39 }, { 156,  37 }, { 174,  35 }, { 191,  37 }, { 208,  42 }, { 224,  41 },
        { 224,  24 }, { 208,  24 }, { 191,  20 }, { 174,  13 }, { 156,  19 }, { 139,  21 },
        { 139,   4 }, { 156,   2 }, { 174,   0 }, { 191,   3 }, { 208,   7 }, { 224,   7 },
        { 208,  20 }, { 174,  13 }, { 139,  16 }, { 139,  52 }, { 174,  48 }, { 208,  38 }
    }, {
        // (x---)8 stands for (layer) indicator
        // (-x--)4 stands for per-key led
        // (--x-)2 stands for underglow led
        // (---1)1 stands for modifier key
        //  4: mostly per-key leds
        //  5: per-key leds, but also modifier keys
        // 12: per-key leds, but used as layer indicators
        // 10: underglow leds, and used as layer indicators
        12, 12, 12,
         4,  5,  5,  5,  5,  4,
         4,  5,  5,  5,  5,  4,
         4,  4,  4,  4,  4,  4,
        10, 10, 10, 10, 10, 10,
        12, 12, 12,
         4,  5,  5,  5,  5,  4,
         4,  5,  5,  5,  5,  4,
         4,  4,  4,  4,  4,  4,
        10, 10, 10, 10, 10, 10
    } };
#   endif // RGB_MATRIX_ENABLE
}

// Fix pimoroni trackball color
#   ifdef RGB_MATRIX_ENABLE
#   ifdef POINTING_DEVICE_ENABLE
extern LED_TYPE rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];
bool rgb_matrix_indicators_advanced_keymap(uint_8 led_min, uint_8 led_max) {
    pimoroni_trackball_set_rgbw(
        rgb_matrix_ws2812_array[29].r,
        rgb_matrix_ws2812_array[29].g,
        rgb_matrix_ws2812_array[29].b,
        0
    );
    return false;
}
#   endif // POINTING_DEVICE_ENABLE
#   endif // RGB_MATRIX_ENABLE

// This is straight from waffle code
void housekeeping_task_keymap(void) {
    if (last_input_activity_elapsed() > 5000) {
        const pin_t row_pins[] = MATRIX_ROW_PINS, col_pins[] = MATRIX_COL_PINS;
        for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
            setPinOutput(col_pins[i]);
            writePinLow(col_pins[i]);
        }
        for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
            setPinInputHigh(row_pins[i]);
            palEnableLineEvent(row_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
        }
        __WFI();
        for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
            palDisableLineEvent(row_pins[i]);
            writePinHigh(row_pins[i]);
            setPinInputHigh(row_pins[i]);
        }
        for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
            writePinHigh(col_pins[i]);
            setPinInputHigh(col_pins[i]);
        }
    }
}

// Set Audio related things
void keyboard_pre_init_keymap(void) {
#   ifdef AUDIO_ENABLE
    //thank you to @sigprof for this
    // Set audio pins to analog mode
    palSetLineMode(A5, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B1, PAL_MODE_INPUT_ANALOG);
#   endif // AUDIO_ENABLE

}

// Enable OPAMP1 as A5 → B1 follower
#ifdef AUDIO_ENABLE
void keyboard_post_init_keymap(void) {
    OPAMP3->CSR = OPAMP3_CSR_VMSEL_1 | OPAMP3_CSR_VMSEL_0 | OPAMP3_CSR_VPSEL_0 | OPAMP3_CSR_OPAMP3EN;
}
#endif // AUDIO_ENABLE

#ifdef OLED_ENABLE
// Flip the display on the right half
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_keymap(void) {
    if (is_keyboard_left()) {
        render_status_left(0, 0);
    } else {
        render_status_right(0, 0);
    }
    return false;
}
#endif // OLED_ENABLE
#endif // KEYBOARD_crkbd_rev1
