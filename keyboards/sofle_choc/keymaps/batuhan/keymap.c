/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#include QMK_KEYBOARD_H
#include "batuhan.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_BASE] = LAYOUT_wrapper(
            _BL0_6_,                _BR0_6_,
            _BL1_6_,                _BR1_6_,
            _BL2_6_,                _BR2_6_,
            _BL3_6_,B_ENC0, B_ENC1, _BR3_6_,
    KC_LEFT,KC_RGHT,_BL4_3_,_BR4_3_,KC_DOWN,KC_UP
    ),
    [_DVOR] = LAYOUT_wrapper(
            _DL0_6_,                _DR0_6_,
            _DL1_6_,                _DR1_6_,
            _DL2_6_,                _DR2_6_,
            _DL3_6_,B_ENC0, B_ENC1, _DR3_6_,
    KC_LEFT,KC_RGHT,_BL4_3_,_BR4_3_,KC_DOWN,KC_UP
    ),
    [_GAME] = LAYOUT_wrapper(
        ___6___,                ___6___,
        _GL1_6_,                _GR1_6_,
        _GL2_6_,                _GR2_6_,
        _GL3_6_,_______,_______,_GR3_6_,
        ___2___,_GL4_3_,_GR4_3_,___2___
    ),
    [_CHAR] = LAYOUT_wrapper(
        ___6___,                ___6___,
        _CL1_6_,                _CR1_6_,
        _CL2_6_,                _CR2_6_,
        _CL3_6_,_______,_______,_CR3_6_,
        ___2___,_CL4_3_,_CR4_3_,___2___
    ),
    [_SYMB] = LAYOUT_wrapper(
        ___6___,                ___6___,
        ___6___,                _SY1_6_,
        ___6___,                _SY2_6_,
        ___6___,_______,_______,_SY3_6_,
        ___2___,___3___,_SY4_3_,___2___
    ),
    [_NUMB] = LAYOUT_wrapper(
        ___6___,                ___6___,
        _NU1_6_,                ___6___,
        _NU2_6_,                ___6___,
        _NU3_6_,_______,_______,___6___,
        ___2___,_NU4_3_,___3___,___2___
    ),
    [_NAVI] = LAYOUT_wrapper(
        ___6___,                ___6___,
        ___6___,                _NA1_6_,
        ___6___,                _NA2_6_,
        ___6___,_______,_______,_NA3_6_,
        ___2___,___3___,_NA4_3_,___2___
    ),
    [_FUNC] = LAYOUT_wrapper(
        ___6___,                ___6___,
        _FU1_6_,                ___6___,
        _FU2_6_,                ___6___,
        _FU3_6_,_______,_______,___6___,
        ___2___,_FU4_3_,___3___,___2___
    ),
    [_SETT] = LAYOUT_wrapper(
        ___6___,                ___6___,
        ___6___,                _SE1_6_,
        ___6___,                _SE2_6_,
        ___6___,_______,_______,_SE3_6_,
        ___2___,___3___,_SE4_3_,___2___
    ),
    [_MOUS] = LAYOUT_wrapper(
        ___6___,                ___6___,
        _MO1_6_,                ___6___,
        _MO2_6_,                ___6___,
        _MO3_6_,_______,_______,___6___,
        ___2___,_MO4_3_,___3___,___2___
    ),
};
// clang-format on

/*
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
*/
