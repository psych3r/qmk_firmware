#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"
#include "psycher.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode)
    {
        case GUIA: return TAPPING_TERM + 50; break;
        //case ALTS: return TAPPING_TERM + 75; break;
        //case ALTS: return TAPPING_TERM + 80; break;
        case ALTS: return TAPPING_TERM + 90; break;
        case CTLD: return TAPPING_TERM + 50; break;
        case SFTF: return TAPPING_TERM + 30; break;
        //case SFTF: return TAPPING_TERM - 10; break;
        case SFTJ: return TAPPING_TERM - 10; break;
        case GUIN: return TAPPING_TERM + 50; break;
        case HJKL: return TAPPING_TERM + 30; break;
        //case MODS: return TAPPING_TERM + 50; break;
        default:   return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
    [_base] = LAYOUT_wrapper(LAYOUT_65_ansi_blocker, _BASE_ROW1_65, _BASE_ROW2_65, _BASE_ROW3_65, _BASE_ROW4_65, _BASE_ROW5_65_2mod ),
    [_game] = LAYOUT_wrapper(LAYOUT_65_ansi_blocker, _GAME_ROW1_65, _GAME_ROW2_65, _GAME_ROW3_65, _GAME_ROW4_65, _GAME_ROW5_65_2mod ),
    [_vrgb] = LAYOUT_wrapper(LAYOUT_65_ansi_blocker, _VRGB_ROW1_65, _VRGB_ROW2_65, _VRGB_ROW3_65, _VRGB_ROW4_65, _VRGB_ROW5_65_2mod ),
    [_hjkl] = LAYOUT_wrapper(LAYOUT_65_ansi_blocker, _HJKL_ROW1_65, _HJKL_ROW2_65, _HJKL_ROW3_65, _HJKL_ROW4_65, _HJKL_ROW5_65_2mod ),
    [_mods] = LAYOUT_wrapper(LAYOUT_65_ansi_blocker, _MODS_ROW1_65, _MODS_ROW2_65, _MODS_ROW3_65, _MODS_ROW4_65, _MODS_ROW5_65_2mod ),
    [_numpad] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_BSPC,      TT(_numpad), _______, _______,
        _______, _______, _______,                            KC_0,             KC_DOT,  KC_ENT,                    _______, _______, _______
    ),
};
