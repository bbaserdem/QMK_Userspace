/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#include QMK_KEYBOARD_H
#include "sbp.h"

/* F layout
 * ┌───┬───┬───┬───┬───┬───┐                 ┌───┬───┬───┬───┬───┬───┐
 * │ W │ F │ G │ Ğ │ I │ O │                 │ D │ R │ N │ H │ P │ Q │
 * ├───┼───┼───┼───┼───┼───┤                 ├───┼───┼───┼───┼───┼───┤
 * │ X │ A │ S │ D │ F │ G │                 │ T │ K │ M │ L │ Y │ Ş │
 * ├───┼───┼───┼───┼───┼───┼───┬───┐ ┌───┬───┼───┼───┼───┼───┼───┼───┤
 * │* +│ J │ Ö │ V │ C │ Ç │   │   │ │   │   │ Z │ S │ B │. :│, ;│< >│
 * └───┴───┴───┼───┼───┼───┤Esc│Shf│ │Shf│Del├───┼───┼───┼───┴───┴───┘
 *             │En1│Tab│Ent│   │   │ │   │   │Spc│Bsp│En2│
 *             └───┴───┴───┴───┴───┘ └───┴───┴───┴───┴───┘
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_wrapper(
        _BL1_1_,_BL1_5_,                _BR1_5_,_BR1_1_,
        _BL2_1_,_BL2_5_,                _BR2_5_,_BR2_1_,
        _BL3_1_,_BL3_5_,xxx2xxx,xxx2xxx,_BR3_5_,_BR3_1_,
        BB_ENC0, _BL4_3_,KC_LSFT,KC_RSFT,_BR4_3_,BB_ENC1
    ),
    [_DVOR] = LAYOUT_wrapper(
        _DL1_1_,_DL1_5_,                _DR1_5_,_DR1_1_,
        _DL2_1_,_DL2_5_,                _DR2_5_,_DR2_1_,
        _DL3_1_,_DL3_5_,xxx2xxx,xxx2xxx,_DR3_5_,_DR3_1_,
        BB_ENC0, _DL4_3_,KC_LSFT,KC_RSFT,_DR4_3_,BB_ENC1
    ),
    [_GAME] = LAYOUT_wrapper(
        _GL1_1_,_GL1_5_,                _GR1_5_,_GR1_1_,
        _GL2_1_,_GL2_5_,                _GR2_5_,_GR2_1_,
        _GL3_1_,_GL3_5_,xxx2xxx,xxx2xxx,_GR3_5_,_GR3_1_,
        _______,_GL4_3_,KC_TAB, KC_ESC, _GR4_3_,_______
    ),
    [_CHAR] = LAYOUT_wrapper(
        XXXXXXX,_CL1_5_,                _CR1_5_,XXXXXXX,
        XXXXXXX,_CL2_5_,                _CR2_5_,XXXXXXX,
        XXXXXXX,_CL3_5_,xxx2xxx,xxx2xxx,_CR3_5_,XXXXXXX,
        _______,_CL4_3_,_______,_______,_CR4_3_,_______
    ),
    [_SYMB] = LAYOUT_wrapper(
        ___1___,___5___,                _SY1_5_,___1___,
        ___1___,___5___,                _SY2_5_,_SY2_1_,
        ___1___,___5___,xxx2xxx,xxx2xxx,_SY3_5_,_SY3_1_,
        ___1___,___3___,_______,_______,_SY4_3_,___1___
    ),
    [_NUMB] = LAYOUT_wrapper(
        ___1___,_NU1_5_,                ___5___,___1___,
        _NU2_1_,_NU2_5_,                ___5___,___1___,
        _NU3_1_,_NU3_5_,xxx2xxx,xxx2xxx,___5___,___1___,
        ___1___,_NU4_3_,_______,_______,___3___,___1___
    ),
    [_NAVI] = LAYOUT_wrapper(
        ___1___,___5___,                _NA1_5_,___1___,
        ___1___,___5___,                _NA2_5_,___1___,
        ___1___,___5___,xxx2xxx,xxx2xxx,_NA3_5_,___1___,
        ___1___,___3___,_______,_______,_NA4_3_,___1___
    ),
    [_FUNC] = LAYOUT_wrapper(
        ___1___,_FU1_5_,                ___5___,___1___,
        ___1___,_FU2_5_,                ___5___,___1___,
        ___1___,_FU3_5_,xxx2xxx,xxx2xxx,___5___,___1___,
        ___1___,_FU4_3_,_______,_______,___3___,___1___
    ),
    [_KEYB] = LAYOUT_wrapper(
        ___1___,___5___,                _KE1_5_,___1___,
        ___1___,___5___,                _KE2_5_,___1___,
        ___1___,___5___,xxx2xxx,xxx2xxx,_KE3_5_,___1___,
        ___1___,___3___,_______,_______,_KE4_3_,___1___
    ),
    [_MOUS] = LAYOUT_wrapper(
        ___1___,_MO1_5_,                ___5___,___1___,
        ___1___,_MO2_5_,                ___5___,___1___,
        ___1___,_MO3_5_,xxx2xxx,xxx2xxx,___5___,___1___,
        ___1___,_MO4_3_,_______,_______,___3___,___1___
    ),
    [_MUSI] = LAYOUT_wrapper(
                        _MU_12_,
                        _MU_12_,
        _MU_06_,    xxx2xxx,xxx2xxx,    _MU_06_,
        MU_TOG, _MUL_3_,_MU_02_,_MUR_3_,___1___
    )
};

#ifdef KEYBOARD_splitkb_kyria_rev1      // Kyria specific code
#ifdef OLED_ENABLE                          // Kyria's oled screen
// Rotate the display on kyria
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}
// For kyria; print logo, and allow default status printing
bool oled_task_keymap(void) {
    render_qmk_logo(0, 0);
    render_status_lite(4, 0);
    return false;
}
#endif //OLED_ENABLE
#endif //KEYBOARD_splitkb_kyria_rev1
