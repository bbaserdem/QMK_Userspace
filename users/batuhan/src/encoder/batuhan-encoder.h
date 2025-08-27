/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
// clang-format off
#pragma once

// Encoder mode constants
enum encoder_modes_base {
    ENC_MODE_VOLUME = 0,
    ENC_MODE_SONG = 1,
    ENC_MODE_ARROW_LR = 2,
    ENC_MODE_ARROW_UD = 3,
    ENC_MODE_PAGE_UD = 4,
    ENC_MODE_ERASE = 5,
    ENC_MODE_BASE_COUNT = 6
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

// Macro to calculate minimum bits needed for a given count
// Works for counts up to 256 (8 bits)
#define BITS_NEEDED(count) \
    ((count) <= 2 ? 1 : \
     (count) <= 4 ? 2 : \
     (count) <= 8 ? 3 : \
     (count) <= 16 ? 4 : \
     (count) <= 32 ? 5 : \
     (count) <= 64 ? 6 : \
     (count) <= 128 ? 7 : 8)

// Calculate actual bit sizes needed for encoder modes
#define ENC_BASE_BITS    BITS_NEEDED(ENC_MODE_BASE_COUNT)     // 3 bits for 6 modes
#define ENC_POINTER_BITS BITS_NEEDED(ENC_MODE_POINTER_COUNT)  // 2 bits for 4 modes
#define ENC_RGB_BITS     BITS_NEEDED(ENC_MODE_RGB_COUNT)      // 3 bits for 5 modes

// Hook to encoder stuff
// Complicated code for what the encoder keys do when pressed down
bool encoder_update_user(uint8_t index, bool clockwise);

// Defines for what the keycode clicks should do (defined in batuhan-keycodes.h)
bool process_record_encoder(uint16_t keycode, keyrecord_t *record);

// Clears the encoder settings (eeprom init uses this)
void reset_encoder_state(void);

// This is purely for oled; should it want to use it
#ifdef OLED_ENABLE
void encoder_state_string(uint8_t index, uint8_t layer, char* buffer);
#endif // OLED_ENABLE
