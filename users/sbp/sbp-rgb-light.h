/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include "sbp.h"

/* UNDERGLOW IMPLEMENTATION
 */

// Used to initialize layer switching overlay
void keyboard_post_init_rgblight(void);
// Used to change RGB underglow layers on keymap layer change
layer_state_t layer_state_set_rgblight(layer_state_t state);
// Hook into shutdown to show effect on shutdown
void shutdown_rgblight(void);
