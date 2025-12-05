// enable if fast tap modding inserts two tapped keys, refer to docs
//#define PERMISSIVE_HOLD

#define TAPPING_TERM 180
//#define RGB_DISABLE_TIMEOUT 1000

#ifdef RGB_MATRIX_ENABLE
    #ifdef RGB_MATRIX_STARTUP_MODE
        #undef RGB_MATRIX_STARTUP_MODE
    #endif
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif

// Prevent normal rollover on alphas from accidentally triggering mods.
// #define IGNORE_MOD_TAP_INTERRUPT // default, doesn't need setting anymore

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// tab moded key then hold it
// TAPPING_FORCE_HOLD will break anything that uses tapping toggles (Such as the TT layer keycode, and the One Shot Tap Toggle).
// there's a per key variant.
// #define TAPPING_FORCE_HOLD
// consider enabling this per key for home row mods

// Apply the modifier on keys that are tapped during a short hold of a modtap
// #define PERMISSIVE_HOLD


#define LED_LIST_FN_LEN        1
#define LED_LIST_CAPS_LEN      1
#define LED_LIST_LOL_LEN       6
#define LED_LIST_WASD_LEN      4
#define LED_LIST_ARROWS_LEN    4
#define LED_LIST_HJKL_LEN      4
#define LED_LIST_NUMROW_LEN    15
#define LED_LIST_QWERTYROW_LEN 15
#define LED_LIST_NUMPAD_LEN    12

