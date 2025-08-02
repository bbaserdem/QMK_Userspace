/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma GCC optimize("Os")
#include "sbp-rgb-light.h"

/* UNDERGLOW IMPLEMENTATION
 * This file needs each keyboard to define the following;
 * - RGBLIGHT_LED_COUNT (required)
 * - RGBLIGHT_LEFT_BEG
 * - RGBLIGHT_LEFT_NUM
 * - RGBLIGHT_RIGHT_BEG
 * - RGBLIGHT_RIGHT_NUM
 */

// Define the layer switching code

// For full layers, color left and right of the strip
const rgblight_segment_t PROGMEM sbp_game_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_PURPLE}, {RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_PURPLE});
const rgblight_segment_t PROGMEM sbp_char_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_MAGENTA}, {RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_MAGENTA});
const rgblight_segment_t PROGMEM sbp_musi_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_GOLD}, {RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_GOLD});

// Right-hand layers
const rgblight_segment_t PROGMEM sbp_keyb_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_CHARTREUSE});
const rgblight_segment_t PROGMEM sbp_navi_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_ORANGE});
const rgblight_segment_t PROGMEM sbp_symb_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_CYAN});

// Left-hand layers
const rgblight_segment_t PROGMEM sbp_numb_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_AZURE});
const rgblight_segment_t PROGMEM sbp_func_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_CORAL});
const rgblight_segment_t PROGMEM sbp_mous_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_SPRINGGREEN});

// The layer setup
const rgblight_segment_t* const PROGMEM sbp_rgb_layers[] = RGBLIGHT_LAYERS_LIST(sbp_game_layer, // 0
                                                                                sbp_char_layer, // 1
                                                                                sbp_symb_layer, // 2
                                                                                sbp_numb_layer, // 3
                                                                                sbp_navi_layer, // 4
                                                                                sbp_func_layer, // 5
                                                                                sbp_keyb_layer, // 6
                                                                                sbp_mous_layer, // 7
                                                                                sbp_musi_layer  // 8
);

// Enable the LED switching layers
void keyboard_post_init_rgblight(void) {
    rgblight_layers = sbp_rgb_layers;
}

// Set RGBLIGHT state depending on layer
layer_state_t layer_state_set_rgblight(layer_state_t state) {
    // Activate layers if on that region
    // First arg is the index in the array <rgblight_layers>
    rgblight_set_layer_state(0, layer_state_cmp(state, _GAME));
    rgblight_set_layer_state(1, layer_state_cmp(state, _CHAR));
    rgblight_set_layer_state(2, layer_state_cmp(state, _SYMB));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUMB));
    rgblight_set_layer_state(4, layer_state_cmp(state, _NAVI));
    rgblight_set_layer_state(5, layer_state_cmp(state, _FUNC));
    rgblight_set_layer_state(6, layer_state_cmp(state, _KEYB));
    rgblight_set_layer_state(7, layer_state_cmp(state, _MOUS));
    rgblight_set_layer_state(8, layer_state_cmp(state, _MUSI));
    // Return so other stuff can be done
    return state;
}

// Hook into shutdown code
void shutdown_rgblight(void) {
    // Make the LED's red on shutdown
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv(HSV_RED);
}
