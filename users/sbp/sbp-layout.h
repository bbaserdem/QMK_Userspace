/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once

/// Enumerate of layers
enum userspace_layers {
    // Full layers
    _BASE = 0,  // Base layer
    _DVOR,      // Firmware dvorak base layer
    _GAME,      // Game layer
    _CHAR,      // Characters layer
    // Half layers
    _SYMB,      // R1: Symbols layer
    _NUMB,      // L1: Numbers layer
    _NAVI,      // R2: Navigation (and media) layer
    _FUNC,      // L2: Function keys layer
    _KEYB,      // R3: Keyboard settings layer
    _MOUS,      // L3: Mouse keys layer
    // Top overlays
    _MUSI       // Music overlay
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

// MOD-tap definitions
// Regular keymap, left side
#define GUI_A   MT(MOD_LGUI, DV_A)
#define ALT_O   MT(MOD_LALT, DV_O)
#define CTL_E   MT(MOD_LCTL, DV_E)
#define SFT_U   MT(MOD_LSFT, DV_U)
#define GUI_SC  MT(MOD_RGUI, DV_SCLN)
#define ALT_Q   MT(MOD_RALT, DV_Q)
#define CTL_J   MT(MOD_RCTL, DV_J)
#define SFT_K   MT(MOD_RSFT, DV_K)
// Regular keymap, right side
#define SFT_H   MT(MOD_LSFT, DV_H)
#define CTL_T   MT(MOD_LCTL, DV_T)
#define ALT_N   MT(MOD_LALT, DV_N)
#define GUI_S   MT(MOD_LGUI, DV_S)
#define SFT_M   MT(MOD_RSFT, DV_M)
#define CTL_W   MT(MOD_RCTL, DV_W)
#define ALT_V   MT(MOD_RALT, DV_V)
#define GUI_Z   MT(MOD_RGUI, DV_Z)
// Dvorak keymap, left side
#define DGUI_A  MT(MOD_LGUI, KC_A)
#define DALT_O  MT(MOD_LALT, KC_O)
#define DCTL_E  MT(MOD_LCTL, KC_E)
#define DSHF_U  MT(MOD_LSFT, KC_U)
#define DGUI_SC MT(MOD_RGUI, KC_SCLN)
#define DALT_Q  MT(MOD_RALT, KC_Q)
#define DCTL_J  MT(MOD_RCTL, KC_J)
#define DSHF_K  MT(MOD_RSFT, KC_K)
// Dvorak keymap, right side
#define DSHF_H  MT(MOD_LSFT, KC_H)
#define DCTL_T  MT(MOD_LCTL, KC_T)
#define DALT_N  MT(MOD_LALT, KC_N)
#define DGUI_S  MT(MOD_LGUI, KC_S)
#define DSHF_M  MT(MOD_RSFT, KC_M)
#define DCTL_W  MT(MOD_RCTL, KC_W)
#define DALT_V  MT(MOD_RALT, KC_V)
#define DGUI_Z  MT(MOD_RGUI, KC_Z)

// Layer long-tap switches
#define MED_DEL LT(_KEYB, KC_DEL )
#define NAV_TAB LT(_NAVI, KC_TAB )
#define SYM_SPC LT(_SYMB, KC_SPC )
#define NUM_ENT LT(_NUMB, KC_ENT )
#define FUN_ESC LT(_FUNC, KC_ESC )
#define MOU_BSP LT(_MOUS, KC_BSPC)

// Layer switches
#define BB_CHAR OSL(_CHAR)
#define BB_GAME TG(_GAME)
#define BB_DVOR TG(_DVOR)

/* Depending on how the layouts change with language; the keys are shown as;
 * ┌────────────────────────────────────────────────┐
 * │AltGr       -none-      Shift       Shift+AltGr │
 * └────────────────────────────────────────────────┘
 * If there is an exclamation mark; it indicates a dead key on this map.
 */

/* Base layout
 * DVORAK
 *      ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 *  ` ~ │ ' " │ , < │ . > │ p P │ y Y │             │ f F │ g G │ c C │ r R │ l L │ < >
 *      ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 *  \ | │ a A │ o O │ e E │ u U │ i I │             │ d D │ h H │ t T │ n N │ s S │ - _
 *      ├─Gui─┼─Alt─┼─Ctr─┼─Sft─┼─────┤             ├─────┼─Sft─┼─Ctr─┼─Alt─┼─Gui─┤
 *  / ? │ ; : │ q Q │ j J │ k K │ x X │             │ b B │ m M │ w W │ v V │ z Z │ = +
 *      └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
 *                        │ Del │ Tab │Space│ │Enter│ Esc │BkSpc│
 *                        └─Key─┴─Nav─┴─Sym─┘ └─Num─┴─Fun─┴─Mou─┘
 * QWERTY
 *      ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 *  ` ~ │ q Q │ w W │ e E │ r R │ t T │             │ y Y │ u U │ i I │ o O │ p P │ < >
 *      ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 *  \ | │ a A │ s S │ d D │ f F │ g G │             │ h H │ j J │ k K │ l L │ ; : │ ' "
 *      ├─Gui─┼─Alt─┼─Ctr─┼─Sft─┼─────┤             ├─────┼─Sft─┼─Ctr─┼─Alt─┼─Gui─┤
 *  [ { │ z Z │ x X │ c C │ v V │ b B │             │ n N │ m M │ , < │ . > │ / ? │ ] }
 *      └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
 *                        │ Del │ Tab │Space│ │Enter│ Esc │BkSpc│
 *                        └─Key─┴─Nav─┴─Sym─┘ └─Num─┴─Fun─┴─Mou─┘
 * TURKISH F
 *      ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 * ¬+ *±│@f F │ g G │ ğ Ğ │¶ı I │ôo OÔ│             │¥d D │®r R │ n N │°h H │£p P │|< >¦
 *     !├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼────!┤    !
 * `x Xà│ûu UÛ│îi İÎ│€e E │âa AÂ│ûü ÜÛ│             │₺t T │ k K │µm M │ l L │´y Yá│#ş Şǎ
 * !   !├─Gui─┼─Alt─┼─Ctr─┼─Sft─┼─────┤             ├─────┼─Sft─┼─Ctr─┼─Alt!┼─Gui─┤
 * äq Qå│«j J<│»ö Ö>│“v V │¢c C©│”ç Ç │             │ z Z │§s S │×b B │÷. :ȧ│·, ; │~w W
 *      └─────┴AltGr┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴AltGr┴─────┘
 *                        │ Del │ Tab │Space│ │Enter│ Esc │BkSpc│
 *                        └─Key─┴─Nav─┴─Sym─┘ └─Num─┴─Fun─┴─Mou─┘
 * The thing about this layout is that these will fit most boards I have.
 */
// Row 1
#define _BL1_1_ DV_GRV
#define _BL1_5_ DV_QUOT,DV_COMM,DV_DOT, DV_P,   DV_Y
#define _BR1_5_ DV_F,   DV_G,   DV_C,   DV_R,   DV_L
#define _BR1_1_ KC_NUBS
// Row 2
#define _BL2_1_ DV_BSLS
#define _BL2_5_ GUI_A,  ALT_O,  CTL_E,  SFT_U,  DV_I
#define _BR2_5_ DV_D,   SFT_H,  CTL_T,  ALT_N,  GUI_S
#define _BR2_1_ DV_MINS
// Row 3
#define _BL3_1_ DV_SLSH
#define _BL3_5_ GUI_SC, ALT_Q,  CTL_J,  SFT_K,  DV_X
#define _BR3_5_ DV_B,   SFT_M,  CTL_W,  ALT_V,  GUI_Z
#define _BR3_1_ DV_EQL
// Row 4
#define _BL4_3_ MED_DEL,NAV_TAB,SYM_SPC
#define _BR4_3_ NUM_ENT,FUN_ESC,MOU_BSP

/* Dvorak firmware emulation layout
 * DVORAK
 *      ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 *  ` ~ │ ' " │ , < │ . > │ p P │ y Y │             │ f F │ g G │ c C │ r R │ l L │ < >
 *      ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 *  \ | │ a A │ o O │ e E │ u U │ i I │             │ d D │ h H │ t T │ n N │ s S │ - _
 *      ├─Gui─┼─Alt─┼─Ctr─┼─Sft─┼─────┤             ├─────┼─Sft─┼─Ctr─┼─Alt─┼─Gui─┤
 *  / ? │ ; : │ q Q │ j J │ k K │ x X │             │ b B │ m M │ w W │ v V │ z Z │ = +
 *      └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
 *                        │ Del │ Tab │Space│ │Enter│ Esc │BkSpc│
 *                        └─Med─┴─Nav─┴─Sym─┘ └─Num─┴─Fun─┴─Mou─┘
 */
// Row 1
#define _DL1_1_ KC_GRV
#define _DL1_5_ KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y
#define _DR1_5_ KC_F,   KC_G,   KC_C,   KC_R,   KC_L
#define _DR1_1_ KC_NUBS
// Row 2
#define _DL2_1_ KC_BSLS
#define _DL2_5_ DGUI_A, DALT_O, DCTL_E, DSFT_U, KC_I
#define _DR2_5_ KC_D,   DSFT_H, DCTL_T, DALT_N, DGUI_S
#define _DR2_1_ KC_MINS
// Row 3
#define _DL3_1_ KC_SLSH
#define _DL3_5_ DGUI_SC,DALT_Q, DCTL_J, DSFT_K, KC_X
#define _DR3_5_ KC_B,   DSFT_M, DCTL_W, DALT_V, DGUI_Z
#define _DR3_1_ KC_EQL
// Row 4
#define _DL4_3_ MED_DEL,NAV_TAB,SYM_SPC
#define _DR4_3_ NUM_ENT,FUN_ESC,MOU_BSP

/* Game layer
 * This layer turns off tap-hold keys, and exits via one button
 *      ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 *  Tab │  Q  │  W  │  E  │  R  │  T  │             │ F 1 │ F 2 │Pg Dn│  ^  │Pg Up│ ` ~
 *      ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 * Shift│  A  │  S  │  D  │  F  │  G  │             │ F 6 │ F 7 │  <  │  v  │  >  │Shift
 *      ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 * Ctrl │  Z  │  X  │  C  │  V  │  B  │             │ F10 │ F12 │ F12 │ , < │ . > │ Alt
 *      └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
 *                        │ Esc │Enter│Space│ │Enter│Space│EXIT │
 *                        └─────┴─────┴─────┘ └─────┴─────┴─────┘
 */
// Row 1
#define _GL1_1_ KC_TAB
#define _GL1_5_ KC_Q,   KC_W,   KC_E,   KC_R,   KC_T
#define _GR1_5_ KC_F1,  KC_F2,  KC_PGDN,KC_UP,  KC_PGDN
#define _GR1_1_ KC_GRV
// Row 2
#define _GL2_1_ KC_LSFT
#define _GL2_5_ KC_A,   KC_S,   KC_D,   KC_F,   KC_G
#define _GR2_5_ KC_F6,  KC_F7,  KC_LEFT,KC_DOWN,KC_RGHT
#define _GR2_1_ KC_RSFT
// Row 3
#define _GL3_1_ KC_RCTL
#define _GL3_5_ KC_Z,   KC_X,   KC_C,   KC_V,   KC_B
#define _GR3_5_ KC_F10, KC_F11, KC_F12, KC_COMM,KC_DOT
#define _GR3_1_ KC_LALT
// Row 4
#define _GL4_3_ KC_ESC, KC_ENT, KC_SPC
#define _GR4_3_ KC_ENT, KC_SPC, BB_GAME

/* Extra characters layer
 * This is accessed via unicode; so IBus only.
 * ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
 * │ Esc │Lenny│Table│  π  │  υ  │             │  φ  │  γ  │  χ  │  ρ  │  λ  │
 * ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 * │  α  │  ο  │  ε  │  ψ  │  ι  │             │  δ  │  η  │  τ  │  ν  │  σ  │
 * ├─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┤
 * │  ₿  │  θ  │  ℏ  │  κ  │  ξ  │             │  β  │  μ  │  ω  │  Å  │  ζ  │
 * └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
 *                   │ ... │ Shf │ GPG │ │Swap │ Shf │Game │
 *                   └─────┴─────┴─────┘ └─────┴─────┴─────┘
 *
 */
#define _CL1_5_ KC_ESC,BB_LENY,BB_TABL,GR_PI,  GR_UPS
#define _CR1_5_ GR_PHI, GR_GAM, GR_CHI, GR_RHO, GR_LAM
#define _CL2_5_ GR_ALP, GR_OMI, GR_EPS, GR_PSI, GR_IOT
#define _CR2_5_ GR_DEL, GR_ETA, GR_TAU, GR_NU,  GR_SIG
#define _CL3_5_ BB_BITC,GR_THE, BB_PLNK,GR_KAP, GR_XI
#define _CR3_5_ GR_BET, GR_MU,  GR_OME, BB_ANGS,GR_ZET
#define _CL4_3_ BB_ELLI,KC_RSFT,BB_PGPK
#define _CR4_3_ BB_DVOR,KC_LSFT,BB_GAME

/* Symbols layer
 *  This layer has the central columns shifted for convenience
 * DVORAK
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │  `  │  {  │  }  │  /  │  =  │
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │  ~  │  [  │  ]  │  ?  │  +  │
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Char.│  (  │  )  │  \  │  |  │ Llock
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │Enter│ Esc │BkSpc│
 * └─────┴─────┴─────┘
 * Turkish F
 * (AltGr is right on the central column, red. keys on main layer are omitted)
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │ + ¬ │ / \ │ - | │     │     │
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │ * ± │ ? ¿ │  _  │     │     │
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Char.│     │     │     │     │ Llock
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │Enter│ Esc │BkSpc│
 * └─────┴─────┴─────┘
 * QWERTY
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │  `  │  -  │  =  │  {  │  }  │
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │  ~  │  _  │  +  │  [  │  ]  │ # ~
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Char.│  (  │  )  │  \  │  |  │ Llock
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │Enter│ Esc │BkSpc│
 * └─────┴─────┴─────┘
 */
#define _SY1_5_ DV_GRV, DV_LCBR,DV_RCBR,DV_SLSH,DV_EQL
#define _SY2_5_ DV_TILD,DV_LBRC,DV_RBRC,DV_QUES,DV_PLUS
#define _SY2_1_ KC_NUHS
#define _SY3_5_ BB_CHAR,DV_LPRN,DV_RPRN,DV_BSLS,DV_PIPE
#define _SY3_1_ QK_LLCK
#define _SY4_3_ KC_ENT, KC_ESC, KC_BSPC

/* Numbers layer
 *  This layer contains numbers and the associated symbols.
 * DVORAK
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │ {}  │ 7 & │ 8 * │ 9 ( │ 0 ) │
 *       ├─────┼─────┼─────┼─────┼─────┤
 *  <>   │ ()  │ 4 $ │ 5 % │ 6 ^ │ < > │
 *       ├─────┼─────┼─────┼─────┼─────┤
 * Llock │ []  │ 1 ! │ 2 @ │ 3 # │Char.│
 *       └─────┴─────┴─────┼─────┼─────┼─────┐
 *                         │ Del │ Tab │Space│
 *                         └─────┴─────┴─────┘
 * Turkish F
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │     │{7 ' │[8 ( │]9 )±│}0 =°│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │     │¼4 $ │½5 %⅜│¾6 & │     │
 *       ├─────┼─────┼─────┼─────┼─────┤
 * Llock │     │¹1 !¡│²2 " │#3 ^³│Char.│
 *       └─────┴─────┴─────┼─────┼─────┼─────┐
 *                         │ Del │ Tab │Space│
 *                         └─────┴─────┴─────┘
 */
#define _NU1_5_ DBL_CBR,KC_7,   KC_8,   KC_9,   KC_0
#define _NU2_1_ DBL_ANG
#define _NU2_5_ DBL_PAR,KC_4,   KC_5,   KC_6,   KC_NUBS
#define _NU3_1_ QK_LLCK
#define _NU3_5_ DBL_BRC,KC_1,   KC_2,   KC_3,   BB_CHAR
#define _NU4_3_ KC_DEL, KC_TAB, KC_SPACE

/* Navigation layer
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │Prev │Pause│Next │  ^  │PrScr│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Stop │PgUp │  <  │  v  │  >  │
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Home │PgDwn│End  │ Ins │CapsL│
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │Enter│ Esc │BkSpc│
 * └─────┴─────┴─────┘
 */
#define _NA1_5_ KC_MPRV,KC_MPLY,KC_MNXT,KC_UP,  KC_PSCR
#define _NA2_5_ KC_MSTP,KC_PGUP,KC_LEFT,KC_DOWN,KC_RGHT
#define _NA3_5_ KC_HOME,KC_PGDN,KC_END,KC_INS,  KC_CAPS
#define _NA4_3_ KC_ENT, KC_ESC, KC_BSPC

/* Function layer
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │ F01 │ F02 │ F03 │ F04 │Vol+ │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ F05 │ F06 │ F07 │ F08 │Vol- │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ F09 │ F10 │ F11 │ F12 │Mute │
 * └─────┴─────┴─────┼─────┼─────┼─────┐
 *                   │ Del │ Tab │Space│
 *                   └─────┴─────┴─────┘
 */
#define _FU1_5_ KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_VOLU
#define _FU2_5_ KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_VOLD
#define _FU3_5_ KC_F9,  KC_F10, KC_F11, KC_F12, KC_MUTE
#define _FU4_3_ KC_DEL, KC_TAB, KC_SPC

/* Keyboard settings layer
 *       ┌─────┬─────┬─────┬─────┬─────┐
 *       │Togg.│Togg.│Eeprm│Debug│Boot │
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Spd+-│Hue+-│Sat+-│Bri+-│Mod+-│
 *       ├─────┼─────┼─────┼─────┼─────┤
 *       │Spd+-│Hue+-│Sat+-│Bri+-│Mod+-│
 * ┌─────┼─────┼─────┼─────┴─────┴─────┘
 * │OledL│Music│Game │
 * └─────┴─────┴─────┘
 */
#define _KE1_5_ RM_TOGG,UG_TOGG,EE_CLR, DB_TOGG,QK_BOOT
#define _KE2_5_ RM_SPDU,RM_HUEU,RM_SATU,RM_VALU,RM_NEXT
#define _KE3_5_ UG_SPDU,UG_HUEU,UG_SATU,UG_VALU,UG_NEXT
#define _KE4_3_ XXXXXXX,MU_ON,  BB_GAME

/* Mouse layer
 * ┌─────┬─────┬─────┬─────┬─────┐
 * │Slow │ Bt6 │ Bt7 │ Bt8 │Fast │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ |<| │ |v| │ |^| │ |>| │ Bt4 │
 * ├─────┼─────┼─────┼─────┼─────┤
 * │ <<< │ vvv │ ^^^ │ >>> │ Bt5 │
 * └─────┴─────┴─────┼─────┼─────┼─────┐
 *                   │ Lft │ Mid │Right│
 *                   └─────┴─────┴─────┘
 */
#define _MO1_5_ KC_ACL0,MS_BTN6,MS_BTN7,MS_BTN8,KC_ACL2
#define _MO2_5_ MS_LEFT,MS_DOWN,MS_UP,  MS_RGHT,MS_BTN4
#define _MO3_5_ MS_WHLL,MS_WHLD,MS_WHLU,MS_WHLR,MS_BTN5
#define _MO4_3_ MS_BTN1,MS_BTN2,MS_BTN3

/* Music layer
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
 * │   │   │   │   │   │   │   │   │   │   │   │   │
 * └───┴───┴───┼───┼───┼───┼───┼───┼───┼───┴───┴───┘
 *             │Rec│Stp│Ply│Tmp│Off│Mod│
 *             └───┴───┴───┴───┴───┴───┘
 */
#define _MUL_3_ MU_REC, MU_STOP,MU_PLAY
#define _MUR_3_ MU_TEMP,MU_OFF, MU_MOD
#define _MU_01_ MU_MASK
#define _MU_02_ MU_MASK,MU_MASK
#define _MU_03_ MU_MASK,MU_MASK,MU_MASK
#define _MU_06_ MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK
#define _MU_08_ MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK
#define _MU_10_ MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK
#define _MU_12_ MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK
