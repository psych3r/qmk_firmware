/* Copyright 2019 Yiancar
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
#include QMK_KEYBOARD_H
//#include "nk65.h"
//#include "drivers/issi/is31fl3733.h"

/*{  matrix init and scan*/
void matrix_init_user(void) {
  //user initialization
}
void matrix_scan_user(void) {
  //user matrix
}
/*}*/
/*{ for complex tap dancing */
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};
/*}*/
/*{ Custom keycodes */
// custom KCs enum
enum custom_keycodes {
    MT_TMUXPRE = SAFE_RANGE
};
#define TMUX_PRE CTL_T(MT_TMUXPRE)
// tap dance enum
enum tap_dance_keys {
    TD_CLN = 1,
    TD_TERMINATOR
};
/*}*/
/*{ custom tap dance functions */
void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_SCLN);
    } else {
        register_code16(KC_COLN);
    }
}
void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_SCLN);
    } else {
        unregister_code16(KC_COLN);
    }
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

void x_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {

        case SINGLE_TAP: register_code16(LALT(KC_F4)); break;
        case SINGLE_HOLD: register_code(KC_RALT); break;
        case DOUBLE_TAP: register_code16(RSFT(KC_DEL)); break;
        case DOUBLE_HOLD: register_code(KC_RALT); break;
        case TRIPLE_TAP: register_code16(LCA(KC_DEL)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        //case DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
    }
}

void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code16(LALT(KC_F4)); break;
        case SINGLE_HOLD: unregister_code(KC_RALT); break;
        case DOUBLE_TAP: unregister_code16(RSFT(KC_DEL)); break;
        case DOUBLE_HOLD: unregister_code(KC_RALT);break;
        //case DOUBLE_SINGLE_TAP: unregister_code(KC_X);break;
        case TRIPLE_TAP: unregister_code16(LCA(KC_DEL)); break;
    }
    xtap_state.state = 0;
}

/*}*/
/*{ tap dance actions array */

// All tap dance functions would go here.
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CLN]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
    [TD_TERMINATOR]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};

/*}*/
/*{ process record user */

bool process_record_user(uint16_t keycode, keyrecord_t *record) 
{
    switch (keycode) 
    {
        // sends tmux prefix of tap, that is lctl(kc_spc)
      	// tap_code16 sends advanced keycodes. the 16 bit version of the `tap_code` function is used here.
       	case TMUX_PRE:
  			if (record->tap.count > 0) 
  			{
    			if (record->event.pressed) 
      				tap_code16(LCTL(KC_SPC));

    			// do not continue with default tap action
    			// if the MT was pressed or released, but not held
    			return false;
  			}
			break;
        default:
            return true; // Process all other keycodes normally
    }
    return true;
}

/*}*/
/*{ Key aliases */

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define CTL_D LCTL_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

// Tmux, hjkl and mods
#define TMUX CTL_T(TMUX_PRE)
#define HJKL LT(3, KC_W)
#define MODS LT(4, KC_Q)
//#define XXX KC_TRNS
/*}  */
/*{ Tapping term */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) 
{
    switch (keycode) {
        case GUI_A:
            return TAPPING_TERM + 65; break;
        case ALT_S:
            return TAPPING_TERM + 85; break;
        case CTL_D:
            return TAPPING_TERM + 50; break;
        case SFT_F:
            return TAPPING_TERM - 10; break;
        default:
            return TAPPING_TERM;
    }
}
/*}  */
/*{ LAYERS  */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_65_ansi( /* Base */
        KC_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,\
        KC_TAB,  MODS,    HJKL,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,\
        TMUX,    GUI_A,   ALT_S,  CTL_D,  SFT_F,  KC_G,   KC_H,   SFT_J,  CTL_K,   ALT_L,   KC_SCLN, KC_QUOT,          KC_ENT,  KC_END,\
        KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   TT(3), \
        KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,                TD(TD_TERMINATOR), TT(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[1] = LAYOUT_65_ansi( /* Gaming Layer */
        KC_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,\
        KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,\
        KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_END,\
        KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   DF(0), \
        KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,                          KC_RALT, TT(2),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[2] = LAYOUT_65_ansi( /* RGB and VOL layer */
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_TRNS,\
        KC_TRNS, S1_DEC,  S1_INC,  S2_DEC,  S2_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP,\
        KC_CAPS, EF_DEC,  EF_INC,  H1_DEC,  H1_INC,  H2_DEC,  H2_INC,  BR_DEC,  BR_INC,  ES_DEC,  ES_INC,  KC_TRNS,          KC_TRNS, KC_PGDN,\
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_VOLU, KC_MUTE,\
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_VOLD, KC_MNXT),

[3] = LAYOUT_65_ansi( /* HJKL layer */
        KC_PWR,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_DEL,\
        KC_TAB,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_PGUP,\
        TMUX,    KC_LEFT, KC_RIGHT, KC_UP,   KC_DOWN, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_ENT,  KC_TRNS,          KC_ENT,  KC_PGDN,\
        KC_LSFT, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT,          KC_VOLU, KC_TRNS,\
        KC_LCTL, KC_LGUI, KC_LALT,           KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, DF(1)),

[4] = LAYOUT_65_ansi( /* MODS layer */
        KC_PWR,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_DEL,\
        KC_TAB,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_PGUP,\
        TMUX,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_BSPC, KC_DEL,  KC_END,  KC_ENT,  KC_TRNS,          KC_ENT,  KC_PGDN,\
        KC_LSFT, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT,          KC_VOLU, KC_TRNS,\
        KC_LCTL, KC_LGUI, KC_LALT,           KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_TRNS),

};
/*}*/
