/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
// clang-format off
#pragma once
#include "quantum.h"

// Make it so that keymaps can use KEYMAP_SAFE_RANGE for custom keycodes
#ifdef KEYMAP_SAFE_RANGE
#define PLACEHOLDER_SAFE_RANGE KEYMAP_SAFE_RANGE
#else
#define PLACEHOLDER_SAFE_RANGE SAFE_RANGE
#endif

// Custom macro keycode ranges
enum userspace_custom_keycodes {
    B_SAFE = PLACEHOLDER_SAFE_RANGE,
#   ifdef ENCODER_ENABLE
    B_ENC0,
    B_ENC1,
#   endif // ENCODER_ENABLE
    B_LYCL,
    // Glyph keycodes
    G_FIRST,
    G_ALPHA = G_FIRST,  // First glyph
    G_BETA,
    G_GAMMA,
    G_DELTA,
    G_EPSLN,
    G_ZETA,
    G_ETA,
    G_THETA,
    G_LAMBD,
    G_MU,
    G_XI,
    G_PI,
    G_SIGMA,
    G_PHI,
    G_PSI,
    G_OMEGA,
    G_CGAMM,
    G_CDELT,
    G_CXI,
    G_CPI,
    G_CSIGM,
    G_CPHI,
    G_CPSI,
    G_COMEG,
    G_ELLIP,
    G_ANGST,
    G_BTCN,
    G_PLNCK,
    G_PGPK,
    G_LENY,
    G_TFLIP,
    G_LAST = G_TFLIP,  // Last glyph for range checking
    //use for keymap specific codes
    KEYMAP_SAFE_RANGE
};

// Mask these keycodes if required features are not enabled
#ifndef ENCODER_ENABLE
#   define B_ENC0 KC_NO
#   define B_ENC1 KC_NO
#endif // ENCODER_ENABLE

// MOD-tap definitions
// Base layer (Dvorak keycodes)
#define B_GUI_A MT(MOD_LGUI, DV_A)
#define B_ALT_O MT(MOD_LALT, DV_O)
#define B_CTL_E MT(MOD_LCTL, DV_E)
#define B_SFT_U MT(MOD_LSFT, DV_U)
#define B_GUI_9 MT(MOD_RGUI, DV_SCLN)
#define B_ALT_Q MT(MOD_RALT, DV_Q)
#define B_CTL_J MT(MOD_RCTL, DV_J)
#define B_SFT_K MT(MOD_RSFT, DV_K)
#define B_SFT_H MT(MOD_LSFT, DV_H)
#define B_CTL_T MT(MOD_LCTL, DV_T)
#define B_ALT_N MT(MOD_LALT, DV_N)
#define B_GUI_S MT(MOD_LGUI, DV_S)
#define B_SFT_M MT(MOD_RSFT, DV_M)
#define B_CTL_W MT(MOD_RCTL, DV_W)
#define B_ALT_V MT(MOD_RALT, DV_V)
#define B_GUI_Z MT(MOD_RGUI, DV_Z)

// Firmware Dvorak layer (QWERTY keycodes)
#define D_GUI_A MT(MOD_LGUI, KC_A)
#define D_ALT_O MT(MOD_LALT, KC_O)
#define D_CTL_E MT(MOD_LCTL, KC_E)
#define D_SFT_U MT(MOD_LSFT, KC_U)
#define D_GUI_9 MT(MOD_RGUI, KC_SCLN)
#define D_ALT_Q MT(MOD_RALT, KC_Q)
#define D_CTL_J MT(MOD_RCTL, KC_J)
#define D_SFT_K MT(MOD_RSFT, KC_K)
#define D_SFT_H MT(MOD_LSFT, KC_H)
#define D_CTL_T MT(MOD_LCTL, KC_T)
#define D_ALT_N MT(MOD_LALT, KC_N)
#define D_GUI_S MT(MOD_LGUI, KC_S)
#define D_SFT_M MT(MOD_RSFT, KC_M)
#define D_CTL_W MT(MOD_RCTL, KC_W)
#define D_ALT_V MT(MOD_RALT, KC_V)
#define D_GUI_Z MT(MOD_RGUI, KC_Z)

// Layer long-tap switches
#define B_SET_DEL LT(_SETT, KC_DEL)
#define B_NAV_TAB LT(_NAVI, KC_TAB)
#define B_SYM_SPC LT(_SYMB, KC_SPC)
#define B_NUM_ENT LT(_NUMB, KC_ENT)
#define B_FUN_ESC LT(_FUNC, KC_ESC)
#define B_MOU_BSP LT(_MOUS, KC_BSPC)

// Layer switches
#define B_CHAR OSL(_CHAR)
#define B_GAME TG(_GAME)
#define B_DVOR TG(_DVOR)

// Audio keys
#ifdef AUDIO_ENABLE
#   define MU_REC   KC_LCTL
#   define MU_STOP  KC_LALT
#   define MU_PLAY  KC_LGUI
#   define MU_FAST  KC_UP
#   define MU_SLOW  KC_DOWN
#   define MU_MASK  KC_A
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
#   define MU_SLOW  KC_NO
#   define MU_MASK  KC_NO
#   define MU_TEMP  KC_NO
#endif // AUDIO_ENABLE
