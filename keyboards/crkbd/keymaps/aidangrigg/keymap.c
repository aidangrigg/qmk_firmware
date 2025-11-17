/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    COLEMAK_DH,
    QWERTY,
    NUM,
    SYM,
    NAV,
};

// combos
const uint16_t PROGMEM tab_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM l_win_combo[] = {KC_A, KC_R, COMBO_END};
const uint16_t PROGMEM l_alt_combo[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM l_ctl_combo[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM r_win_combo[] = {KC_O, KC_I, COMBO_END};
const uint16_t PROGMEM r_alt_combo[] = {KC_I, KC_E, COMBO_END};
const uint16_t PROGMEM r_ctl_combo[] = {KC_E, KC_N, COMBO_END};

combo_t key_combos[] = {
    COMBO(tab_combo, KC_TAB),
    COMBO(l_win_combo, KC_LGUI),
    COMBO(l_alt_combo, KC_LALT),
    COMBO(l_ctl_combo, KC_LCTL),
    COMBO(r_win_combo, KC_LGUI),
    COMBO(r_alt_combo, KC_LALT),
    COMBO(r_ctl_combo, KC_LCTL)
};

uint8_t combo_ref_from_layer(uint8_t layer){
    switch (layer) {
        case QWERTY: return COLEMAK_DH;
        default: return layer;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [COLEMAK_DH] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                          KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                          KC_M,    KC_N,    KC_E,    KC_I,   KC_O,     XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,                          KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                  LT(NUM, KC_ESC), KC_SPC, KC_TAB,  KC_BSPC,   KC_LSFT, LT(SYM, KC_ENT)
                                // `----------------------------'  `--------------------------'
  ),
  [QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                  LT(NUM, KC_ESC), KC_SPC, KC_TAB,  KC_BSPC,   KC_LSFT, LT(SYM, KC_ENT)
                                // `----------------------------'  `--------------------------'
  ),


    [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                     XXXXXXX,  KC_4, KC_5, KC_6, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_1, KC_2, KC_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    KC_BSPC, KC_MINS, LT(NAV, KC_0)
                                      //`--------------------------'  `--------------------------'
  ),


    /*     KC.F13,  KC.F14,   KC.F15,  KC.F16,  KC.F17,  KC.F18,                          KC.F19,  KC.F20, KC.F21,  KC.F22,  KC.F23,  KC.F24, */
    /*     KC.TRNS, KC.QUOT,  KC.LABK, KC.RABK, KC.DQUO, KC.DOT,                          KC.AMPR, CC,     KC.LBRC, KC.RBRC, KC.PERC, KC.NO, */
    /*     KC.TRNS, KC.EXLM,  KC.MINS, KC.PLUS, KC.EQL,  KC.HASH,                         KC.PIPE, KC.COLN,KC.LPRN, KC.RPRN, KC.QUES, KC.TRNS, */
    /*     KC.TRNS, KC.CIRC,  KC.BSLS, KC.ASTR, KC.SLSH, BKDIR,                           KC.TILD, KC.DLR, KC.LCBR, KC.RCBR, KC.AT,   KC.TRNS, */
    /*                        KC.LPRN, KC.RPRN,                                                           KC.NO, KC.NO, */
    /*                                                 KC.MO(4),KC.UNDS,      KC.TRNS, KC.TRNS, */
    /*                                                 KC.TRNS, KC.CW,        KC.TRNS, KC.TRNS, */
    /*                                                 KC.LGUI, KC.LGUI,      KC.RGUI, KC.RGUI */
    /* ], */

    [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_QUOT, KC_LABK, KC_RABK, KC_DQUO, KC_DOT,                       KC_AMPR, XXXXXXX, KC_LBRC, KC_RBRC, KC_PERC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL, KC_HASH,                       KC_PIPE, KC_COLN,KC_LPRN, KC_RPRN, KC_QUES, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_CIRC, KC_BSLS, KC_ASTR, KC_SLSH, XXXXXXX,                      KC_TILD, KC_DLR, KC_LCBR, KC_RCBR, KC_AT,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                  LT(NAV, KC_ESC), KC_TAB, KC_UNDS,     _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, DF(QWERTY), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DF(COLEMAK_DH), XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        XXXXXXX, _______,  KC_SPC,     KC_BSPC,   _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )

};
