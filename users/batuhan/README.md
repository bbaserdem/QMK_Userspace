# Batuhan's QMK Userspace

## Keyboard Layout

The keyboard layout commonly used, and will be demonstrated is the `Split 3x6+3` layout.
Layouts are meant to be used for `dvorak` and `turkish-f` software keymaps.
`qwerty` is provided for compatibility.

**Tap-Hold Notation:**
- X/Y = Tap for X, Hold for Y
  - ⌘ = GUI/Win
  - ⌥ = Alt
  - ⌃ = Ctrl
  - ⇧ = Shift
  - ⌤ = AltGr
  
**Layer Keys (hold to activate):**
- ⁰ = Key layer
- ¹ = Nav layer
- ² = Sym layer
- ³ = Num layer
- ⁴ = Fun layer
- ⁵ = Mou layer

### Base Layer

- Base layer is keyboard's base layer.
- The 5x3 is taken directly from the regular keyboard layout.
- The outer columns are made for convenience.
- The thumb cluster has important typing functionality.
- Layers are accessed through tap-hold on the thumb cluster.
- Modifiers are accessed through tap-hold on the home-row.

#### Dvorak

```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ ` ~ │ ' " │ , < │ . > │  P  │  Y  │   │  F  │  G  │  C  │  R  │  L  │ < > │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│ \ | │ A/⌘ │ O/⌥ │ E/⌃ │ U/⇧ │  I  │   │  D  │ H/⇧ │ T/⌃ │ N/⌥ │ S/⌘ │ - _ │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│ / ? │ ; : │ Q/⌤ │  J  │  K  │  X  │   │  B  │  M  │  W  │ V/⌤ │  Z  │ = + │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │Del⁰ │Tab¹ │Spc² │   │Ent³ │Esc⁴ │Bks⁵ │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
```

#### Turkish F

```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ + * │  F  │  G  │  Ğ  │  I  │  O  │   │  D  │  R  │  N  │  H  │  P  │ < > │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  X  │ U/⌘ │ İ/⌥ │ E/⌃ │ A/⇧ │  Ü  │   │  T  │ K/⇧ │ M/⌃ │ L/⌥ │ Y/⌘ │  Ş  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  Q  │  J  │ Ö/⌤ │  V  │  C  │  Ç  │   │  Z  │  S  │  B  │ ./⌤ │ , ; │  W  │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │Del⁰ │Tab¹ │Spc² │   │Ent³ │Esc⁴ │Bks⁵ │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
Alt-Gr
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ ¬ ± │ @   │     │     │ ¶   │ ô Ô │   │ ¥   │ ®   │     │ °   │ £   │ < > │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│ ` ◌̀ │ û Û │ î Î │ €   │ â Â │ û Û │   │ ₺   │     │ µ   │     │ ´ ◌́ │ # ◌̌ │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│ ◌̋ ◌̊ │ « < │ » > │ “   │ ¢ © │ ”   │   │     │ §   │ ×   │ ÷ ◌̇ │ ·   │ ◌̃ ◌̆ │
└─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
```

<details>
<summary><b>⌨️ Additional Layers</b></summary>

### Numbers & Symbols Layer

Both number and symbols layers activate with the farthest thumb keys holds.
They take over the thumb cluster of their respective boards.

The **number layer** is built to have a complete character set with the base board;
such that a 5x3 layout can still have access to all the keys.

The **symbol layer** is adaptive, and will adjust to each configured language's map.
The purpose for the symbol layer is to make coding similar across software keymaps.

```
Qwerty
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │ \ | │ 7 & │ 8 * │ 9 ( │ 0 ) │   │  `  │  {  │  }  │  /  │  =  │  *  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ [ { │ 4 $ │ 5 % │ 6 ^ │ - _ │   │  ~  │  [  │  ]  │  ?  │  +  │  -  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ] } │ 1 ! │ 2 @ │ 3 # │ = + │   │  !  │  (  │  )  │  \  │  |  │  _  │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ < > │ ` ~ │ ' " │   │  #  │  &  │  $  │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
Dvorak
┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │ \ | │ 7 & │ 8 * │ 9 ( │ 0 ) │
├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ / ? │ 4 $ │ 5 % │ 6 ^ │ [ { │
├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ = + │ 1 ! │ 2 @ │ 3 # │ ] } │
└─────┴─────┴─────┼─────┼─────┼─────┤
                  │ < > │ ` ~ │ - _ │
                  └─────┴─────┴─────┘
Turkish F
┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │` X ◌̀│{7 ' │[8 ( │]9 )±│}0 =°│
├─────┼─────┼─────┼─────┼─────┼─────┤
│     │◌̋ Q ◌̊│¼4 $ │½5 %⅜│¾6 & │\/ ?¿│
├─────┼─────┼─────┼─────┼─────┼─────┤
│     │◌̃ W ◌̆│¹1 !¡│²2 " │#3 ^³│|- _ │
└─────┴─────┴─────┼─────┼─────┼─────┤
                  │ < > │¬+ *±│# Ş ◌̌│
                  └─────┴─────┴─────┘
```

### Function & Navigation Layers

Both function and navigation layers activate with the central thumb pad options.
They overlay a simple thumb cluster, so thumb cluster keys can be held if needed.

The **navigation layer** holds navigation keys, and music control functionality.

The **function layer** holds f keys, and volume functions.

```

┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │ F01 │ F02 │ F03 │ F04 │ 🔊  │   │  ⏮  │  ⏯  │  ⏭  │  ▲  │  ⎙  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ F05 │ F06 │ F07 │ F08 │ 🔉  │   │  ⏹  │  ⇞  │  ◀  │  ▼  │  ▶  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ F09 │ F10 │ F11 │ F12 │ 🔇  │   │  ⇱  │  ⇟  │  ⇲  │  ⎀  │  ⇪  │     │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ Del │ Tab │ Spc │   │ Ent │ Esc │ Bks │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
```

### Mouse & Settings Layer

The mouse layer provides mouse emulation on the left hand,
while the settings layer provides keyboard configuration on the right hand.
Both layers overlay the thumb cluster.

The settings layer allows entry to persistent layers on thumb keys.
Center row controls key leds, while the bottom row controls the underglow leds.
Top row is for toggling features, and has EEProm reset function.

Mouse buttons are for moving the mouse.
Thumb cluster mimics a mouse.

```
Mouse (Left)                                           Settings (Right)
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │Slow │ Bt6 │ Bt7 │ Bt8 │Fast │   │RGBTg│UGTg │Oled │ Vel.│EEClr│     │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ◀── │ ▼── │ ▲── │ ──▶ │ Bt4 │   │Spd± │Hue± │Sat± │Bri± │Mod± │     │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │◀◀── │▼▼── │▲▲── │──▶▶ │ Bt5 │   │USpd±│UHue±│USat±│UBri±│UMod±│     │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ Lft │ Mid │Right│   │Boot │Music│Game │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
```

**Legend:**
- Mouse: Bt = Button, 
- Arrows = Mouse movement (single = normal, double = scroll)
- RGB = RGB Matrix
- UG = Underglow
- EE = EEPROM
- Vel = Velocikey
- ± indicates increase/(shift)decrease

### Music Layer

The music layer allows playing musical notes on the keyboard.
All regular keys are masked (produce no output) and play notes instead.
The thumb cluster controls recording, playback, and music settings.

```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │   │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │   │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │   │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │  ♪  │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ Rec │Stop │Play │   │Tempo│ Off │Mode │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
```

**Music Controls:**
- Rec = Start recording
- Stop = Stop recording or playback
- Play = Start playback
- Tempo = Tap once to decrease, double-tap to increase tempo
- Mode = Cycle through modes (Major, Chromatic Guitar, Chromatic Violin)
- Off = Exit music layer

### Game Layer

The game layer disables all tap-hold functionality for gaming.
Left hand provides standard WASD gaming controls with modifiers.
Right hand provides function keys and navigation.
Exit the layer using the dedicated EXIT button.

```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ Tab │  Q  │  W  │  E  │  R  │  T  │   │ F1  │ F2  │PgDn │  ↑  │PgUp │ ` ~ │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│Shift│  A  │  S  │  D  │  F  │  G  │   │ F6  │ F7  │  ←  │  ↓  │  →  │Shift│
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│Ctrl │  Z  │  X  │  C  │  V  │  B  │   │ F10 │ F11 │ F12 │ , < │ . > │ Alt │
└─────┴─────┴─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ Esc │Enter│Space│   │Enter│Space│EXIT │
                  └─────┴─────┴─────┘   └─────┴─────┴─────┘
```

**Gaming Features:**
- No tap-hold delays for instant key response
- Standard WASD movement with surrounding keys
- Direct modifier access (Shift, Ctrl, Alt)
- Function keys and arrows on right hand
- EXIT button to return to base layer

</details>
