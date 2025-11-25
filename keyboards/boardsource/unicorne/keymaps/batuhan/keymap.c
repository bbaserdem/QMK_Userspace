// clang-format off
/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#include QMK_KEYBOARD_H
#include "batuhan.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_wrapper(
        _BL1_6_,_BR1_6_,
        _BL2_6_,_BR2_6_,
        _BL3_6_,_BR3_6_,
        _BL4_3_,_BR4_3_),
    [_DVOR] = LAYOUT_split_3x6_3_wrapper(
        _DL1_6_,_DR1_6_,
        _DL2_6_,_DR2_6_,
        _DL3_6_,_DR3_6_,
        _DL4_3_,_DR4_3_),
    [_GAME] = LAYOUT_split_3x6_3_wrapper(
        _GL1_6_,_GR1_6_,
        _GL2_6_,_GR2_6_,
        _GL3_6_,_GR3_6_,
        _GL4_3_,_GR4_3_),
    [_CHAR] = LAYOUT_split_3x6_3_wrapper(
        _CL1_6_,_CR1_6_,
        _CL2_6_,_CR2_6_,
        _CL3_6_,_CR3_6_,
        _CL4_3_,_CR4_3_),
    [_SYMB] = LAYOUT_split_3x6_3_wrapper(
        ___6___,_SY1_6_,
        ___6___,_SY2_6_,
        ___6___,_SY3_6_,
        ___3___,_SY4_3_),
    [_NUMB] = LAYOUT_split_3x6_3_wrapper(
        _NU1_6_,___6___,
        _NU2_6_,___6___,
        _NU3_6_,___6___,
        _NU4_3_,___3___),
    [_NAVI] = LAYOUT_split_3x6_3_wrapper(
        ___6___,_NA1_6_,
        ___6___,_NA2_6_,
        ___6___,_NA3_6_,
        ___3___,_NA4_3_),
    [_FUNC] = LAYOUT_split_3x6_3_wrapper(
        _FU1_6_,___6___,
        _FU2_6_,___6___,
        _FU3_6_,___6___,
        _FU4_3_,___3___),
    [_SETT] = LAYOUT_split_3x6_3_wrapper(
        ___6___,_SE1_6_,
        ___6___,_SE2_6_,
        ___6___,_SE3_6_,
        ___3___,_SE4_3_),
    [_MOUS] = LAYOUT_split_3x6_3_wrapper(
        _MO1_6_,___6___,
        _MO2_6_,___6___,
        _MO3_6_,___6___,
        _MO4_3_,___3___),
    [_MUSI] = LAYOUT_split_3x6_3_wrapper(
        _MU_12_,_MU_12_,_MU_12_,
            _MUL_3_,_MUR_3_)
};

// Set LED info
void matrix_init_keymap(void) {
#ifdef RGB_MATRIX_ENABLE
    // Led locations are different on boardsource crkbd
    // First six leds are underglow
    // Next 21 leds are perkey left
    // Next 6 leds are underglow
    // Next 21 leds are perkey right
    g_led_config = (led_config_t){
        {   // Logical Layout
            // 0  1  2  3  4  5  COLS
            // -LEFT             ROWS
            // 24 23 18 17 10 09   0
            // 25 22 19 16 11 08   1
            // 26 21 20 15 12 07   2
            //          14 13 06   3
            // -Right
            // 51 50 45 44 37 36   4
            // 52 49 46 43 38 35   5
            // 53 48 47 42 39 34   6
            //          41 40 33   7
            {   24,     23,     18,     17,     10,     9},
            {   25,     22,     19,     16,     11,     8},
            {   26,     21,     20,     15,     12,     7},
            {   NO_LED, NO_LED, NO_LED, 2,      1,      0},
            {   51,     50,     45,     44,     37,     36},
            {   52,     49,     46,     43,     38,     35},
            {   53,     48,     47,     42,     39,     34},
            {   NO_LED, NO_LED, NO_LED, 41,     40,     33}
        }, {// Physical Layout
            //      LEFT                RIGHT
            // 24 23 18 17 10 09   51 50 45 44 37 36
            //    02  01  00         27  28  29
            // 25 22 19 16 11 08   52 49 46 43 38 35
            //    03  04  05         32  31  30
            // 26 21 20 15 12 07   53 48 47 42 39 34
            //          14 13 06   41 40 33
            { 85,16}, { 50,13}, { 16,20}, { 16,38}, { 50,48}, { 85,52},
            { 95,63}, { 85,39}, { 85,21}, { 85,04}, { 68,02}, { 68,19}, { 68,37},
            { 80,58}, { 60,55}, { 50,35}, { 50,13}, { 50, 0}, { 33, 3}, { 33,20},
            { 33,37}, { 16,42}, { 16,24}, { 16, 7}, {  0, 7}, {  0,24}, {  0,41},
            {139,16}, {174,13}, {208,20}, {208,38}, {174,48}, {139,52},
            {129,63}, {139,39}, {139,21}, {139,04}, {156,02}, {156,19}, {156,37},
            {144,58}, {164,55}, {174,35}, {174,13}, {174, 0}, {191, 3}, {191,20},
            {191,37}, {208,42}, {208,24}, {208, 7}, {223, 7}, {223,24}, {223,41}
        }, {// Led layout
            // (x---)8 stands for (layer) indicator
            // (-x--)4 stands for per-key led
            // (--x-)2 stands for underglow led
            // (---1)1 stands for modifier key
            //  4: mostly per-key leds
            //  5: per-key leds, but also modifier keys
            // 12: per-key leds, but used as layer indicators
            // 10: underglow leds, and used as layer indicators
            10,10,10,10,10,10,
            12, 4, 4, 4, 4, 5, 5,12,
            12, 5, 5, 4, 4, 5, 5,
                5, 5, 4, 4, 5, 4,
            10,10,10,10,10,10,
            12, 4, 4, 4, 4, 5, 5,12,
            12, 5, 5, 4, 4, 5, 5,
                5, 5, 4, 4, 5, 4
        }
    };
#endif // RGB_MATRIX_ENABLE
}
