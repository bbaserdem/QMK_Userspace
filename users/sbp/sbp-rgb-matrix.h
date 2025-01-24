/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include "sbp.h"

// For custom indicators
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);
// Hook into shutdown code
void shutdown_rgbmatrix(void);
void suspend_wakeup_init_rgbmatrix(void);
void suspend_power_down_rgbmatrix(void);
