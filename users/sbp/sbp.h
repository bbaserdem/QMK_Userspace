/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "keymap_dvorak.h"

// Import layout
#include "sbp-macros.h"
#include "sbp-keycodes.h"
#include "sbp-layout.h"

// Macros to use, this has base level code so not affected by enabled features
#include "sbp-macro.h"
// Audio from onboard speakers
#ifdef AUDIO_ENABLE

#include "sbp-audio.h"
#endif // AUDIO_ENABLE

// Underglow light using rgb LEDs
#ifdef RGBLIGHT_ENABLE
#include "sbp-rgb-light.h"
#endif // RGBLIGHT_ENABLE

// Keycap light using rgb LEDs
#ifdef RGB_MATRIX_ENABLE
#include "sbp-rgb-matrix.h"
#endif // RGB_MATRIX_ENABLE

// Rotary encoder
#ifdef ENCODER_ENABLE
#include "sbp-encoder.h"
#endif // ENCODER_ENABLE

// Oled screen
#ifdef OLED_ENABLE
#include "sbp-oled.h"
#endif // OLED_ENABLE

// Structures to keep runtime/eeprom info on states.
// For RGB runtime info, might be unneccessary now
typedef union {
    uint32_t raw;
    struct {
        bool rgb_sleep;
    };
} userspace_runtime_t;

// For encoder state
typedef union {
    uint32_t raw;
    struct {
        uint8_t e0base  :4; // ( 4:0) The encoder state on most layers; regular function
        uint8_t e1base  :4; // ( 8:1) 9 states for this; 4 bits
        uint8_t e0point :2; // (10:1) The encoder state on mouse layer; moves pointer
        uint8_t e1point :2; // (12:1) 4 states for this; 2 bits
        uint8_t e0rgb   :4; // (16:2) The encoder state on media layer; controls light
        uint8_t e1rgb   :4; // (20:2) 5 states for this; 3 bits but 4 is better
        uint8_t layout  :2; // (22:2) Stores keymap layout; 3 states is good on 2 bits
        uint16_t       :10; // (32:3) Padding here, free space for 10 more bits
    };
} userspace_config_t;

// Broadcast us, so everyone else can use us
extern userspace_runtime_t  userspace_runtime;
extern userspace_config_t   userspace_config;

// Function definitions that can be accessed through keymap level code

// Runs before all initialization
void keyboard_pre_init_keymap(void);
// For code that launches once midway through initialization
void matrix_init_keymap(void);
// For code that launches after initialization is finished.
void keyboard_post_init_keymap(void);
// These will be delegated to keymap specific stuff (weak definition)
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
// This code runs on every tick
void matrix_scan_keymap(void);
// This code runs after every layer change
layer_state_t layer_state_set_keymap(layer_state_t state);
// This code runs when the default layer changes
layer_state_t default_layer_state_set_keymap (layer_state_t state);
// Some code that runs every now and then
void housekeeping_task_user(void);
// This code runs to set LED states
void led_set_keymap(uint8_t usb_led);
// For code that runs on suspend
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
// For code that runs on powerdown
void shutdown_keymap(void);
