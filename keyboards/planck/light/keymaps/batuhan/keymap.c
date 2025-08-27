/* Copyright 2025 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "batuhan.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    // Base layer
    [_BASE] = LAYOUT_ortho_4x12_wrapper(
                        _BL1_5_,_BL1_1_,_BR1_1_,_BR1_5_,
                        _BL2_5_,_BL2_1_,_BR2_1_,_BR2_5_,
                        _BL3_5_,_BL3_1_,_BR3_1_,_BR3_5_,
        RM_NEXT,KC_DOWN,KC_UP,  _BL4_3_,_BR4_3_,KC_LEFT,KC_RGHT,RM_TOGG
    ),
    // Dvorak emulation
    [_DVOR] = LAYOUT_ortho_4x12_wrapper(
                        _DL1_5_,_DL1_1_,_DR1_1_,_DR1_5_,
                        _DL2_5_,_DL2_1_,_DR2_1_,_DR2_5_,
                        _DL3_5_,_DL3_1_,_DR3_1_,_DR3_5_,
        RM_NEXT,KC_DOWN,KC_UP,  _DL4_3_,_DR4_3_,KC_LEFT,KC_RGHT,RM_TOGG
    ),
    // Game layer overlay
    [_GAME] = LAYOUT_ortho_4x12_wrapper(
                        _GL1_5_,_GL1_1_,_GR1_1_,_GR1_5_,
                        _GL2_5_,_GL2_1_,_GR2_1_,_GR2_5_,
                        _GL3_5_,_GL3_1_,_GR3_1_,_GR3_5_,
        RM_NEXT,KC_DOWN,KC_UP,  _GL4_3_,_GR4_3_,KC_LEFT,KC_RGHT,RM_TOGG
    ),
    // Extra characters overlay
    [_CHAR] = LAYOUT_ortho_4x12_wrapper(
                        _CL1_5_,_CL1_1_,_CR1_1_,_CR1_5_,
                        _CL2_5_,_CL2_1_,_CR2_1_,_CR2_5_,
                        _CL3_5_,_CL3_1_,_CR3_1_,_CR3_5_,
        RM_NEXT,KC_DOWN,KC_UP,  _CL4_3_,_CR4_3_,KC_LEFT,KC_RGHT,RM_TOGG
    ),
    // Symbol layer: right_half
    [_SYMB] = LAYOUT_ortho_4x12_wrapper(
        ___6___,_SY1_1_,_SY1_5_,
        ___6___,_SY2_1_,_SY2_5_,
        ___6___,_SY3_1_,_SY3_5_,
        ___6___,_SY4_3_,___3___
    ),
    // Number layer: left_half
    [_NUMB] = LAYOUT_ortho_4x12_wrapper(
        _NU1_5_,_NU1_1_,___6___,
        _NU2_5_,_NU2_1_,___6___,
        _NU3_5_,_NU3_1_,___6___,
        ___3___,_NU4_3_,___6___
    ),
    // Navigation layer: right_half
    [_NAVI] = LAYOUT_ortho_4x12_wrapper(
        ___6___,xxx1xxx,_NA1_5_,
        ___6___,xxx1xxx,_NA2_5_,
        ___6___,xxx1xxx,_NA3_5_,
        ___6___,_NA4_3_,___3___
    ),
    // Function layer: left_half
    [_FUNC] = LAYOUT_ortho_4x12_wrapper(
        _FU1_5_,xxx1xxx,___6___,
        _FU2_5_,xxx1xxx,___6___,
        _FU3_5_,xxx1xxx,___6___,
        ___3___,_FU4_3_,___6___
    ),
    // Settings layer: right_half
    [_SETT] = LAYOUT_ortho_4x12_wrapper(
        ___6___,xxx1xxx,_SE1_5_,
        ___6___,xxx1xxx,_SE2_5_,
        ___6___,xxx1xxx,_SE3_5_,
        ___6___,_SE4_3_,___3___
    ),
    // Mouse layer: left_half
    [_MOUS] = LAYOUT_ortho_4x12_wrapper(
        _MO1_5_,xxx1xxx,___6___,
        _MO2_5_,xxx1xxx,___6___,
        _MO3_5_,xxx1xxx,___6___,
        ___3___,_MO4_3_,___6___
    ),
    // Music layer: everything
    [_MUSI] = LAYOUT_ortho_4x12_wrapper(
                            _MU_12_,
                            _MU_12_,
                            _MU_12_,
        ___1___,_MU_02_,_MUL_3_,_MUR_3_,_MU_02_,___1___)
    // clang-format on
};
