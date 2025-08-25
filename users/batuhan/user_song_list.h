/* Copyright 2025 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
 *
 * Custom song definitions for batuhan userspace
 * This file is automatically included when it exists
 */
#pragma once

#include "musical_notes.h"

/* Note duration shortcuts reference:
 * B__NOTE = Breve (2 whole notes)
 * W__NOTE = Whole note
 * H__NOTE = Half note
 * Q__NOTE = Quarter note
 * E__NOTE = Eighth note
 * S__NOTE = Sixteenth note
 * T__NOTE = Thirty-second note
 *
 * Dotted versions (add half the duration):
 * BD_NOTE, WD_NOTE, HD_NOTE, QD_NOTE, ED_NOTE, SD_NOTE, TD_NOTE
 *
 * M__NOTE(note, duration) for custom durations
 * NOTE_REST or _REST for silence
 */

// ==================== Guitar Fret Calculation Helpers ====================
// Each fret = multiply by 2^(1/12) = 1.05946309436
// This makes tablature transcription much easier!
// Using pre-calculated values to avoid needing math.h in embedded environment

// Pre-calculated semitone multipliers for up to 24 frets
// Formula: 2^(fret/12) for equal temperament tuning
#define _F__00 1.0000f   // Open string
#define _F__01 1.0595f   // 1st fret
#define _F__02 1.1225f   // 2nd fret
#define _F__03 1.1892f   // 3rd fret
#define _F__04 1.2599f   // 4th fret
#define _F__05 1.3348f   // 5th fret
#define _F__06 1.4142f   // 6th fret
#define _F__07 1.4983f   // 7th fret
#define _F__08 1.5874f   // 8th fret
#define _F__09 1.6818f   // 9th fret
#define _F__10 1.7818f   // 10th fret
#define _F__11 1.8877f   // 11th fret
#define _F__12 2.0000f   // 12th fret (octave)
#define _F__13 2.1189f   // 13th fret
#define _F__14 2.2449f   // 14th fret
#define _F__15 2.3784f   // 15th fret
#define _F__16 2.5198f   // 16th fret
#define _F__17 2.6697f   // 17th fret
#define _F__18 2.8284f   // 18th fret
#define _F__19 2.9966f   // 19th fret
#define _F__20 3.1748f   // 20th fret
#define _F__21 3.3636f   // 21st fret
#define _F__22 3.5636f   // 22nd fret
#define _F__23 3.7754f   // 23rd fret
#define _F__24 4.0000f   // 24th fret (2 octaves)

// Helper macro to calculate fret position using lookup table
// Note: pass the note with underscore prefix like _E3, not NOTE_E3
// Concatenate F_ with fret number to get the multiplier
#define TAB(note, fret, duration) { (NOTE##note * _F_##fret), duration }

// All the note variants:
#define TAB_B(note, fret)  TAB(note, fret, 128)  // Breve (2 whole notes)
#define TAB_W(note, fret)  TAB(note, fret, 64)   // Whole note
#define TAB_H(note, fret)  TAB(note, fret, 32)   // Half note
#define TAB_Q(note, fret)  TAB(note, fret, 16)   // Quarter note
#define TAB_E(note, fret)  TAB(note, fret, 8)    // Eighth note
#define TAB_S(note, fret)  TAB(note, fret, 4)    // Sixteenth note
#define TAB_T(note, fret)  TAB(note, fret, 2)    // Thirty-second note
// Dotted versions
#define TAB_BD(note, fret) TAB(note, fret, 192)  // Breve dotted (128+64)
#define TAB_WD(note, fret) TAB(note, fret, 96)   // Whole dotted (64+32)
#define TAB_HD(note, fret) TAB(note, fret, 48)   // Half dotted (32+16)
#define TAB_QD(note, fret) TAB(note, fret, 24)   // Quarter dotted (16+8)
#define TAB_ED(note, fret) TAB(note, fret, 12)   // Eighth dotted (8+4)
#define TAB_SD(note, fret) TAB(note, fret, 6)    // Sixteenth dotted (4+2)
#define TAB_TD(note, fret) TAB(note, fret, 3)    // Thirty-second dotted (2+1)

// Standard guitar tuning starts from E2

// ==================== Guitar Tabs ====================

// Simple guitar riff example (Smoke on the Water style)
// Tab: G string: 0-3-5, 0-3-6-5
#define GUITAR_RIFF \
    TAB_Q(_G3, _00), TAB_Q(_G3, _03), TAB_H(_G3, _05), \
    TAB_Q(_G3, _00), TAB_Q(_G3, _03), TAB_E(_G3, _06), TAB_QD(_G3, _05)

// Polygon has CS2 FS2 B2 E3 GS3 CS3 tuning, and 5/4 time scale
// https://www.songsterr.com/a/wsa/king-gizzard-the-lizard-wizard-crumbling-castle-tab-s447026
#define POLYGONDWANALAND \
    TAB_Q(_E3,_07), TAB_Q(_B2,_00), TAB_Q(_E3,_14), TAB_Q(_B2,_00), TAB_Q(_E3,_12), \
    TAB_Q(_E3,_14), TAB_Q(_E3,_10), TAB_Q(_B2,_00), TAB_Q(_E3,_10), TAB_Q(_E3,_12), \
    TAB_Q(_E3,_09), TAB_Q(_B2,_00), TAB_Q(_E3,_09), TAB_Q(_E3,_10), TAB_S(_E3,_09), TAB_S(_E3,_10), TAB_E(_E3,_09), \
    TAB_Q(_E3,_07), TAB_Q(_E3,_02), TAB_Q(_B2,_00), TAB_Q(_E3,_05), TAB_Q(_B2,_00), \
    TAB_Q(_E3,_07), TAB_Q(_B2,_00), TAB_Q(_E3,_14), TAB_Q(_B2,_00), TAB_Q(_E3,_14), \
    TAB_Q(_E3,_15), TAB_Q(_E3,_17), TAB_Q(_B2,_00), TAB_Q(_E3,_19), TAB_Q(_E3,_15), \
    TAB_S(_E3,_14), TAB_S(_E3,_15), TAB_E(_E3,_14), TAB_Q(_B2,_00), TAB_Q(_E3,_14), TAB_Q(_E3,_15), TAB_S(_E3,_14), TAB_S(_E3,_15), TAB_E(_E3,_14), \
    TAB_Q(_B2,_00), TAB_Q(_E3,_10), TAB_Q(_B2,_00), TAB_Q(_E3,_12), TAB_Q(_B2,_00), \
    TAB_Q(_E3,_09), TAB_Q(_B2,_00), TAB_Q(_E3,_14), TAB_Q(_B2,_00), TAB_Q(_E3,_12), \
    TAB_Q(_E3,_14), TAB_H(_E3,_10), TAB_Q(_E3,_10), TAB_Q(_E3,_12), \
    TAB_H(_E3,_09), TAB_Q(_E3,_09), TAB_Q(_E3,_10), TAB_S(_E3,_09), TAB_S(_E3,_10), TAB_E(_E3,_09), \
    TAB_Q(_E3,_07), TAB_Q(_E3,_07), TAB_Q(_B2,_00), TAB_Q(_E3,_00), TAB_Q(_B2,_00)
