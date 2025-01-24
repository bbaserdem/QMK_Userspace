/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include "sbp.h"

// OLED layout images writer function
void render_modifiers(uint8_t row, uint8_t col, uint8_t mods);
void render_rgb(uint8_t row, uint8_t col);
void render_status_left(uint8_t row, uint8_t col);
void render_status_right(uint8_t row, uint8_t col);
