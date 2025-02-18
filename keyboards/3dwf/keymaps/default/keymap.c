/* Copyright 2020 Matt3o
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV, KC_PSCR, \
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,        KC_BSPC,KC_DEL,  \
        MO(_FN1),         KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,         KC_PGUP, \
        KC_LSFT,                KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,KC_UP,  KC_PGDN, \
        KC_LCTL,KC_LGUI,        KC_LALT,                        KC_SPC,                         KC_RALT,MO(_FN2), KC_LEFT,KC_DOWN,KC_RGHT
    ),
    [_FN1] = LAYOUT(
        KC_MUTE,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,_______,_______, \
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_DEL, KC_INS,  \
        _______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        KC_VOLU, \
        _______,                _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_VOLD, \
        _______,_______,        _______,                        _______,                        _______,_______,KC_HOME,KC_PGDN,KC_END
    ),
    [_FN2] = LAYOUT(
        _______,KC_P1,  KC_P2,  KC_P3,  KC_P4,  KC_P5,  KC_P6,  KC_P7,  KC_P8,  KC_P9,  KC_P0,  KC_PMNS,KC_PPLS,_______,_______,_______, \
        _______,KC_ACL0,KC_ACL1,KC_ACL2,_______,_______,_______,_______,_______,RESET,  _______,_______,_______,        _______,_______, \
        KC_CAPS,        _______,KC_SLEP,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PENT,        KC_WH_U, \
        _______,                _______,_______,_______,_______,_______,_______,_______,_______,KC_PDOT,KC_PSLS,_______,KC_MS_U,KC_WH_D, \
        KC_BTN1,KC_BTN2,        KC_BTN3,                        _______,                        _______,_______,KC_MS_L,KC_MS_D,KC_MS_R
    )
};

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
