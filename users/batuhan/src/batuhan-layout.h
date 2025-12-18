/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
// clang-format off
#pragma once

// Layer definitions
enum userspace_layers {
    _BASE = 0,  // Base Dvorak layer with home row mods
    _DVOR,      // Firmware Dvorak (uses QWERTY keycodes)
    _GAME,      // Gaming layer (no tap-hold)
    _CHAR,      // Unicode characters layer
    _SYMB,      // Symbol layer (right side)
    _NUMB,      // Number layer (left side)
    _NAVI,      // Navigation layer (right side)
    _FUNC,      // Function keys (left side)
    _SETT,      // Settings layer (right side)
    _MOUS,      // Mouse layer (left side)
    _MUSI,      // Music layer
};

// Use 7 wide characters for keymaps, to keep things aligned with 4 tabs
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// These defines allow multiple multi-parameter definitions to expand
// for these boards
#define LAYOUT_wrapper(...)             LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...)  LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_ortho_5x15_wrapper(...)  LAYOUT_ortho_5x15(__VA_ARGS__)
#define LAYOUT_ortho_3x10_wrapper(...)  LAYOUT_ortho_3x10(__VA_ARGS__)
#define LAYOUT_split_3x6_3_wrapper(...) LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_split_3x5_3_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

// Masks
#define ___1___ _______
#define ___2___ _______,_______
#define ___3___ _______,_______,_______
#define ___4___ _______,_______,_______,_______
#define ___5___ _______,_______,_______,_______,_______
#define ___6___ _______,_______,_______,_______,_______,_______
#define xxx1xxx KC_NO
#define xxx2xxx KC_NO,  KC_NO
#define xxx3xxx KC_NO,  KC_NO,  KC_NO
#define xxx4xxx KC_NO,  KC_NO,  KC_NO,  KC_NO
#define xxx5xxx KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
#define xxx6xxx KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
#define B_DVOR TG(_DVOR)

/* Depending on how the layouts change with language; the keys are shown as;
 * ┌────────────────────────────────────────────────┐
 * │AltGr       -none-      Shift       Shift+AltGr │
 * └────────────────────────────────────────────────┘
 * If there is an exclamation mark; it indicates a dead key on this map.
 */

/* Base layout - DVORAK
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │ / ? │ ' " │ , < │ . > │  P  │  Y  │   │  F  │  G  │  C  │  R  │  L  │ = + │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │ \ | │  A  │  O  │  E  │  U  │  I  │   │  D  │  H  │  T  │  N  │  S  │ - _ │
 * ├──⌘──┼──⌥──┼──⌃──┼──⇧──┼─────┼─────┤   ├─────┼──⇧──┼──⌃──┼──⌥──┼──⌘──┼─────┤
 * │ < > │ ; : │  Q  │  J  │  K  │  X  │   │  B  │  M  │  W  │  V  │  Z  │ ` ~ │
 * └─────┴─────┴──⌤──┼─────┼─────┼─────┤   ├─────┼─────┼─────┼──⌤──┴─────┴─────┘
 *                   │ Del │ Tab │ Spc │   │ Ent │ Esc │ Bks │
 *                   └─set─┴─nav─┴─sym─┘   └─num─┴─fun─┴─mou─┘
 *
 * QWERTY layout not implemented - using dvorak keycodes for now
 * See README.md for reference
 *
 * TURKISH F
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │◌̈ Q ◌̊│@ F  │  G  │  Ğ  │¶ I  │ô O Ô│   │¥ D  │® R  │  N  │° H  │£ P  │~ W ◌̃│
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │` X ◌̀│  U  │  İ  │€ E  │â A Â│û Ü Û│   │₺ T  │  K  │µ M  │  L  │´ Y ◌́│# Ş ◌̌│
 * ├──⌘──┼──⌥──┼──⌃──┼──⇧──┼─────┼─────┤   ├─────┼──⇧──┼──⌃──┼──⌥──┼──⌘──┼─────┤
 * │|< >¦│« J <│  Ö  │" V  │¢ C ©│" Ç  │   │  Z  │§ S  │× B  │÷. :◌̇│·, ; │¬+ *±│
 * └─────┴─────┴──⌤──┼─────┼─────┼─────┤   ├─────┼─────┼─────┼──⌤──┴─────┴─────┘
 *                   │ Del │ Tab │ Spc │   │ Ent │ Esc │ Bks │
 *                   └─set─┴─nav─┴─sym─┘   └─num─┴─fun─┴─mou─┘
 * The thing about this layout is that these will fit most boards I have.
 */
// Row 0; number row
#define _BL0_1_ DV_LBRC
#define _BL0_5_ KC_1,   KC_2,   KC_3,   KC_4,   KC_5
#define _BR0_5_ KC_6,   KC_7,   KC_8,   KC_9,   KC_0
#define _BR0_1_ DV_RBRC
#define _BL0_6_ _BL0_1_,_BL0_5_
#define _BR0_6_ _BR0_5_,_BR0_1_
// Row 1
#define _BL1_1_ DV_SLSH
#define _BL1_5_ DV_QUOT,DV_COMM,DV_DOT, DV_P,   DV_Y
#define _BR1_5_ DV_F,   DV_G,   DV_C,   DV_R,   DV_L
#define _BR1_1_ DV_EQL
#define _BL1_6_ _BL1_1_,_BL1_5_
#define _BR1_6_ _BR1_5_,_BR1_1_
// Row 2
#define _BL2_1_ DV_BSLS
#define _BL2_5_ B_GUI_A,B_ALT_O,B_CTL_E,B_SFT_U,DV_I
#define _BR2_5_ DV_D,   B_SFT_H,B_CTL_T,B_ALT_N,B_GUI_S
#define _BR2_1_ DV_MINS
#define _BL2_6_ _BL2_1_,_BL2_5_
#define _BR2_6_ _BR2_5_,_BR2_1_
// Row 3
#define _BL3_1_ KC_NUBS
#define _BL3_5_ B_GUI_9,B_ALT_Q,B_CTL_J,B_SFT_K,DV_X
#define _BR3_5_ DV_B,   B_SFT_M,B_CTL_W,B_ALT_V,B_GUI_Z
#define _BR3_1_ DV_GRV
#define _BL3_6_ _BL3_1_,_BL3_5_
#define _BR3_6_ _BR3_5_,_BR3_1_
// Row 4
#define _BL4_3_ B_SET_DEL,B_NAV_TAB,B_SYM_SPC
#define _BR4_3_ B_NUM_ENT,B_FUN_ESC,B_MOU_BSP

/* Firmware Dvorak layer - using QWERTY keycodes
 * Same as base layout but firmware handles Dvorak conversion
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │ / ? │ ' " │ , < │ . > │  P  │  Y  │   │  F  │  G  │  C  │  R  │  L  │ = + │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │ \ | │  A  │  O  │  E  │  U  │  I  │   │  D  │  H  │  T  │  N  │  S  │ - _ │
 * ├──⌘──┼──⌥──┼──⌃──┼──⇧──┼─────┼─────┤   ├─────┼──⇧──┼──⌃──┼──⌥──┼──⌘──┼─────┤
 * │ < > │ ; : │  Q  │  J  │  K  │  X  │   │  B  │  M  │  W  │  V  │  Z  │ ` ~ │
 * └─────┴─────┴──⌤──┼─────┼─────┼─────┤   ├─────┼─────┼─────┼──⌤──┴─────┴─────┘
 *                   │ Del │ Tab │ Spc │   │ Ent │ Esc │ Bks │
 *                   └─set─┴─nav─┴─sym─┘   └─num─┴─fun─┴─mou─┘
 */
// Row 0; number row
#define _DL0_1_ KC_LBRC
#define _DL0_5_ KC_1,   KC_2,   KC_3,   KC_4,   KC_5
#define _DR0_5_ KC_6,   KC_7,   KC_8,   KC_9,   KC_0
#define _DR0_1_ KC_RBRC
#define _DL0_6_ _BL0_1_,_BL0_5_
#define _DR0_6_ _BR0_5_,_BR0_1_
// Row 1
#define _DL1_1_ KC_SLSH
#define _DL1_5_ KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y
#define _DR1_5_ KC_F,   KC_G,   KC_C,   KC_R,   KC_L
#define _DR1_1_ KC_EQL
#define _DL1_6_ _DL1_1_,_DL1_5_
#define _DR1_6_ _DR1_5_,_DR1_1_
// Row 2
#define _DL2_1_ KC_BSLS
#define _DL2_5_ D_GUI_A,D_ALT_O,D_CTL_E,D_SFT_U,KC_I
#define _DR2_5_ KC_D,   D_SFT_H,D_CTL_T,D_ALT_N,D_GUI_S
#define _DR2_1_ KC_MINS
#define _DL2_6_ _DL2_1_,_DL2_5_
#define _DR2_6_ _DR2_5_,_DR2_1_
// Row 3
#define _DL3_1_ KC_NUBS
#define _DL3_5_ D_GUI_9,D_ALT_Q,D_CTL_J,D_SFT_K,KC_X
#define _DR3_5_ KC_B,   D_SFT_M,D_CTL_W,D_ALT_V,D_GUI_Z
#define _DR3_1_ KC_EQL
#define _DL3_6_ _DL3_1_,_DL3_5_
#define _DR3_6_ _DR3_5_,_DR3_1_
// Row 4
#define _DL4_3_ B_SET_DEL,B_NAV_TAB,B_SYM_SPC
#define _DR4_3_ B_NUM_ENT,B_FUN_ESC,B_MOU_BSP

/* Game layer - tap-hold disabled for gaming
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │ Tab │  Q  │  W  │  E  │  R  │  T  │   │ F1  │ F2  │PgDn │  ↑  │PgUp │ ` ~ │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │Shift│  A  │  S  │  D  │  F  │  G  │   │ F6  │ F7  │  ←  │  ↓  │  →  │Shift│
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │Ctrl │  Z  │  X  │  C  │  V  │  B  │   │ F10 │ F11 │ F12 │ , < │ . > │ Alt │
 * └─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
 *                   │ Esc │Enter│Space│   │Enter│Space│EXIT │
 *                   └─────┴─────┴─────┘   └─────┴─────┴─────┘
 */
// Row 1
#define _GL1_1_ KC_TAB
#define _GL1_5_ KC_Q,   KC_W,   KC_E,   KC_R,   KC_T
#define _GR1_5_ KC_F1,  KC_F2,  KC_PGDN,KC_UP,  KC_PGDN
#define _GR1_1_ KC_GRV
#define _GL1_6_ _GL1_1_,_GL1_5_
#define _GR1_6_ _GR1_5_,_GR1_1_
// Row 2
#define _GL2_1_ KC_LSFT
#define _GL2_5_ KC_A,   KC_S,   KC_D,   KC_F,   KC_G
#define _GR2_5_ KC_F6,  KC_F7,  KC_LEFT,KC_DOWN,KC_RGHT
#define _GR2_1_ KC_RSFT
#define _GL2_6_ _GL2_1_,_GL2_5_
#define _GR2_6_ _GR2_5_,_GR2_1_
// Row 3
#define _GL3_1_ KC_RCTL
#define _GL3_5_ KC_Z,   KC_X,   KC_C,   KC_V,   KC_B
#define _GR3_5_ KC_F10, KC_F11, KC_F12, KC_COMM,KC_DOT
#define _GR3_1_ KC_LALT
#define _GL3_6_ _GL3_1_,_GL3_5_
#define _GR3_6_ _GR3_5_,_GR3_1_
// Row 4
#define _GL4_3_ KC_ESC, KC_ENT, KC_SPC
#define _GR4_3_ KC_ENT, KC_SPC, B_GAME

/* Extra characters layer
 * This is accessed via unicode; so IBus only.
 *┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
 *│     │  α  │  β  │  γ  │  δ  │  ε  │   │  ζ  │  η  │  θ  │  λ  │  μ  │     │
 *├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 *│Leny │  Å  │  ₿  │  Γ  │  Δ  │  Ω  │   │  Ξ  │  Π  │  Σ  │  Φ  │  Ψ  │TFlip│
 *├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 *│     │  ℏ  │ ... │ PGP │     │  ω  │   │  ξ  │  π  │  σ  │  φ  │  ψ  │     │
 *└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
 *                  │EXIT │     │     │   │     │     │Game │
 *                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
 *
 */
// Row 1 - Greek letters (lowercase)
#define _CL1_1_ KC_NO
#define _CL1_5_ G_ALPHA,G_BETA, G_GAMMA,G_DELTA,G_EPSLN
#define _CR1_5_ G_ZETA, G_ETA,  G_THETA,G_LAMBD,G_MU
#define _CR1_1_ KC_NO
#define _CL1_6_ _CL1_1_,_CL1_5_
#define _CR1_6_ _CR1_5_,_CR1_1_
// Row 2 - More Greek and special
#define _CL2_1_ G_LENY
#define _CL2_5_ G_ANGST,G_BTCN, G_CGAMM,G_CDELT,G_COMEG
#define _CR2_5_ G_CXI,  G_CPI,  G_CSIGM,G_CPHI, G_CPSI
#define _CR2_1_ G_TFLIP
#define _CL2_6_ _CL2_1_,_CL2_5_
#define _CR2_6_ _CR2_5_,_CR2_1_
// Row 3 - Capital Greek and special characters
#define _CL3_1_ KC_NO
#define _CL3_5_ G_PLNCK,G_ELLIP,G_PGPK, KC_NO,  G_OMEGA
#define _CR3_5_ G_XI,   G_PI,   G_SIGMA,G_PHI,  G_PSI
#define _CR3_1_ KC_NO
#define _CL3_6_ _CL3_1_,_CL3_5_
#define _CR3_6_ _CR3_5_,_CR3_1_
// Row 4
#define _CL4_3_ KC_ESC, KC_RSFT,G_PGPK
#define _CR4_3_ B_DVOR, KC_LSFT,B_GAME

/* Symbols layer
 *  This layer is stable across keymap emulations
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  `  │  {  │  }  │  /  │  =  │  @  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │  ~  │  [  │  ]  │  ?  │  +  │  -  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │  !  │  (  │  )  │  \  │  |  │  _  │
 * ├─────┼─────┼─────┼─────┴─────┴─────┘
 * │  #  │  &  │  $  │
 * └─────┴─────┴─────┘
 */
// Row 1
#define _SY1_5_ DV_GRV, DV_LCBR,DV_RCBR,DV_SLSH,DV_EQL
#define _SY1_1_ _______
#define _SY1_6_ _SY1_5_,_SY1_1_
// Row 2
#define _SY2_5_ DV_TILD,DV_LBRC,DV_RBRC,DV_QUES,DV_PLUS
#define _SY2_1_ _______
#define _SY2_6_ _SY2_5_,_SY2_1_
// Row 3
#define _SY3_5_ B_CHAR, DV_LPRN,DV_RPRN,DV_BSLS,DV_PIPE
#define _SY3_1_ _______
#define _SY3_6_ _SY3_5_,_SY3_1_
// Row 4
#define _SY4_3_ KC_ENT, KC_ESC, KC_BSPC

/* Numbers layer
 *  This layer contains numbers and the associated symbols.
 * DVORAK
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │ \ | │ 7 & │ 8 * │ 9 ( │ 0 ) │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ / ? │ 4 $ │ 5 % │ 6 ^ │ [ { │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ = + │ 1 ! │ 2 @ │ 3 # │ ] } │
 * └─────┴─────┼─────┼─────┼─────┤
 *             │ < > │ ` ~ │ - _ │
 *             └─────┴─────┴─────┘
 * Turkish F
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │` X ◌̀│{7 ' │[8 ( │]9 )±│}0 =°│
 * ├─────┼─────┼─────┼─────┼─────┤
 * │◌̈ Q ◌̊│¼4 $ │½5 %⅜│¾6 & │\/ ?¿│
 * ├─────┼─────┼─────┼─────┼─────┤
 * │~ W ◌̃│¹1 !¡│²2 " │#3 ^³│|- _ │
 * └─────┴─────┼─────┼─────┼─────┤
 *             │ < > │¬+ *±│# Ş ◌̌│
 *             └─────┴─────┴─────┘
 */
// Row 1
#define _NU1_1_ _______
#define _NU1_5_ KC_BSLS,KC_7,   KC_8,   KC_9,   KC_0
#define _NU1_6_ _NU1_1_,_NU1_5_
// Row 2
#define _NU2_1_ _______
#define _NU2_5_ KC_LBRC,KC_4,   KC_5,   KC_6,   KC_MINS
#define _NU2_6_ _NU2_1_,_NU2_5_
// Row 3
#define _NU3_1_ _______
#define _NU3_5_ KC_RBRC,KC_1,   KC_2,   KC_3,   KC_EQL
#define _NU3_6_ _NU3_1_,_NU3_5_
// Row 4
#define _NU4_3_ KC_NUBS,KC_GRV, KC_QUOT

/* Navigation layer
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │  ⏮  │  ⏯  │  ⏭  │  ▲  │  ⎙  │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │  ⏹  │  ⇞  │  ◀  │  ▼  │  ▶  │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │  ⇱  │  ⇟  │  ⇲  │  ⎀  │  ⇪  │
 * ├─────┼─────┼─────┼─────┴─────┘
 * │ Ent │ Esc │ Bks │
 * └─────┴─────┴─────┘
 */
#define _NA1_5_ KC_MPRV,KC_MPLY,KC_MNXT,KC_UP,  KC_PSCR
#define _NA1_6_ _NA1_5_,KC_NO
#define _NA2_5_ KC_MSTP,KC_PGUP,KC_LEFT,KC_DOWN,KC_RGHT
#define _NA2_6_ _NA2_5_,KC_NO
#define _NA3_5_ KC_HOME,KC_PGDN,KC_END, KC_INS,  KC_CAPS
#define _NA3_6_ _NA3_5_,KC_NO
#define _NA4_3_ KC_ENT, KC_ESC, KC_BSPC

/* Function layer
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │ F01 │ F02 │ F03 │ F04 │ 🔊  │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ F05 │ F06 │ F07 │ F08 │ 🔉  │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ F09 │ F10 │ F11 │ F12 │ 🔇  │
 * └─────┴─────┼─────┼─────┼─────┤
 *             │ Del │ Tab │ Spc │
 *             └─────┴─────┴─────┘
 */
#define _FU1_5_ KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_VOLU
#define _FU1_6_ KC_NO,  _FU1_5_
#define _FU2_5_ KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_VOLD
#define _FU2_6_ KC_NO,  _FU2_5_
#define _FU3_5_ KC_F9,  KC_F10, KC_F11, KC_F12, KC_MUTE
#define _FU3_6_ KC_NO,  _FU3_5_
#define _FU4_3_ KC_DEL, KC_TAB, KC_SPC

/* Settings layer (formerly keyboard)
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │RGBTg│UGTg │Oled │FirDv│EEClr│
 * ├─────┼─────┼─────┼─────┼─────┤
 * │Spd± │Hue± │Sat± │Bri± │Mod± │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │USpd±│UHue±│USat±│UBri±│UMod±│
 * ├─────┼─────┼─────┼─────┴─────┘
 * │Char │Music│Game │
 * └─────┴─────┴─────┘
 */
#define _SE1_5_ RM_TOGG,UG_TOGG,B_LYCL, B_DVOR, EE_CLR
#define _SE1_6_ _SE1_5_,KC_NO
#define _SE2_5_ RM_SPDU,RM_HUEU,RM_SATU,RM_VALU,RM_NEXT
#define _SE2_6_ _SE2_5_,KC_NO
#define _SE3_5_ UG_SPDU,UG_HUEU,UG_SATU,UG_VALU,UG_NEXT
#define _SE3_6_ _SE3_5_,KC_NO
#define _SE4_3_ B_CHAR, MU_ON,  B_GAME

/* Mouse layer
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │Slow │ Bt6 │ Bt7 │ Bt8 │Fast │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ ◀── │ ▼── │ ▲── │ ──▶ │ Bt4 │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │◀◀── │▼▼── │▲▲── │──▶▶ │ Bt5 │
 * └─────┴─────┼─────┼─────┼─────┤
 *             │ Lft │ Mid │Right│
 *             └─────┴─────┴─────┘
 */
#define _MO1_5_ MS_ACL0,MS_BTN6,MS_BTN7,MS_BTN8,MS_ACL2
#define _MO1_6_ KC_NO,  _MO1_5_
#define _MO2_5_ MS_LEFT,MS_DOWN,MS_UP,  MS_RGHT,MS_BTN4
#define _MO2_6_ KC_NO,  _MO2_5_
#define _MO3_5_ MS_WHLL,MS_WHLD,MS_WHLU,MS_WHLR,MS_BTN5
#define _MO3_6_ KC_NO,  _MO3_5_
#define _MO4_3_ MS_BTN1,MS_BTN2,MS_BTN3

/* Music layer
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │   │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │   │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │   │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │
 * └─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
 *                   │ Rec │Stop │Play │   │Tempo│ Off │Mode │
 *                   └─────┴─────┴─────┘   └─────┴─────┴─────┘
 */
#define _MUL_3_ MU_ON, MU_OFF,MU_TOGG
#define _MUR_3_ MU_TEMP,MU_OFF, MU_NEXT
#define _MU_01_ KC_NO
#define _MU_02_ KC_NO,KC_NO
#define _MU_03_ _MU_02_,KC_NO
#define _MU_06_ _MU_03_,_MU_03_
#define _MU_08_ _MU_06_,_MU_02_
#define _MU_10_ _MU_08_,_MU_02_
#define _MU_12_ _MU_06_,_MU_06_
