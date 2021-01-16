// tapping timeout in ms, for TAPPING_TERM_PER_KEY, refer to the docs
// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

#define TAPPING_TERM_PER_KEY

// enable if fast tap modding inserts two tapped keys, refer to docs
//#define PERMISSIVE_HOLD

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT
// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// tab moded key then hold it 
// TAPPING_FORCE_HOLD will break anything that uses tapping toggles (Such as the TT layer keycode, and the One Shot Tap Toggle).
// there's a per key variant.
// #define TAPPING_FORCE_HOLD
// consider enabling this per key for home row mods

// Apply the modifier on keys that are tapped during a short hold of a modtap
// #define PERMISSIVE_HOLD


// default is 5
#define TAPPING_TOGGLE 2
