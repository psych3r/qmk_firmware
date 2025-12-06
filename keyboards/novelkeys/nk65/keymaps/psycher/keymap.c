#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"
#include "psycher.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case GUIA: return TAPPING_TERM + 65; break;
        case ALTS: return TAPPING_TERM + 85; break;
        case CTLD: return TAPPING_TERM + 50; break;
        case SFTF: return TAPPING_TERM - 10; break;
        default: return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_base] = LAYOUT_wrapper(LAYOUT_65_ansi, _BASE_ROW1_65, _BASE_ROW2_65, _BASE_ROW3_65, _BASE_ROW4_65, _BASE_ROW5_65_3mod ),
    [_game] = LAYOUT_wrapper(LAYOUT_65_ansi, _GAME_ROW1_65, _GAME_ROW2_65, _GAME_ROW3_65, _GAME_ROW4_65, _GAME_ROW5_65_3mod ),
    [_vrgb] = LAYOUT_wrapper(LAYOUT_65_ansi, _VRGB_ROW1_65, _VRGB_ROW2_65, _VRGB_ROW3_65, _VRGB_ROW4_65, _VRGB_ROW5_65_3mod ),
    [_hjkl] = LAYOUT_wrapper(LAYOUT_65_ansi, _HJKL_ROW1_65, _HJKL_ROW2_65, _HJKL_ROW3_65, _HJKL_ROW4_65, _HJKL_ROW5_65_3mod ),
    [_mods] = LAYOUT_wrapper(LAYOUT_65_ansi, _MODS_ROW1_65, _MODS_ROW2_65, _MODS_ROW3_65, _MODS_ROW4_65, _MODS_ROW5_65_3mod ),
};
