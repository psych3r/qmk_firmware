/* Copyright 2021 Jonavin Eng
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])


// Custom RGB Colours
#define RGB_GODSPEED 0x00, 0xE4, 0xFF // colour for matching keycaps #define RGB_NAUTILUS 0x00, 0xA4, 0xA9 // Naurilus Font colours #define RGB_PURPLELITE 0x80, 0x00, 0x80 // Purple colours

enum led_location_map {
    LED_BS,   LED_EQ,   LED_MINUS, LED_0,  LED_9,   LED_8, LED_7, LED_6, LED_5, LED_4, LED_3,    LED_2,    LED_1,    LED_ESC,
    LED_BSLS, LED_CSB,  LED_OSB,   LED_P,  LED_O,   LED_I, LED_U, LED_Y, LED_T, LED_R, LED_E,    LED_W,    LED_Q,    LED_TAB,
    LED_ENTR,           LED_QUOT,  LED_SC, LED_L,   LED_K, LED_J, LED_H, LED_G, LED_F, LED_D,    LED_S,    LED_A,    LED_CAPS,
    LED_RSHFT,          LED_SLSH,  LED_DOT,LED_COM, LED_M, LED_N, LED_B, LED_V, LED_C, LED_X,    LED_Z,              LED_LSHFT,
    LED_RFN, LED_RCTL,  LED_FN,   LED_RALT,                       LED_SPC,                       LED_LALT, LED_LGUI, LED_LCTL
};

void set_array_rgb(const uint8_t* led_array, uint8_t arr_size, uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i = 0; i < arr_size; i++)
        rgb_matrix_set_color(led_array[i], r, g, b);
}

const uint8_t LED_LIST_LOL[]       = { LED_Q  , LED_W, LED_E, LED_R, LED_D, LED_F };
const uint8_t LED_LIST_WASD[]      = { LED_W  , LED_A, LED_S, LED_D };
const uint8_t LED_LIST_ARROWS[]    = { LED_H  , LED_J, LED_K, LED_L };
const uint8_t LED_LIST_NUMROW[]    = { LED_ESC, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, LED_9, LED_0, LED_MINUS, LED_EQ,  LED_BS};
const uint8_t LED_LIST_QWERTYROW[] = { LED_TAB, LED_Q, LED_W, LED_E, LED_R, LED_T, LED_Y, LED_U, LED_I, LED_O, LED_P, LED_OSB,   LED_CSB, LED_BSLS};
const uint8_t LED_LIST_NUMPAD[]    = {
    LED_7, LED_8,   LED_9,
    LED_U, LED_I,   LED_O,
    LED_J, LED_K,   LED_L,
    LED_M, LED_COM, LED_DOT
};
