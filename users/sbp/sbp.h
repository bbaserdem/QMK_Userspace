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
#include "sbp-macros.h"
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
typedef struct __attribute__((packed)) {
    uint8_t e0base  :4; // ( 4:0) The encoder state on most layers; regular function
    uint8_t e1base  :4; // ( 8:1) 9 states for this; 4 bits
    uint8_t e0point :2; // (10:1) The encoder state on mouse layer; moves pointer
    uint8_t e1point :2; // (12:1) 4 states for this; 2 bits
    uint8_t e0rgb   :4; // (16:2) The encoder state on media layer; controls light
    uint8_t e1rgb   :4; // (20:2) 5 states for this; 3 bits but 4 is better
    uint8_t layout  :2; // (22:2) Stores keymap layout; 3 states is good on 2 bits
    uint16_t       :10; // (32:3) Padding here, free space for 10 more bits
} userspace_config_bits_t;

typedef union {
    uint32_t raw;
    userspace_config_bits_t bits;
} userspace_config_t;

// Compile-time size checks for data structure portability
_Static_assert(sizeof(userspace_config_t) == 4, "userspace_config_t size mismatch");
_Static_assert(sizeof(userspace_runtime_t) == 4, "userspace_runtime_t size mismatch");

// Encoder mode constants
enum encoder_modes_base {
    ENC_MODE_VOLUME = 0,
    ENC_MODE_SONG = 1,
    ENC_MODE_SINK = 2,
    ENC_MODE_SRC_VOL = 3,
    ENC_MODE_SOURCE = 4,
    ENC_MODE_ARROW_LR = 5,
    ENC_MODE_ARROW_UD = 6,
    ENC_MODE_PAGE_UD = 7,
    ENC_MODE_ERASE = 8,
    ENC_MODE_BASE_COUNT = 9
};

enum encoder_modes_pointer {
    ENC_MODE_LATERAL = 0,
    ENC_MODE_VERTICAL = 1,
    ENC_MODE_SCR_VER = 2,
    ENC_MODE_SCR_LAT = 3,
    ENC_MODE_POINTER_COUNT = 4
};

enum encoder_modes_rgb {
    ENC_MODE_ANI_MODE = 0,
    ENC_MODE_HUE = 1,
    ENC_MODE_SATURATION = 2,
    ENC_MODE_VALUE = 3,
    ENC_MODE_SPEED = 4,
    ENC_MODE_RGB_COUNT = 5
};

// Broadcast us, so everyone else can use us
extern userspace_runtime_t  userspace_runtime;
extern userspace_config_t   userspace_config;

// Macro to reduce boilerplate for weak function definitions
#define SBP_WEAK_HOOK_VOID(name, params) \
    __attribute__((weak)) void name##_keymap params; \
    __attribute__((weak)) void name##_keymap params { } \
    void name##_user params

#define SBP_WEAK_HOOK_RETURN(name, rettype, params, default_return) \
    __attribute__((weak)) rettype name##_keymap params; \
    __attribute__((weak)) rettype name##_keymap params { return default_return; } \
    rettype name##_user params

// Function definitions that can be accessed through keymap level code

// EEPROM wear leveling function
void mark_config_dirty(void);

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
bool shutdown_keymap(bool jump_to_bootloader);
