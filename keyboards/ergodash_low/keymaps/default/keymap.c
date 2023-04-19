#include QMK_KEYBOARD_H

#define LAYER1_LED      D5
#define LAYER2_LED      B0

enum layer_names {
    _LAYER0,
    _LAYER1,
    _LAYER2,
};

enum custom_keycodes {
    MOD_L = SAFE_RANGE,
    MOD_R,
    ACC_A,  // á
    ACC_E,  // é
    ACC_I,  // í
    ACC_O,  // ó
    ACC_U,  // ú
    AP_QUOT, // apostrophe or quotes (depending on shift key)
};

// Shortcuts for working in bash
#define CS_X	C(S(KC_X))
#define CS_C	C(S(KC_C))
#define CS_V	C(S(KC_V))
#define CS_W	C(S(KC_W))
#define CS_Q	C(S(KC_Q))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT(
        /* ROW 1 */
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LBRC, /* LEFT */
        KC_RBRC, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, /* RIGHT */
        /* ROW 2 */
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_MINS, /* LEFT */
        KC_EQL, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_ENT, /* RIGHT */
        /* ROW 3 */
        KC_A, KC_S, KC_D, KC_F, KC_G, KC_QUOT, /* LEFT */
        KC_QUOT, KC_H, KC_J, KC_K, KC_L, KC_SCLN, /* RIGHT */
        /* ROW 4 */
        KC_GRV, KC_BSLS, KC_Z, KC_X, KC_C, KC_V, /* LEFT */
        KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, /* RIGHT */
        /* ROW 5 */
        KC_LCTL, KC_LGUI, XXXXXXX, KC_LALT, MOD_L, KC_SPC, KC_LSFT, /* LEFT */
        KC_RSFT, KC_BSPC, MOD_R, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT /* RIGHT */
    ),

    [_LAYER1] = LAYOUT(
        /* ROW 1 */
        KC_F11, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,  XXXXXXX, /* LEFT */
         XXXXXXX, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F12, /* RIGHT */
        /* ROW 2 */
         XXXXXXX,  XXXXXXX,  XXXXXXX, ACC_E,  XXXXXXX,  XXXXXXX,  XXXXXXX, /* LEFT */
         XXXXXXX,  XXXXXXX, ACC_U, ACC_I, ACC_O,  XXXXXXX,  XXXXXXX, /* RIGHT */
        /* ROW 3 */
        ACC_A,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, AP_QUOT, /* LEFT */
        AP_QUOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, /* RIGHT */
        /* ROW 4 */
         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, /* LEFT */
         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, /* RIGHT */
        /* ROW 5 */
         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MOD_L,  XXXXXXX,  KC_LSFT, /* LEFT */
         KC_RSFT,  XXXXXXX,  MOD_R, KC_HOME, KC_PGUP, KC_PGDN, KC_END /* RIGHT */
    ),

    [_LAYER2] = LAYOUT(
        /* ROW 1 */
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /* LEFT */
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /* RIGHT */
        /* ROW 2 */
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /* LEFT */
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /* RIGHT */
        /* ROW 3 */
        XXXXXXX, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN1, XXXXXXX, XXXXXXX, /* LEFT */
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /* RIGHT */
        /* ROW 4 */
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, /* LEFT */
        XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_WH_UP, KC_MS_WH_DOWN, XXXXXXX, /* RIGHT */
        /* ROW 5 */
        KC_LCTL, KC_LGUI, XXXXXXX, KC_LALT, MOD_L, XXXXXXX, XXXXXXX, /* LEFT */
        XXXXXXX, XXXXXXX, MOD_R, KC_MS_LEFT, KC_MS_UP, KC_MS_DOWN, KC_MS_RIGHT /* RIGHT */
    ),
};

static bool shift_left = false;
static bool shift_right = false;
static bool shift_is_held = false;

static bool mod_left = false;
static bool mod_right = false;

static void check_and_switch_to_layer(void)
{
    if (mod_left && mod_right) {
        layer_on(_LAYER2);
        writePinLow(LAYER2_LED);
        writePinHigh(LAYER1_LED);
    } else if (mod_left || mod_right) {
        layer_off(_LAYER2);
        layer_on(_LAYER1);
        writePinHigh(LAYER2_LED);
        writePinLow(LAYER1_LED);
    } else {
        layer_off(_LAYER1);
        layer_off(_LAYER2);
        writePinHigh(LAYER2_LED);
        writePinHigh(LAYER1_LED);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MOD_L:
            mod_left = record->event.pressed;
            check_and_switch_to_layer();
            return false;
        case MOD_R:
            mod_right = record->event.pressed;
            check_and_switch_to_layer();
            return false;
        case ACC_A:
            if (record->event.pressed) {
                SEND_STRING("'a");
            }
            return false;
        case ACC_E:
            if (record->event.pressed) {
                SEND_STRING("'e");
            }
            return false;
        case ACC_I:
            if (record->event.pressed) {
                SEND_STRING("'i");
            }
            return false;
        case ACC_O:
            if (record->event.pressed) {
                SEND_STRING("'o");
            }
            return false;
        case ACC_U:
            if (record->event.pressed) {
                SEND_STRING("'u");
            }
            return false;
        case KC_LSFT:
            shift_left = record->event.pressed;
            shift_is_held = shift_left || shift_right;
            return true;
        case KC_RSFT:
            shift_right = record->event.pressed;
            shift_is_held = shift_left || shift_right;
            return true;
        case AP_QUOT:
            if (record->event.pressed) {
                if (shift_is_held) {
                    SEND_STRING(SS_LSFT("'")" ");
                } else {
                    SEND_STRING("' ");
                }
            }
            return false;
    }
    return true;
}
