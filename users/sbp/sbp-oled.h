/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 */
#pragma once
#include "sbp.h"

// Contain the main oled writer here
bool oled_task_user(void);

// Some generic rendering functions
void render_qmk_logo(uint8_t row, uint8_t col);
void render_layer(uint8_t row, uint8_t col, uint8_t top_layer);
void render_modifiers_lite(uint8_t row, uint8_t col, uint8_t mods);
void render_encoder(uint8_t row, uint8_t col, uint8_t index, uint8_t layer);
void render_wpm(uint8_t row, uint8_t col);

#ifdef RGB_MATRIX_ENABLE
void render_rgb_lite(uint8_t row, uint8_t col);
#endif // RGB_MATRIX_ENABLE

void render_status_lite(uint8_t row, uint8_t col);
