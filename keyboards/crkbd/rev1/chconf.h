/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */

// Code pertaining the ARM crkbd version
#define CH_CFG_ST_RESOLUTION 16
#define CH_CFG_ST_FREQUENCY 10000
#if __has_include("platforms/chibios/common/configs/chconf.h")
#   include_next "platforms/chibios/common/configs/chconf.h"
#else
#   include_next "chconf.h"
#endif
