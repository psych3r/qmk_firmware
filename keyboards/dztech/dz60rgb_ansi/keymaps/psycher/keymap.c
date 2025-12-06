#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"
#include "psycher.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case GUIA: return TAPPING_TERM + 50; break;
        case ALTS: return TAPPING_TERM + 75; break;
        case CTLD: return TAPPING_TERM + 50; break;
        case SFTF: return TAPPING_TERM - 25; break;
        case GUIN: return TAPPING_TERM + 50; break;
        default: return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_base] = LAYOUT_wrapper(LAYOUT_60_ansi, _BASE_ROW1, _BASE_ROW2, _BASE_ROW3, _BASE_ROW4_60, _BASE_ROW5_60),
    [_game] = LAYOUT_wrapper(LAYOUT_60_ansi, _GAME_ROW1, _GAME_ROW2, _GAME_ROW3, _GAME_ROW4,    _GAME_ROW5_60),
    [_vrgb] = LAYOUT_wrapper(LAYOUT_60_ansi, _VRGB_ROW1, _VRGB_ROW2, _VRGB_ROW3, _VRGB_ROW4_60, _VRGB_ROW5_60),
    [_hjkl] = LAYOUT_wrapper(LAYOUT_60_ansi, _HJKL_ROW1, _HJKL_ROW2, _HJKL_ROW3, _HJKL_ROW4,    _HJKL_ROW5),
    [_mods] = LAYOUT_wrapper(LAYOUT_60_ansi, _MODS_ROW1, _MODS_ROW2, _MODS_ROW3, _MODS_ROW4,    _MODS_ROW5),
};
