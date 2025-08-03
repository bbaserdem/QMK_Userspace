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
    BB_SAFE = PLACEHOLDER_SAFE_RANGE,
    // Double entry macros
    DBL_ANG,
    DBL_PAR,
    DBL_CBR,
    DBL_BRC,
    // Macro key
    BB_PGPK,
    // Undo/Redo
    BB_UNDO,
    BB_REDO,
    // Unicode strings
#   ifdef UNICODEMAP_ENABLE
    BB_LENY,
    BB_TABL,
    TR_FLAG,
#   endif // UNICODEMAP_ENABLE
    // Encoder buttons
#   ifdef ENCODER_ENABLE
    BB_ENC0,
    BB_ENC1,
#   endif // ENCODER_ENABLE
    // Oled editor
#   ifdef OLED_ENABLE
    BB_OLED,
#   endif // OLED_ENABLE
    //use for keymap specific codes
    KEYMAP_SAFE_RANGE
};

// Mask these keycodes if required features are not enabled
#ifndef UNICODEMAP_ENABLE
#define BB_LENY KC_NO
#define BB_TABL KC_NO
#define TR_FLAG KC_NO
#endif // UNICODEMAP_ENABLE
#ifndef ENCODER_ENABLE
#define BB_ENC0 KC_NO
#define BB_ENC1 KC_NO
#endif // ENCODER_ENABLE

// Audio keys
#ifdef AUDIO_ENABLE
#define MU_REC  KC_LCTL
#define MU_STOP KC_LALT
#define MU_PLAY KC_LGUI
#define MU_FAST KC_UP
#define MU_SLOW KC_DOWN
#define MU_MASK KC_A
#define BB_SND  MU_ON
#define MU_MOD  MU_NEXT
#ifdef TAP_DANCE_ENABLE
#define MU_TEMP TD(TD_AUDIO_TEMPO)
#else // TAP_DANCE_ENABLE
#define MU_TEMP KC_DOWN
#endif // TAP_DANCE_ENABLE
#else // AUDIO_ENABLE
#define MU_REC  KC_NO
#define MU_STOP KC_NO
#define MU_PLAY KC_NO
#define MU_FAST KC_NO
#define MU_TEMP KC_NO
#define MU_SLOW KC_NO
#define MU_MASK KC_NO
#define BB_SND  KC_MUTE
#define MU_MOD  KC_NO
#endif // AUDIO_ENABLE

// Unicode single keys
#ifdef UNICODEMAP_ENABLE
#define TR_ACIR UP(LOW_A_CIRC, UPC_A_CIRC )
#define TR_CCED UP(LOW_C_CEDI, UPC_C_CEDI )
#define TR_GBRE UP(LOW_G_BREV, LOW_G_BREV )
#define TR_ICIR UP(LOW_I_CIRC, LOW_I_CIRC )
#define TR_I_NO UP(LOW_I_DOTL, LOW_I_DOTL )
#define TR_IDOT UP(LOW_I_DOTT, LOW_I_DOTT )
#define TR_ODIA UP(LOW_O_DIAE, LOW_O_DIAE )
#define TR_SCED UP(LOW_S_CEDI, LOW_S_CEDI )
#define TR_UCIR UP(LOW_U_CIRC, LOW_U_CIRC )
#define TR_UDIA UP(LOW_U_DIAE, LOW_U_DIAE )
#define GR_ALP  UP(LOW_ALPHA,  UPC_ALPHA  )
#define GR_BET  UP(LOW_BETA,   UPC_BETA   )
#define GR_GAM  UP(LOW_GAMMA,  UPC_GAMMA  )
#define GR_DEL  UP(LOW_DELTA,  UPC_DELTA  )
#define GR_EPS  UP(LOW_EPSILON,UPC_EPSILON)
#define GR_ZET  UP(LOW_ZETA,   UPC_ZETA   )
#define GR_ETA  UP(LOW_ETA,    UPC_ETA    )
#define GR_THE  UP(LOW_THETA,  UPC_THETA  )
#define GR_IOT  UP(LOW_IOTA,   UPC_IOTA   )
#define GR_KAP  UP(LOW_KAPPA,  UPC_KAPPA  )
#define GR_LAM  UP(LOW_LAMBDA, UPC_LAMBDA )
#define GR_MU   UP(LOW_MU,     UPC_MU     )
#define GR_NU   UP(LOW_NU,     UPC_NU     )
#define GR_XI   UP(LOW_XI,     UPC_XI     )
#define GR_OMI  UP(LOW_OMICRON,UPC_OMICRON)
#define GR_PI   UP(LOW_PI,     UPC_PI     )
#define GR_RHO  UP(LOW_RHO,    UPC_RHO    )
#define GR_SIG  UP(LOW_SIGMA,  UPC_SIGMA  )
#define GR_TAU  UP(LOW_TAU,    UPC_TAU    )
#define GR_UPS  UP(LOW_UPSILON,UPC_UPSILON)
#define GR_PHI  UP(LOW_PHI,    UPC_PHI    )
#define GR_CHI  UP(LOW_CHI,    UPC_CHI    )
#define GR_PSI  UP(LOW_PSI,    UPC_PSI    )
#define GR_OME  UP(LOW_OMEGA,  UPC_OMEGA  )
#define BB_ELLI UM(ELLIPSIS)
#define BB_PLNK UM(PLANCK_CON)
#define BB_ANGS UM(ANGSTROM)
#define BB_BITC UM(BITCOIN)
#else // UNICODEMAP_ENABLE
#define TR_ACIR KC_A
#define TR_CCED KC_C
#define TR_GBRE KC_G
#define TR_ICIR KC_I
#define TR_I_NO KC_I
#define TR_IDOT KC_I
#define TR_ODIA KC_O
#define TR_SCED KC_S
#define TR_UCIR KC_U
#define TR_UDIA KC_U
#define GR_ALP  KC_NO
#define GR_BET  KC_NO
#define GR_GAM  KC_NO
#define GR_DEL  KC_NO
#define GR_EPS  KC_NO
#define GR_ZET  KC_NO
#define GR_ETA  KC_NO
#define GR_THE  KC_NO
#define GR_IOT  KC_NO
#define GR_KAP  KC_NO
#define GR_LAM  KC_NO
#define GR_MU   KC_NO
#define GR_NU   KC_NO
#define GR_XI   KC_NO
#define GR_OMI  KC_NO
#define GR_PI   KC_NO
#define GR_RHO  KC_NO
#define GR_SIG  KC_NO
#define GR_TAU  KC_NO
#define GR_UPS  KC_NO
#define GR_PHI  KC_NO
#define GR_CHI  KC_NO
#define GR_PSI  KC_NO
#define GR_OME  KC_NO
#define BB_ELLI KC_NO
#define BB_PLNK KC_NO
#define BB_ANGS KC_NO
#define BB_BITC KC_NO
#endif // UNICODEMAP_ENABLE
