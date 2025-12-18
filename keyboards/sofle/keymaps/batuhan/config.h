/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once

// Use EE_HANDS to determine handedness
#   define EE_HANDS

// Space-saving overrides for Sofle (ATmega32U4 has limited flash)
#ifdef RGB_MATRIX_ENABLE
    // Disable most RGB Matrix effects to save space
    #undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    #undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    #undef ENABLE_RGB_MATRIX_FLOWER_BLOOMING
    #undef ENABLE_RGB_MATRIX_RAINDROPS
    #undef ENABLE_RGB_MATRIX_PIXEL_FLOW
    #undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
    #undef ENABLE_RGB_MATRIX_RIVERFLOW
    #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
    #undef ENABLE_RGB_MATRIX_CYCLE_ALL

    // Keep only requested effects
    #define ENABLE_RGB_MATRIX_SOLID_COLOR
    #define ENABLE_RGB_MATRIX_BREATHING
    #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT

    // Reduce brightness for power/memory savings
    #undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100

    // Override default mode since TYPING_HEATMAP is disabled
    #undef RGB_MATRIX_DEFAULT_MODE
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_BREATHING
#endif

// Disable OLED fade to save space
#ifdef OLED_ENABLE
    #undef OLED_FADE_OUT
    #undef OLED_FADE_OUT_INTERVAL
#endif

// Disable audio features (not available on Sofle anyway)
#ifdef AUDIO_ENABLE
    #undef AUDIO_ENABLE
#endif
