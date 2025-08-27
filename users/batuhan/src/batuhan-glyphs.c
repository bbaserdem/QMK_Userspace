/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 * 
 * THIS FILE IS AUTO-GENERATED FROM keymap.yaml
 * DO NOT EDIT MANUALLY
 */
// clang-format off
#pragma GCC optimize("Os")
#include "batuhan-keycodes.h"
#include "macros/batuhan-macros.h"

// Unicode array for Lenny face
static const uint32_t g_leny_unicode[] = {
    0x0028, // (
    0x0361, // ͡
    0x00B0, // °
    0x0020, // space
    0x035C, // ͜
    0x0296, // ʖ
    0x0020, // space
    0x0361, // ͡
    0x00B0, // °
    0x0029, // )
};

// Unicode array for Table flip
static const uint32_t g_tflip_unicode[] = {
    0x253B, // ┻
    0x2501, // ━
    0x253B, // ┻
    0xFE35, // ︵
    0x0020, // space
    0x005C, // backslash
    0x0028, // (
    0x00B0, // °
    0x25A1, // □
    0x00B0, // °
    0x0029, // )
    0x002F, // forward slash
    0x0020, // space
    0xFE35, // ︵
    0x0020, // space
    0x253B, // ┻
    0x2501, // ━
    0x253B, // ┻
};

// Glyph data table - maps keycodes to unicode/strings
const glyph_data_t glyph_table[] = {
    [G_ALPHA - G_FIRST] = {0x03B1, NULL, 0, NULL},    // α
    [G_BETA - G_FIRST] = {0x03B2, NULL, 0, NULL},    // β
    [G_GAMMA - G_FIRST] = {0x03B3, NULL, 0, NULL},    // γ
    [G_DELTA - G_FIRST] = {0x03B4, NULL, 0, NULL},    // δ
    [G_EPSLN - G_FIRST] = {0x03B5, NULL, 0, NULL},    // ε
    [G_ZETA - G_FIRST] = {0x03B6, NULL, 0, NULL},    // ζ
    [G_ETA - G_FIRST] = {0x03B7, NULL, 0, NULL},    // η
    [G_THETA - G_FIRST] = {0x03B8, NULL, 0, NULL},    // θ
    [G_LAMBD - G_FIRST] = {0x03BB, NULL, 0, NULL},    // λ
    [G_MU - G_FIRST] = {0x03BC, NULL, 0, NULL},    // μ
    [G_XI - G_FIRST] = {0x03BE, NULL, 0, NULL},    // ξ
    [G_PI - G_FIRST] = {0x03C0, NULL, 0, NULL},    // π
    [G_SIGMA - G_FIRST] = {0x03C3, NULL, 0, NULL},    // σ
    [G_PHI - G_FIRST] = {0x03C6, NULL, 0, NULL},    // φ
    [G_PSI - G_FIRST] = {0x03C8, NULL, 0, NULL},    // ψ
    [G_OMEGA - G_FIRST] = {0x03C9, NULL, 0, NULL},    // ω
    [G_CGAMM - G_FIRST] = {0x0393, NULL, 0, NULL},    // Γ
    [G_CDELT - G_FIRST] = {0x0394, NULL, 0, NULL},    // Δ
    [G_CXI - G_FIRST] = {0x039E, NULL, 0, NULL},    // Ξ
    [G_CPI - G_FIRST] = {0x03A0, NULL, 0, NULL},    // Π
    [G_CSIGM - G_FIRST] = {0x03A3, NULL, 0, NULL},    // Σ
    [G_CPHI - G_FIRST] = {0x03A6, NULL, 0, NULL},    // Φ
    [G_CPSI - G_FIRST] = {0x03A8, NULL, 0, NULL},    // Ψ
    [G_COMEG - G_FIRST] = {0x03A9, NULL, 0, NULL},    // Ω
    [G_ELLIP - G_FIRST] = {0x2026, NULL, 0, NULL},    // …
    [G_ANGST - G_FIRST] = {0x212B, NULL, 0, NULL},    // Å
    [G_BTCN - G_FIRST] = {0x20BF, NULL, 0, NULL},    // ₿
    [G_PLNCK - G_FIRST] = {0x210F, NULL, 0, NULL},    // ℏ
    [G_PGPK - G_FIRST] = {0, NULL, 0, "0B7151C823559DD8A7A04CE36426139E2F4C6CCE"},    // PGP public key
    [G_LENY - G_FIRST] = {0, g_leny_unicode, sizeof(g_leny_unicode)/sizeof(uint32_t), NULL},    // ( ͡° ͜ʖ ͡°)
    [G_TFLIP - G_FIRST] = {0, g_tflip_unicode, sizeof(g_tflip_unicode)/sizeof(uint32_t), NULL},    // ┻━┻︵ \(°□°)/ ︵ ┻━┻
};

const size_t glyph_table_size = sizeof(glyph_table) / sizeof(glyph_table[0]);
