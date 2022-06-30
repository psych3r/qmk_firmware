/* Copyright 2022 Abdalrahman Ali @abdalrahman-ali */

#include "abdalrahman-ali.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode)
    {
        // sends tmux prefix on tap, that is lctl(kc_spc)
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
