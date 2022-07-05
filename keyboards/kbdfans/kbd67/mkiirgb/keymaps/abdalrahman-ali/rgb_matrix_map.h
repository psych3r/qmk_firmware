#ifdef RGB_MATRIX_ENABLE

// Custom RGB Colours
#define RGB_GODSPEED 0x00, 0xE4, 0xFF // colour for matching keycaps
#define RGB_NAUTILUS 0x00, 0xA4, 0xA9 // Naurilus Font colours
#define RGB_PURPLELITE 0x80, 0x00, 0x80 // Purple colours

// RGB LED locations
enum led_location_map {
    LED_ESC , LED_1   , LED_2   , LED_3   , LED_4  , LED_5 , LED_6   , LED_7   , LED_8   , LED_9  , LED_0   , LED_MINS, LED_EQL , LED_BSPC, LED_DEL ,
    LED_TAB , LED_Q   , LED_W   , LED_E   , LED_R  , LED_T , LED_Y   , LED_U   , LED_I   , LED_O  , LED_P   , LED_LBRC, LED_RBRC, LED_BSLS, LED_PGUP,
    LED_CAPS, LED_A   , LED_S   , LED_D   , LED_F  , LED_G , LED_H   , LED_J   , LED_K   , LED_L  , LED_SCLN, LED_QUOT,           LED_ENT , LED_PGDN,
    LED_LSFT, LED_Z   , LED_X   , LED_C   , LED_V  , LED_B , LED_N   , LED_M   , LED_COMM, LED_DOT, LED_SLSH,           LED_RSFT, LED_UP  , LED_FN2, 
    LED_LCTL, LED_LWIN, LED_LALT,                              LED_SPC                            , LED_FN,   LED_RCTL, LED_LEFT, LED_DOWN, LED_RIGHT
};

const uint8_t LED_LIST_LOL[]       = { LED_Q   , LED_W    , LED_E , LED_R, LED_D, LED_F };
const uint8_t LED_LIST_WASD[]      = { LED_W   , LED_A    , LED_S , LED_D };
const uint8_t LED_LIST_ARROWS[]    = { LED_LEFT, LED_RIGHT, LED_UP, LED_DOWN };
const uint8_t LED_LIST_HJKL[]      = { LED_H   , LED_J    , LED_K , LED_L };
const uint8_t LED_LIST_NUMROW[]    = { LED_ESC , LED_1    , LED_2 , LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, LED_9, LED_0, LED_MINS, LED_EQL , LED_BSPC, LED_DEL};
const uint8_t LED_LIST_QWERTYROW[] = { LED_TAB , LED_Q    , LED_W , LED_E, LED_R, LED_T, LED_Y, LED_U, LED_I, LED_O, LED_P, LED_LBRC, LED_RBRC, LED_BSLS, LED_PGUP};
const uint8_t LED_LIST_NUMPAD[] = {
    LED_7, LED_8, LED_9,
    LED_U, LED_I, LED_O,
    LED_J, LED_K, LED_L,
    LED_M, LED_COMM, LED_DOT
};

#endif
