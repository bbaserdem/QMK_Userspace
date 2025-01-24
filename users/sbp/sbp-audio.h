/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include "sbp.h"

/* AUDIO
 * Some functions to hook to some modes
 */

// Hook to layer change effects
layer_state_t layer_state_set_audio(layer_state_t state);

// Hook to audio keycodes
bool process_record_audio(uint16_t keycode, keyrecord_t *record);
