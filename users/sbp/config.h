/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once

/* CONFIG
 * Common hardware configuration accross my boards
 */
// Space saving
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
#ifndef NO_DEBUG
#   define NO_DEBUG
#endif

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#   define NO_PRINT
#endif

// Some of my own settings
# define HOUSEKEEPING_THROTTLE_INTERVAL_MS 250

// Split transport settings
#ifdef SPLIT_KEYBOARD
#   define SPLIT_TRANSPORT_MIRROR
#   define SPLIT_LAYER_STATE_ENABLE
#   define SPLIT_MODS_ENABLE
#   define SPLIT_TRANSACTION_IDS_USER RPC_ID_CONFIG_SYNC, RPC_ID_RUNTIME_SYNC, RPC_ID_KEYMAP_SYNC
#   define SPLIT_LED_STATE_ENABLE
#   ifdef WPM_ENABLE
#       define SPLIT_WPM_ENABLE
#   endif // WPM_ENABLE
#   ifdef RGBLIGHT_ENABLE
#       define RGBLIGHT_SPLIT
#   endif // RGBLIGHT_ENABLE
#   ifdef OLED_ENABLE
#       define SPLIT_OLED_ENABLE
#   endif // OLED_ENABLE
#endif // SPLIT_KEYBOARD

// Unicode entry mode
#ifdef UNICODEMAP_ENABLE
#   define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX
    // Adapt the unicode entry mode to dvorak
#   ifdef UNICODE_KEY_LNX
#   undef UNICODE_KEY_LNX
#   endif
#   define UNICODE_KEY_LNX LCTL(LSFT(KC_F))
#endif // UNICODEMAP_ENABLE

// Mousekey mode
#ifdef MOUSEKEY_ENABLE
#   define MK_COMBINED
#endif // MOUSEKEY_ENABLE

// Tap-hold settings
#define TAPPING_TERM 200
#define TAP_CODE_DELAY 20
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

// Backlight settings
#ifdef BACKLIGHT_ENABLE
#   define BACKLIGHT_BREATHING 3
#   define BACKLIGHT_LEVELS 3
#   define BACKLIGHT_DEFAULT_ON true
#   define BACKLIGHT_DEFAULT_BREATHING true
#   define BACKLIGHT_DEFAULT_LEVEL 2
#   define BREATHING_PERIOD 5
#endif // BACKLIGHT_ENABLE

// Audio definitions
#ifdef AUDIO_ENABLE
//#   define AUDIO_ENABLE_TONE_MULTIPLEXING
    // Make findable songs as defaults
#   ifdef HOROLOGY
#   define STARTUP_SONG    SONG(HOROLOGY)
#   endif
#   ifdef PEOPLE_VULTURES
#   define GOODBYE_SONG    SONG(PEOPLE_VULTURES)
#   endif
#   ifdef NONAGON_INFINITY
#   define MUSIC_ON_SONG   SONG(NONAGON_INFINITY)
#   endif
#   ifdef WAH_WAH
#   define MUSIC_OFF_SONG  SONG(WAH_WAH)
#   endif
    // Audio code expects these to be defined
#   ifdef BIG_FIG_WASP
#   define GAME_ON_SONG    SONG(BIG_FIG_WASP)
#   else
#   define GAME_ON_SONG    SONG(USSR_ANTHEM)
#   endif
#   ifdef POLYGONDWANALAND
#   define GAME_OFF_SONG   SONG(POLYGONDWANALAND)
#   else
#   define GAME_OFF_SONG   SONG(NOCTURNE_OP_9_NO_1)
#   endif
#endif // AUDIO_ENABLE

// OLED definitions
#ifdef OLED_ENABLE
    // Timeout does not work for split secondary board; i implemented it myself
#   define OLED_TIMEOUT 30000
    // Fade out the screen when timing out
#   define OLED_FADE_OUT
#   define OLED_FADE_OUT_INTERVAL 15
#endif // OLED_ENABLE

// For underglow rgb leds
#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL
#   define RGBLIGHT_MAX_LAYERS 9
#   define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
//  Enabled effects
#   define RGBLIGHT_EFFECT_ALTERNATING
#   define RGBLIGHT_EFFECT_BREATHING
#   define RGBLIGHT_EFFECT_RAINBOW_MOOD
#   define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#   define RGBLIGHT_EFFECT_STATIC_GRADIENT
#   define RGBLIGHT_EFFECT_TWINKLE
#endif // RGBLIGHT_ENABLE

// For per-key rgb leds
#ifdef RGB_MATRIX_ENABLE
//  Settings
#   define RGB_MATRIX_SLEEP
#   define RGB_MATRIX_KEYRELEASES
//  Defaults
#   define RGB_MATRIX_DEFAULT_ON  true
#   define RGB_MATRIX_DEFAULT_HUE 100
#   define RGB_MATRIX_DEFAULT_SAT 255
#   define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_TYPING_HEATMAP
#   define RGB_MATRIX_DEFAULT_SPD 127
//  Enabled effects
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#   define ENABLE_RGB_MATRIX_RAINDROPS
#   define ENABLE_RGB_MATRIX_PIXEL_FLOW
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#   define ENABLE_RGB_MATRIX_RIVERFLOW
//  Heatmap settings
#endif // RGB_MATRIX_ENABLE
