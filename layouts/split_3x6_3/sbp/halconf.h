/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once

#ifdef KEYBOARD_crkbd_rev1
//#    define HAL_USE_DAC TRUE
#   define HAL_USE_PWM TRUE
#   define HAL_USE_SERIAL TRUE
#   include_next <halconf.h>
#endif
