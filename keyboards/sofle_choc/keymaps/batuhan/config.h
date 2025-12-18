/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once

// Use EE_HANDS to determine handedness
#   define EE_HANDS

// WS2812 RGB configuration for atmega32u4
#   define WS2812_PWM_DRIVER PWMD3  // Use Timer 3 instead of Timer 2
#   define WS2812_PWM_CHANNEL 2     // Use channel 2
#   define WS2812_PWM_PAL_MODE 2    // PWM mode
