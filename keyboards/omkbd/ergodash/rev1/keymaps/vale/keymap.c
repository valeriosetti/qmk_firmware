#include QMK_KEYBOARD_H

enum layer_names {
    _LAYER0,
    _LAYER1
};

enum custom_keycodes {
    TO_L0 = SAFE_RANGE,
    TO_L1,
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
// Shortcut for switching tabs (es: Chrome)
#define C_TAB	C(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT_3key_2us(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LBRC,                       KC_RBRC, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,                       KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_QUOT,                       KC_QUOT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_GRV,  KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,                                            KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    KC_LCTL, KC_LGUI, KC_LGUI, KC_LALT,          TO_L1,   KC_SPC,  KC_LSFT,     KC_RSFT, KC_BSPC, TO_L1,            KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
    ),

    [_LAYER1] = LAYOUT_3key_2us(
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    _______, CS_Q,    CS_W,    ACC_E,   _______, _______, _______,                       _______, _______, ACC_U,   ACC_I,   ACC_O,   _______, _______,
    _______, ACC_A,   _______, _______, _______, _______, AP_QUOT,                       AP_QUOT,  _______, _______, _______, _______, _______, _______,
    C_TAB,   _______, _______, CS_X,    CS_C,    CS_V,                                            _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE,
    _______, _______, _______, _______,          _______, _______,  _______,    _______, _______, _______,          KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
};

static bool shift_is_held = false;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TO_L0:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_LAYER0);
            }
            return false;
            break;
        case TO_L1:
            if (record->event.pressed) {
                layer_on(_LAYER1);
            } else {
                layer_off(_LAYER1);
            }
            return false;
            break;
        case ACC_A:
            if (record->event.pressed) {
                SEND_STRING("'a");
            }
            return false;
            break;
        case ACC_E:
            if (record->event.pressed) {
            SEND_STRING("'e");
            }
            return false;
            break;
        case ACC_I:
            if (record->event.pressed) {
            SEND_STRING("'i");
            }
            return false;
            break;
        case ACC_O:
            if (record->event.pressed) {
            SEND_STRING("'o");
            }
            return false;
            break;
        case ACC_U:
            if (record->event.pressed) {
            SEND_STRING("'u");
            }
            return false;
            break;
        case KC_LSFT:
        case KC_RSFT:
            shift_is_held = record->event.pressed;
            break;
        case AP_QUOT:
            if (record->event.pressed) {
                if (shift_is_held) {
                    SEND_STRING(SS_LSFT("'")" ");
                } else {
                    SEND_STRING("' ");
                }
            }
            return false;
            break;
    }
    return true;
}
