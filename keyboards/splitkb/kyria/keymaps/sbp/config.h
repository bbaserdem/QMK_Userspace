/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */

#pragma once

// Kyria specific
#ifdef KEYBOARD_splitkb_kyria_rev1
    // Split definition; use the following to flash;
    //  pro-micro:      avrdude-split-left/right
    //  elite-c:        dfu-split-left/right
#   define ENCODER_DIRECTION_FLIP
#   define EE_HANDS
#endif
