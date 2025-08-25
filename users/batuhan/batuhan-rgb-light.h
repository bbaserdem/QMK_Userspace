/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include "batuhan.h"

/* UNDERGLOW IMPLEMENTATION
 * This file handles RGB underglow lighting layers.
 * Requires the following defines in keyboard's config.h:
 * - RGBLIGHT_LED_COUNT (required by QMK)
 * - RGBLIGHT_LAYERS (required for layer support)
 * - RGBLIGHT_LEFT_BEG (starting index for left side LEDs)
 * - RGBLIGHT_LEFT_NUM (number of left side LEDs)
 * - RGBLIGHT_RIGHT_BEG (starting index for right side LEDs)
 * - RGBLIGHT_RIGHT_NUM (number of right side LEDs)
 */

// Configuration validation
#ifndef RGBLIGHT_LED_COUNT
    #error "RGBLIGHT_LED_COUNT must be defined in config.h"
#endif

#ifndef RGBLIGHT_LAYERS
    #error "RGBLIGHT_LAYERS must be defined in config.h to use RGB lighting layers"
#endif

// Check if split keyboard LED defines are provided
#if !defined(RGBLIGHT_LEFT_BEG) || !defined(RGBLIGHT_LEFT_NUM) || !defined(RGBLIGHT_RIGHT_BEG) || !defined(RGBLIGHT_RIGHT_NUM)
    #warning "RGBLIGHT split defines not set. Using defaults for single strip."
    #define RGBLIGHT_LEFT_BEG 0
    #define RGBLIGHT_LEFT_NUM (RGBLIGHT_LED_COUNT / 2)
    #define RGBLIGHT_RIGHT_BEG (RGBLIGHT_LED_COUNT / 2)
    #define RGBLIGHT_RIGHT_NUM (RGBLIGHT_LED_COUNT - RGBLIGHT_LED_COUNT / 2)
#endif

// Number of layers we're defining (must not exceed RGBLIGHT_MAX_LAYERS)
#define BATUHAN_RGBLIGHT_LAYER_COUNT 9

// Validate against maximum layers
#ifndef RGBLIGHT_MAX_LAYERS
    #define RGBLIGHT_MAX_LAYERS 8
#endif

#if BATUHAN_RGBLIGHT_LAYER_COUNT > RGBLIGHT_MAX_LAYERS
    #error "BATUHAN_RGBLIGHT_LAYER_COUNT exceeds RGBLIGHT_MAX_LAYERS. Increase RGBLIGHT_MAX_LAYERS in config.h or reduce layer count."
#endif

// Used to initialize layer switching overlay
void keyboard_post_init_rgblight(void);
// Used to change RGB underglow layers on keymap layer change
layer_state_t layer_state_set_rgblight(layer_state_t state);
// Hook into shutdown to show effect on shutdown
void shutdown_rgblight(void);
