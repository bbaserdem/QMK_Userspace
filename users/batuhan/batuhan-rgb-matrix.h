/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include "batuhan.h"

// For custom indicators
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);

// Keymap level hook for custom indicators
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);

// Hook into shutdown code
void shutdown_rgbmatrix(bool jump_to_bootloader);
