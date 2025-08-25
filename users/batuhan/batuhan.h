/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "keymap_dvorak.h"

// Import layout
#include "batuhan-keycodes.h"
#include "batuhan-layout.h"

// Glyphs and unicode handling
#include "batuhan-glyphs.h"

// Audio from onboard speakers
#ifdef AUDIO_ENABLE
#include "batuhan-audio.h"
#endif // AUDIO_ENABLE

// Underglow light using rgb LEDs
#ifdef RGBLIGHT_ENABLE
#include "batuhan-rgb-light.h"
#endif // RGBLIGHT_ENABLE

// Keycap light using rgb LEDs
#ifdef RGB_MATRIX_ENABLE
#include "batuhan-rgb-matrix.h"
#endif // RGB_MATRIX_ENABLE

// Rotary encoder - include early for bit definitions
#ifdef ENCODER_ENABLE
#include "batuhan-encoder.h"
#endif // ENCODER_ENABLE

// Oled screen
// #ifdef OLED_ENABLE
// #include "batuhan-oled.h"
// #endif // OLED_ENABLE

// Structures to keep runtime/eeprom info on states.
// For RGB runtime info, might be unneccessary now
typedef union {
    uint32_t raw;
    struct {
        bool rgb_sleep;
    };
} userspace_runtime_t;

// For custom state handling with eeprom
typedef struct __attribute__((packed)) {
#ifdef ENCODER_ENABLE
    // Encoder 0 (left/first encoder) states
    uint8_t e0base  :ENC_BASE_BITS;    // Base layer mode
    uint8_t e0point :ENC_POINTER_BITS; // Mouse layer mode
    uint8_t e0rgb   :ENC_RGB_BITS;     // RGB layer mode

    // Encoder 1 (right/second encoder) states
    uint8_t e1base  :ENC_BASE_BITS;    // Base layer mode
    uint8_t e1point :ENC_POINTER_BITS; // Mouse layer mode
    uint8_t e1rgb   :ENC_RGB_BITS;     // RGB layer mode
#endif // ENCODER_ENABLE

    // Other configuration
    uint8_t layout  :2; // Keymap layout selection (up to 4 layouts)

    // Bit usage automatically calculated from encoder mode counts
    // If encoder disabled, only layout uses 2 bits
} userspace_config_bits_t;

typedef union {
    uint32_t raw;
    userspace_config_bits_t bits;
} userspace_config_t;

// Compile-time size checks for data structure portability
_Static_assert(sizeof(userspace_config_t) == 4, "userspace_config_t size mismatch");
_Static_assert(sizeof(userspace_runtime_t) == 4, "userspace_runtime_t size mismatch");

// Layout definitions
enum layout_types {
    LAYOUT_DVORAK = 0,
    LAYOUT_TURKISHF = 1,
    LAYOUT_QWERTY = 2,
    LAYOUT_RESERVED = 3
};

// Broadcast us, so everyone else can use us
extern userspace_runtime_t  userspace_runtime;
extern userspace_config_t   userspace_config;

// Macro to reduce boilerplate for weak function definitions
#define BATUHAN_WEAK_HOOK_VOID(name, params) \
    __attribute__((weak)) void name##_keymap params; \
    __attribute__((weak)) void name##_keymap params { } \
    void name##_user params

#define BATUHAN_WEAK_HOOK_RETURN(name, rettype, params, default_return) \
    __attribute__((weak)) rettype name##_keymap params; \
    __attribute__((weak)) rettype name##_keymap params { return default_return; } \
    rettype name##_user params

// Function definitions that can be accessed through keymap level code

// EEPROM wear leveling function
void mark_config_dirty(void);

// Cycle through layouts
void cycle_layout(void);

// Get current layout name for display
const char* get_layout_name(void);

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
