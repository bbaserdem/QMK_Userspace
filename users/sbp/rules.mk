# Copyright 2025 Batuhan Başerdem
# <baserdem.batuhan@gmail.com> @bbaserdem

# Common compilation flags
LTO_ENABLE = yes

# These should be enabled in all boards
EXTRAKEY_ENABLE = yes		# OS signals like volume control
UNICOD_COMMON = yes			# Used for unicode character emulation
UNICODEMAP_ENABLE = yes		# We will use unicodemap feature
OS_DETECTION_ENABLE = yes	# Auto-detect where we are hooked up
LAYER_LOCK_ENABLE = yes		# Enables locking layers

# These should be disabled in all boards
KEY_LOCK_ENABLE = no    # Allows locking any key. Not used in general
TAP_DANCE_ENABLE = no   # Tap dance keys; i don't use tap dance

# These features can be disabled at whim
NKRO_ENABLE ?= yes      # Default is 6KRO
VELOCIKEY_ENABLE ?= yes # Speed effects change with typing speed
WPM_ENABLE ?= yes       # Get WPM reports as you type

# Manually configure these on each keyboard individually
# AUDIO_ENABLE            # Audio stuff
# BACKLIGHT_ENABLE        # Switch LEDs
# ENCODER_ENABLE          # Rotary encoder
# RGB_MATRIX_ENABLE       # RGB LEDs
# OLED_ENABLE  	          # For OLED

# Userspace code
SRC += sbp.c

# Macros
SRC += bb-macro.c

# Audio code
ifeq ($(strip $(AUDIO_ENABLE)), yes)
SRC += sbp-audio.c
endif

# Rotary encoder stuff
ifeq ($(strip $(ENCODER_ENABLE)), yes)
SRC += sbp-encoder.c
endif

# RGB LED (Underglow) code
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
SRC += sbp-rgb-light.c
endif

# RGB LED (Perkey) code
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
SRC += sbp-rgb-matrix.c
endif

# OLED code
ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += sbp-oled.c
    ifeq ($(strip $(CTPC)), yes)
        SRC += sbp-oled-extra.c
    endif
endif
