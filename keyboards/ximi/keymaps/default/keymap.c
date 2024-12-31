/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef XIMI_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // XIMI_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum ximi_keymap_layers {
    LAYER_BASE = 0,
    LAYER_MOD,
    LAYER_MODOPT,
    LAYER_MODCTRL,
    LAYER_MODCMD,
    LAYER_NUM
};

// Automatically enable sniping-mode on the pointer layer.
// #define XIMI_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef XIMI_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef XIMI_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define XIMI_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // XIMI_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef XIMI_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define XIMI_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // XIMI_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // XIMI_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define TO_BASE TO(LAYER_BASE)


#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

enum custom_keycodes {
    ARROW = SAFE_RANGE,
    DBL_DSH,
    UP5,
    DOWN5,
    UP10,
    DOWN10
};



const uint16_t PROGMEM num_left_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM num_right_combo[] = {KC_M, KC_W, COMBO_END};
const uint16_t PROGMEM mod_combo[] = {KC_E, KC_U, COMBO_END};
const uint16_t PROGMEM modopt_combo[] = {KC_O, KC_U, COMBO_END};
const uint16_t PROGMEM modctrl_combo[] = {KC_A, KC_U, COMBO_END};
const uint16_t PROGMEM mod_hold_combo[] = {KC_DOT, KC_P, COMBO_END};
const uint16_t PROGMEM modopt_hold_combo[] = {KC_COMMA, KC_P, COMBO_END};
const uint16_t PROGMEM modcmd_hold_combo[] = {KC_G, KC_C, COMBO_END};
const uint16_t PROGMEM sticky_cmd_ctrl_combo[] = {KC_H, KC_S, COMBO_END};
const uint16_t PROGMEM sticky_cmd_combo[] = {KC_H, KC_T, COMBO_END};
const uint16_t PROGMEM sticky_ctrl_combo[] = {KC_H, KC_N, COMBO_END};
const uint16_t PROGMEM spotlight_combo[] = {KC_U, KC_H, COMBO_END};
combo_t key_combos[] = {
    COMBO(num_left_combo, MO(LAYER_NUM)),
    COMBO(num_right_combo, MO(LAYER_NUM)),
    COMBO(mod_combo, MO(LAYER_MOD)),
    COMBO(modopt_combo, MO(LAYER_MODOPT)),
    COMBO(modctrl_combo, MO(LAYER_MODCTRL)),
    COMBO(mod_hold_combo, TO(LAYER_MOD)),
    COMBO(modopt_hold_combo, TO(LAYER_MODOPT)),
    COMBO(modcmd_hold_combo, TO(LAYER_MODCMD)),
    COMBO(sticky_cmd_combo, OSM(MOD_LGUI)),
    COMBO(sticky_cmd_ctrl_combo, OSM(MOD_LGUI | MOD_LCTL)),
    COMBO(sticky_ctrl_combo, OSM(MOD_LCTL)),
    COMBO(spotlight_combo, LCMD(KC_SPACE)),
};

// const key_override_t shift_space_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPACE, KC_UNDS);

// // This globally defines all key overrides to be used
// const key_override_t **key_overrides = {
// 	&shift_space_override
// };


#define DEL_MS 1 // Delay ms
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ARROW:
        if (record->event.pressed) {
            SEND_STRING("->");
        }
        break;
    case DBL_DSH:
        if (record->event.pressed) {
            SEND_STRING("--");
        }
        break;
    case UP5:
        if (record->event.pressed) {
            SEND_STRING(  SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS));
        }
        break;
    case DOWN5:
        if (record->event.pressed) {
            SEND_STRING( SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) );
        }
        break;
    case UP10:
        if (record->event.pressed) {
            SEND_STRING( SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS) SS_TAP(X_UP) SS_DELAY(DEL_MS));
        }
        break;
    case DOWN10:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS) SS_TAP(X_DOWN) SS_DELAY(DEL_MS));
        }
        break;
    }
    return true;
};

// clang-format off
/** \brief Dvorak layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                     \
       KC_TAB,   KC_SEMICOLON,KC_COMMA,  KC_DOT, KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,  KC_SLSH, \
       KC_ENT,   KC_A,        KC_O,      KC_E,   KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,  KC_SPACE, \
       KC_LSFT,  KC_QUOTE,    KC_Q,      KC_J,   KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,  KC_RSFT, \
                      KC_HASH, KC_ESC, KC_BTN1, KC_BTN1, KC_AT, KC_BSLS

#define LAYOUT_LAYER_MOD                                                                     \
       KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_NO,    TO_BASE,  UP5,    KC_PAGE_UP, KC_UP,    KC_PAGE_DOWN, KC_NO,  KC_BSPC, \
       KC_NO,   KC_LSFT,  KC_NO,     KC_NO,   KC_NO,    KC_NO,    DOWN5,    KC_LEFT,    KC_DOWN,  KC_RIGHT,     KC_NO,  KC_MINUS, \
       KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,        KC_NO,  KC_NO, \
                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO

#define LAYOUT_LAYER_MODOPT                                                                     \
       KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_NO,    TO_BASE,  UP10,    KC_HOME,       LALT(KC_UP),    KC_END,        KC_NO,  LALT(KC_BSPC), \
       KC_NO,   KC_LSFT,  KC_NO,     KC_NO,   KC_NO,    KC_NO,    DOWN10,    LALT(KC_LEFT), LALT(KC_DOWN),  LALT(KC_RIGHT),KC_NO,  DBL_DSH, \
       KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,          KC_NO,         KC_NO,  KC_NO, \
                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO

#define LAYOUT_LAYER_MODCTRL                                                                     \
       KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_NO,    TO_BASE,  KC_NO,    KC_HOME,       LCTL(KC_UP),    KC_END,        KC_NO,  LCTL(KC_BSPC), \
       KC_NO,   KC_NO,  KC_LSFT,     KC_NO,   KC_NO,    KC_NO,    KC_NO,    LCTL(KC_LEFT), LCTL(KC_DOWN),  LCTL(KC_RIGHT),KC_NO,  ARROW, \
       KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,          KC_NO,         KC_NO,  KC_NO, \
                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO

#define LAYOUT_LAYER_MODCMD                                                                     \
       KC_TAB,   KC_SEMICOLON,KC_COMMA,          KC_DOT,  TO_BASE, KC_Y,    KC_F,    LCMD(KC_G),  KC_C,        KC_R,          KC_L,        KC_SLSH, \
       KC_ENT,   KC_A,        KC_O,              KC_E,    KC_U,    KC_I,    KC_D,    LCMD(KC_H),  KC_T,        LCMD(KC_N),    KC_S,        KC_SPACE, \
       KC_LSFT,  KC_QUOTE,    LCMD(KC_Q),        KC_J,    KC_K,    KC_X,    KC_B,    KC_M,        LCMD(KC_W),  (KC_V),        LCMD(KC_Z),  KC_RSFT, \
                      KC_NO, KC_HASH, KC_ESC, KC_LCAP, KC_AT, KC_BSLS

#define LAYOUT_LAYER_NUM                                                                    \
       LCTL(KC_TAB),       KC_DLR,     KC_LPRN,  KC_PERC, KC_RPRN,    KC_EQL,     KC_PLUS,    KC_7,    KC_8,    KC_9,    KC_L,  KC_SLSH, \
       LSFT(LCTL(KC_TAB)),  KC_TILD,    KC_LBRC,  KC_AMPR, KC_RBRC,    KC_BSLS,    KC_ASTR,    KC_4,    KC_5,    KC_6,    KC_S,  KC_SPACE, \
       KC_LSFT,             KC_EXLM,   KC_LCBR,  KC_MINUS,KC_RCBR,    KC_PIPE,    KC_UNDS,    KC_1,    KC_2,    KC_3,    KC_Z,  KC_RSFT, \
                            KC_NO, KC_GRV, KC_ESC, KC_0, KC_CIRC, KC_PIPE


/**
 * \brief Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     (LAYER_ALPHAS_QWERTY)
 */
// #define _POINTER_MOD(                                                  \
//     L00, L01, L02, L03, L04, L05, R06, R07, R08, R09, R1A, R1B,                 \
//     L10, L11, L12, L13, L14, L15, R16, R17, R18, R19, R2A, R2B,                \
//     L20, L21, L22, L23, L24, L25, R26, R27, R28, R29, R3A, R3B,                \
//     ...)                                                               \
//              L00,         L01,         L02,         L03,         L04,  L05,   \
//              R06,         R07,         R08,         R09,         R1A,  R1B, \
//              L10,         L11,         L12,         L13,         L14,  L15, \
//              R16,         R17,         R18,         R19,         R1A,  R1B, \
//       _L_PTR(L20),        L21,         L22,         L23,         L24,  L25, \
//              R26,         R27,         R28,         R29,         R2A,  R2B, \
//       __VA_ARGS__
// #define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(LAYOUT_LAYER_BASE),
  [LAYER_MOD] = LAYOUT_wrapper(LAYOUT_LAYER_MOD),
  [LAYER_MODOPT] = LAYOUT_wrapper(LAYOUT_LAYER_MODOPT),
  [LAYER_MODCTRL] = LAYOUT_wrapper(LAYOUT_LAYER_MODCTRL),
  [LAYER_MODCMD] = LAYOUT_wrapper(LAYOUT_LAYER_MODCMD),
  [LAYER_NUM] = LAYOUT_wrapper(LAYOUT_LAYER_NUM)
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef XIMI_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > XIMI_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > XIMI_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= XIMI_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // XIMI_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef XIMI_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    ximi_set_pointer_sniping_enabled(layer_state_cmp(state, XIMI_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // XIMI_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void pointing_device_init_kb(void) {
#ifdef PMW3360_CPI
    pointing_device_set_cpi(PMW3360_CPI);
#endif
}
