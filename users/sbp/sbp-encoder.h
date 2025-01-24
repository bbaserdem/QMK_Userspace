/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include "sbp.h"

// Hook to encoder stuff
// Complicated code for what the encoder keys do when pressed down
bool encoder_update_user(uint8_t index, bool clockwise);

// Defines for the keycode clicks should do (defined in sbp-keycodes.h)
bool process_record_encoder(uint16_t keycode, keyrecord_t *record);

// Clears the encoder settings (eeprom init uses this)
void reset_encoder_state(void);

// This is purely for oled; should it want to use it
#ifdef OLED_ENABLE
void encoder_state_string(uint8_t index, uint8_t layer, char* buffer);
#endif // OLED_ENABLE
