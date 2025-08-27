/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
// clang-format off
#pragma GCC optimize("Os")
#include "batuhan-rgb-light.h"

/* UNDERGLOW IMPLEMENTATION
 * Configuration is validated in batuhan-rgb-light.h
 * This implementation provides layer-based RGB underglow control.
 *
 * Layer mapping:
 * 0: _GAME - Purple (full keyboard)
 * 1: _CHAR - Magenta (full keyboard)
 * 2: _SYMB - Cyan (right side)
 * 3: _NUMB - Azure (left side)
 * 4: _NAVI - Orange (right side)
 * 5: _FUNC - Coral (left side)
 * 6: _SETT - Chartreuse (right side)
 * 7: _MOUS - Spring Green (left side)
 * 8: _MUSI - Gold (full keyboard)
 */

// Define the layer switching code

// For full layers, color left and right of the strip
const rgblight_segment_t PROGMEM batuhan_game_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_PURPLE}, {RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_PURPLE});
const rgblight_segment_t PROGMEM batuhan_char_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_MAGENTA}, {RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_MAGENTA});
const rgblight_segment_t PROGMEM batuhan_musi_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_GOLD}, {RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_GOLD});

// Right-hand layers
const rgblight_segment_t PROGMEM batuhan_sett_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_CHARTREUSE});
const rgblight_segment_t PROGMEM batuhan_navi_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_ORANGE});
const rgblight_segment_t PROGMEM batuhan_symb_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_RIGHT_BEG, RGBLIGHT_RIGHT_NUM, HSV_CYAN});

// Left-hand layers
const rgblight_segment_t PROGMEM batuhan_numb_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_AZURE});
const rgblight_segment_t PROGMEM batuhan_func_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_CORAL});
const rgblight_segment_t PROGMEM batuhan_mous_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLIGHT_LEFT_BEG, RGBLIGHT_LEFT_NUM, HSV_SPRINGGREEN});

// The layer setup - exactly BATUHAN_RGBLIGHT_LAYER_COUNT layers
const rgblight_segment_t* const PROGMEM batuhan_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    batuhan_game_layer, // 0: _GAME
    batuhan_char_layer, // 1: _CHAR
    batuhan_symb_layer, // 2: _SYMB
    batuhan_numb_layer, // 3: _NUMB
    batuhan_navi_layer, // 4: _NAVI
    batuhan_func_layer, // 5: _FUNC
    batuhan_sett_layer, // 6: _SETT (formerly _KEYB)
    batuhan_mous_layer, // 7: _MOUS
    batuhan_musi_layer  // 8: _MUSI
);

// Compile-time validation that array size matches expected count
_Static_assert(sizeof(batuhan_rgb_layers) / sizeof(batuhan_rgb_layers[0]) == BATUHAN_RGBLIGHT_LAYER_COUNT,
               "RGB layer array size mismatch with BATUHAN_RGBLIGHT_LAYER_COUNT");

// Enable the LED switching layers
void keyboard_post_init_rgblight(void) {
    rgblight_layers = batuhan_rgb_layers;
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
    rgblight_set_layer_state(6, layer_state_cmp(state, _SETT));
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
