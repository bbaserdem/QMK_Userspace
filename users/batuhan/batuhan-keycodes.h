/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once

// Make it so that keymaps can use KEYMAP_SAFE_RANGE for custom keycodes
#ifdef KEYMAP_SAFE_RANGE
#define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
#define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

// Custom macro keycode ranges
enum userspace_custom_keycodes {
    // Safe stuff
    B_SAFE = PLACEHOLDER_SAFE_RANGE,
    // Macro key
    B_PGPK,
    // Encoder buttons
#   ifdef ENCODER_ENABLE
    B_ENC0,
    B_ENC1,
#   endif // ENCODER_ENABLE
    // Oled editor
    B_OLED,
    //use for keymap specific codes
    KEYMAP_SAFE_RANGE
};

// Mask these keycodes if required features are not enabled
#ifndef ENCODER_ENABLE
#   define B_ENC0 KC_NO
#   define B_ENC1 KC_NO
#endif // ENCODER_ENABLE

// Audio keys
#ifdef AUDIO_ENABLE
#   define MU_REC   KC_LCTL
#   define MU_STOP  KC_LALT
#   define MU_PLAY  KC_LGUI
#   define MU_FAST  KC_UP
#   define MU_SLOW  KC_DOWN
#   define MU_MASK  KC_A
#   define B_SND    MU_ON
#   define MU_MOD   MU_NEXT
#   ifdef TAP_DANCE_ENABLE
#       define MU_TEMP TD(TD_AUDIO_TEMPO)
#   else // TAP_DANCE_ENABLE
#       define MU_TEMP KC_DOWN
#   endif // TAP_DANCE_ENABLE
#else // AUDIO_ENABLE
#   define MU_REC   KC_NO
#   define MU_STOP  KC_NO
#   define MU_PLAY  KC_NO
#   define MU_FAST  KC_NO
#   define MU_TEMP  KC_NO
#   define MU_SLOW  KC_NO
#   define MU_MASK  KC_NO
#   define B_SND    KC_MUTE
#   define MU_MOD   KC_NO
#endif // AUDIO_ENABLE

// Unicode keys will be implemented later
// Placeholder definitions for now
