/* Copyright 2022 Abdalrahman Ali @psycher */

#include "tap_dance.h"
#include "psycher.h"

// All tap dance functions would go here.
tap_dance_action_t tap_dance_actions[] = {
    // [TD_CLN]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
    [TD_TERMINATOR]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, terminator_finished, terminator_reset),
    // [TD_LSFT_CAPS]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_LSFT_finished, dance_LSFT_reset),
    [TD_CLN]         = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    // [TD_TERMINATOR]  = ACTION_TAP_DANCE_FN(terminator_exec),
    [TD_LSFT_CAPS]   = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the terminator tap dance.
static td_tap_t terminator_td_state = { .is_press_action = true, .state = TD_NONE };

void terminator_finished(tap_dance_state_t *state, void *user_data) {
    terminator_td_state.state = cur_dance(state);
    switch (terminator_td_state.state) {
        // case TD_SINGLE_TAP:  register_code16(LALT(KC_F4));  break;
        case TD_SINGLE_TAP:  register_code16(OS_TERMINATE);  break;
        case TD_SINGLE_HOLD: register_code(KC_RALT);        break;
        case TD_DOUBLE_TAP:  register_code16(RSFT(KC_DEL)); break;
        case TD_DOUBLE_HOLD: register_code(KC_RALT);        break;
        case TD_TRIPLE_TAP:  register_code16(LCA(KC_DEL));  break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        //case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
        default: break;
    }
}

void terminator_reset(tap_dance_state_t *state, void *user_data) {
    switch (terminator_td_state.state) {
        case TD_SINGLE_TAP:  unregister_code16(OS_TERMINATE);  break;
        // case TD_SINGLE_TAP:  unregister_code16(LALT(KC_F4));  break;
        case TD_SINGLE_HOLD: unregister_code(KC_RALT);        break;
        case TD_DOUBLE_TAP:  unregister_code16(RSFT(KC_DEL)); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_RALT);        break;
        case TD_TRIPLE_TAP:  unregister_code16(LCA(KC_DEL));  break;
        //case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X);break;
        default: break;
    }
    terminator_td_state.state = TD_NONE;
}

// void dance_cln_finished(tap_dance_state_t *state, void *user_data) {
//     if (state->count == 1) {
//         register_code(KC_SCLN);
//     } else {
//         register_code16(KC_COLN);
//     }
// }
//
// void dance_cln_reset(tap_dance_state_t *state, void *user_data) {
//     if (state->count == 1) {
//         unregister_code(KC_SCLN);
//     } else {
//         unregister_code16(KC_COLN);
//     }
// }
//
// void dance_LSFT_finished(tap_dance_state_t *state, void *user_data) {
//     if (state->count == 1 || keymap_config.no_gui) {
//         register_code16(KC_LSFT);
//     } else {
//         register_code(KC_CAPS);
//     }
// }
//
// void dance_LSFT_reset(tap_dance_state_t *state, void *user_data) {
//     if (state->count == 1 || keymap_config.no_gui) {
//         unregister_code16(KC_LSFT);
//     } else {
//         unregister_code(KC_CAPS);
//     }
// }

// void terminator_exec(tap_dance_state_t *state, void *user_data) {
//     switch (state->count) {
//         case SINGLE_TAP:
//             register_code16(LALT(KC_F4));
//             reset_tap_dance(state);
//             break;
//         case SINGLE_HOLD:
//             register_code(KC_RALT);
//             reset_tap_dance(state);
//             break;
//         case DOUBLE_TAP:
//             register_code16(RSFT(KC_DEL));
//             reset_tap_dance(state);
//             break;
//         case DOUBLE_HOLD:
//             register_code(KC_RALT);
//             reset_tap_dance(state);
//             break;
//         case TRIPLE_TAP:
//             register_code16(LCA(KC_DEL));
//             reset_tap_dance(state);
//             break;
//
//         // Last case is for fast typing. Assuming your key is `f`:
//         // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
//         // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
//         //case DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
//
//     }
// }
