/* Copyright 2022 Abdalrahman Ali @abdalrahman-ali */

#include "tap_dance.h"

// Create an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

// All tap dance functions would go here.
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CLN]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
    [TD_TERMINATOR]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, terminator_finished, terminator_reset),
    [TD_LSFT_CAPS]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_LSFT_finished, dance_LSFT_reset),
};

// https://docs.qmk.fm/#/feature_tap_dance 
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

void terminator_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP:  register_code16(LALT(KC_F4));  break;
        case SINGLE_HOLD: register_code(KC_RALT);        break;
        case DOUBLE_TAP:  register_code16(RSFT(KC_DEL)); break;
        case DOUBLE_HOLD: register_code(KC_RALT);        break;
        case TRIPLE_TAP:  register_code16(LCA(KC_DEL));  break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        //case DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
    }
}

void terminator_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:  unregister_code16(LALT(KC_F4));  break;
        case SINGLE_HOLD: unregister_code(KC_RALT);        break;
        case DOUBLE_TAP:  unregister_code16(RSFT(KC_DEL)); break;
        case DOUBLE_HOLD: unregister_code(KC_RALT);        break;
        case TRIPLE_TAP:  unregister_code16(LCA(KC_DEL));  break;
        //case DOUBLE_SINGLE_TAP: unregister_code(KC_X);break;
    }
    xtap_state.state = 0;
}

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

    void dance_LSFT_finished(qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1 || keymap_config.no_gui) {
            register_code16(KC_LSFT);
        } else {
            register_code(KC_CAPS);
        }
    }

    void dance_LSFT_reset(qk_tap_dance_state_t *state, void *user_data) {
        if (state->count == 1 || keymap_config.no_gui) {
            unregister_code16(KC_LSFT);
        } else {
            unregister_code(KC_CAPS);
        }
    }

