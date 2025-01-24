# Copyright 2021 Batuhan Başerdem
# <baserdem.batuhan@gmail.com> @bbaserdem

# Kyria hardware
ifneq (,$(findstring splitkb/kyria/rev1,$(KEYBOARD)))
    # Elective features
    ENCODER_ENABLE = yes
    OLED_ENABLE = yes
    # Nonexistent features
    AUDIO_ENABLE = no
    BACKLIGHT_ENABLE = no
    RGB_MATRIX_ENABLE = no
    # Space savers
    NKRO_ENABLE = no
    VELOCIKEY_ENABLE = no
    WPM_ENABLE = no
endif
