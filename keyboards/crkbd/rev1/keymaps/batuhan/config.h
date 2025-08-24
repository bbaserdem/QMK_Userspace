/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once

// Code pertaining to Corne ARM; from Waffle's keymap
    // Use EE_HANDS to determine handedness
#   define EE_HANDS

    // Set serial pin as D3 for sure
#   undef SOFT_SERIAL_PIN
#   define SOFT_SERIAL_PIN D3
#   define CRC8_USE_TABLE
#   define CRC8_OPTIMIZE_SPEED
#   define SERIAL_USART_SPEED 921600
#   define SERIAL_USART_DRIVER SD1
#   define SERIAL_USART_TX_PAL_MODE 7

    // Rebrand the PCB
#   undef PRODUCT
#   define PRODUCT "Protorne Keyboard"
#   undef MANUFACTURER
#   define MANUFACTURER "Waffles"

    // Audio output on pin A5 (actualy will be output on B1 using keymap init)
#   ifdef AUDIO_ENABLE
#       define AUDIO_PIN A5
#       define MUSIC_MAP
#   endif

    // Things to make RGB matrix work on the waffle board
#   ifdef RGB_MATRIX_ENABLE
#       undef RGB_DI_PIN
#       define RGB_DI_PIN B5
#       undef RGBLED_NUM
#       define RGBLED_NUM 54
#       define RGB_MATRIX_SPLIT { 27, 27 }
#       define WS2812_PWM_DRIVER PWMD3
#       define WS2812_PWM_CHANNEL 3
#       define WS2812_PWM_PAL_MODE 2
#       define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#       define WS2812_DMA_CHANNEL 3
#   endif // RGB_MATRIX_ENABLE

    // Encoder definitons
#   ifdef ENCODER_ENABLE
#       define ENCODERS_PAD_A { B2 }
#       define ENCODERS_PAD_B { B6 }
#       define ENCODER_RESOLUTIONS { 4 }
#   endif // ENCODER_ENABLE

    // Pimoroni trackball
#   ifdef POINTING_DEVICE_ENABLE
#       define SPLIT_POINTING_ENABLE
#       define POINTING_DEVICE_RIGHT
#   endif // POINTING_DEVICE_ENABLE
