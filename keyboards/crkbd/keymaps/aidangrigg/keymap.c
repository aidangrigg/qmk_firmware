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

// Copyright 2021 Nicolas Druoton (druotoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "transactions.h"

// global
#include "gui_state.h"
#include "boot.h"
#include "navi_logo.h"

#include "draw_helper.h"
#include "fast_random.h"

// left side
#include "layer_frame.h"
#include "burst.h"

// right side
#include "ring.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌──────┬───┬───┬─────┬─────┬─────────┐   ┌─────────┬──────┬──────┬───┬───┬──────┐
//    │ tab  │ q │ w │  e  │  r  │    t    │   │    y    │  u   │  i   │ o │ p │ ent  │
//    ├──────┼───┼───┼─────┼─────┼─────────┤   ├─────────┼──────┼──────┼───┼───┼──────┤
//    │ lctl │ a │ s │  d  │  f  │    g    │   │    h    │  j   │  k   │ l │ ' │ lalt │
//    ├──────┼───┼───┼─────┼─────┼─────────┤   ├─────────┼──────┼──────┼───┼───┼──────┤
//    │ lgui │ z │ x │  c  │  v  │    b    │   │    n    │  m   │  ,   │ . │ / │ lgui │
//    └──────┴───┴───┼─────┼─────┼─────────┤   ├─────────┼──────┼──────┼───┴───┴──────┘
//                   │ esc │ spc │ MO(SYM) │   │ MO(NUM) │ lsft │ bspc │
//                   └─────┴─────┴─────────┘   └─────────┴──────┴──────┘
[QWERTY] = LAYOUT_split_3x6_3(
  KC_TAB  , KC_Q , KC_W , KC_E   , KC_R   , KC_T    ,     KC_Y    , KC_U    , KC_I    , KC_O   , KC_P     , KC_ENT ,
  KC_LCTL , KC_A , KC_S , KC_D   , KC_F   , KC_G    ,     KC_H    , KC_J    , KC_K    , KC_L   , KC_QUOTE , KC_LALT,
  KC_LGUI , KC_Z , KC_X , KC_C   , KC_V   , KC_B    ,     KC_N    , KC_M    , KC_COMM , KC_DOT , KC_SLSH  , KC_LGUI,
                          KC_ESC , KC_SPC , MO(SYM) ,     MO(NUM) , KC_LSFT , KC_BSPC
),

//    ┌──────┬───┬───┬───┬───┬─────────┐   ┌─────────┬───────────────┬───────────────┬───────────────┬──────┬──────┐
//    │ tab  │ [ │ 7 │ 8 │ 9 │    ]    │   │   no    │      no       │      no       │      no       │  no  │ ent  │
//    ├──────┼───┼───┼───┼───┼─────────┤   ├─────────┼───────────────┼───────────────┼───────────────┼──────┼──────┤
//    │ lctl │ ; │ 4 │ 5 │ 6 │    =    │   │   ent   │ OSM(MOD_LSFT) │ OSM(MOD_LCTL) │ OSM(MOD_LALT) │ lgui │ lalt │
//    ├──────┼───┼───┼───┼───┼─────────┤   ├─────────┼───────────────┼───────────────┼───────────────┼──────┼──────┤
//    │ lgui │ . │ 1 │ 2 │ 3 │    \    │   │ CW_TOGG │      no       │      no       │      no       │  no  │ lgui │
//    └──────┴───┴───┼───┼───┼─────────┤   ├─────────┼───────────────┼───────────────┼───────────────┴──────┴──────┘
//                   │ 0 │ - │ MO(NAV) │   │ MO(NAV) │      no       │      no       │
//                   └───┴───┴─────────┘   └─────────┴───────────────┴───────────────┘
[NUM] = LAYOUT_split_3x6_3(
  KC_TAB  , KC_LBRC , KC_7 , KC_8 , KC_9     , KC_RBRC ,     XXXXXXX , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX , KC_ENT ,
  KC_LCTL , KC_SCLN , KC_4 , KC_5 , KC_6     , KC_EQL  ,     KC_ENT  , OSM(MOD_LSFT) , OSM(MOD_LCTL) , OSM(MOD_LALT) , KC_LGUI , KC_LALT,
  KC_LGUI , KC_DOT  , KC_1 , KC_2 , KC_3     , KC_BSLS ,     CW_TOGG , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX , KC_LGUI,
                             KC_0 , KC_MINUS , MO(NAV) ,     MO(NAV) , XXXXXXX       , XXXXXXX
),

//    ┌──────┬──────┬───────────────┬───────────────┬───────────────┬─────────┐   ┌─────────┬───┬───┬───┬───┬──────┐
//    │ tab  │  no  │      no       │      no       │      no       │   no    │   │    {    │ ( │ * │ & │ } │ ent  │
//    ├──────┼──────┼───────────────┼───────────────┼───────────────┼─────────┤   ├─────────┼───┼───┼───┼───┼──────┤
//    │ lctl │ lgui │ OSM(MOD_LALT) │ OSM(MOD_LCTL) │ OSM(MOD_LSFT) │   tab   │   │    +    │ ^ │ % │ $ │ : │ lalt │
//    ├──────┼──────┼───────────────┼───────────────┼───────────────┼─────────┤   ├─────────┼───┼───┼───┼───┼──────┤
//    │ lgui │  no  │      no       │      no       │      no       │ CW_TOGG │   │    |    │ # │ @ │ ! │ ~ │ lgui │
//    └──────┴──────┴───────────────┼───────────────┼───────────────┼─────────┤   ├─────────┼───┼───┼───┴───┴──────┘
//                                  │      no       │      no       │ MO(NAV) │   │ MO(NAV) │ _ │ ) │
//                                  └───────────────┴───────────────┴─────────┘   └─────────┴───┴───┘
[SYM] = LAYOUT_split_3x6_3(
  KC_TAB  , XXXXXXX , XXXXXXX       , XXXXXXX       , XXXXXXX       , XXXXXXX ,     KC_LCBR , KC_LPRN , KC_ASTR , KC_AMPR , KC_RCBR  , KC_ENT ,
  KC_LCTL , KC_LGUI , OSM(MOD_LALT) , OSM(MOD_LCTL) , OSM(MOD_LSFT) , KC_TAB  ,     KC_PLUS , KC_CIRC , KC_PERC , KC_DLR  , KC_COLON , KC_LALT,
  KC_LGUI , XXXXXXX , XXXXXXX       , XXXXXXX       , XXXXXXX       , CW_TOGG ,     KC_PIPE , KC_HASH , KC_AT   , KC_EXLM , KC_TILDE , KC_LGUI,
                                      XXXXXXX       , XXXXXXX       , MO(NAV) ,     MO(NAV) , KC_UNDS , KC_RPRN
),

//    ┌─────────┬────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬──────┬────┬────┐
//    │ QK_BOOT │ no │  no  │ btn1 │ btn2 │  no  │   │ lalt │ pgdn │ pgup │  no  │ no │ no │
//    ├─────────┼────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼────┼────┤
//    │   no    │ no │ ms_l │ ms_d │ ms_u │ ms_r │   │ left │ down │  up  │ rght │ no │ no │
//    ├─────────┼────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼────┼────┤
//    │   no    │ no │  no  │ wh_d │ wh_u │  no  │   │  no  │  no  │  no  │  no  │ no │ no │
//    └─────────┴────┴──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┴────┴────┘
//                          │ lctl │ lsft │  no  │   │  no  │ spc  │ lalt │
//                          └──────┴──────┴──────┘   └──────┴──────┴──────┘
[NAV] = LAYOUT_split_3x6_3(
  QK_BOOT , XXXXXXX , XXXXXXX , KC_BTN1 , KC_BTN2 , XXXXXXX ,     KC_LALT , KC_PGDN , KC_PGUP , XXXXXXX  , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R ,     KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , KC_WH_D , KC_WH_U , XXXXXXX ,     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX,
                                KC_LCTL , KC_LSFT , XXXXXXX ,     XXXXXXX , KC_SPC  , KC_LALT
)
};

// clang-format on

// sync transport
typedef struct _sync_keycode_t {
    uint16_t keycode;
} sync_keycode_t;

// force rigth side to update
bool b_sync_need_send = false;

// last keycode typed
sync_keycode_t last_keycode;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // vertical orientation
    return OLED_ROTATION_270;
}

void render(gui_state_t t) {
    // logo
    render_logo(t);

#if IS_LEFT
    // left side
    render_layer_frame(t);
    render_gears();

    decay_scope();
    render_scope(t);
#endif

#if IS_RIGHT
    // right side
    render_circle(t);
#endif
}

void update(uint16_t keycode) {
#if IS_LEFT
    update_scope();
#endif

#if IS_RIGHT
    update_circle(keycode);
#endif
}

void reset(void) {
#if IS_LEFT
    reset_scope();
#endif

#if IS_RIGHT
    reset_ring();
#endif
}

void set_wackingup_mode_clean(void) {
    oled_clear();
    reset();
}

bool oled_task_user(void) {
    gui_state_t t = get_gui_state();

    // in sleep mode => turn display off
    if (t == _SLEEP) {
        oled_off();
        return false;
    }

    // not in sleep mode => screen is on
    oled_on();

#ifdef WITH_BOOT
    // in booting mode => display booting animation
    if (t == _BOOTING) {
        bool boot_finished = render_boot();
        if (boot_finished) {
            // end of the boot : wacking up
            set_wackingup_mode_clean();
            update_gui_state();
        }
        return false;
    }
#endif

    // in halting mode => display booting animation
    if (t == _HALTING) {
        render_halt();
        return false;
    }

    render(t);
    return false;
}

void process_key(uint16_t keycode) {
    // update screen with the new key
    update(keycode);

    gui_state_t t = get_gui_state();

    if (t == _IDLE) {
        // wake up animation
        reset();
    }

    if (t == _BOOTING || t == _HALTING) {
        // cancel booting or halting : waking_up
        set_wackingup_mode_clean();
    }

    if (t == _SLEEP) {
        // boot sequence
        set_wackingup_mode_clean();
        reset_boot();
    }

    update_gui_state();
}

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const sync_keycode_t* m2s = (const sync_keycode_t*)in_data;
    // get the last char typed on left side and update the right side
    process_key(m2s->keycode);
}

void keyboard_post_init_user(void) {
    // callback for tranport sync data
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}

void housekeeping_task_user(void) {
    // only for master side
    if (!is_keyboard_master()) return;

    // only if a new char was typed
    if (!b_sync_need_send) return;

    // send the char to the slave side : sync is done
    if (transaction_rpc_send(USER_SYNC_A, sizeof(last_keycode), &last_keycode)) {
        b_sync_need_send = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        // master : store keycode to sent to the other side to be process_key
        last_keycode.keycode = keycode;
        b_sync_need_send     = true;

        // gui process the input
        process_key(keycode);
    }
    return true;
}

#if IS_LEFT
layer_state_t layer_state_set_user(layer_state_t state) {
    // update the frame with the layer name
    update_layer_frame(state);
    return state;
}
#endif

