// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "timer.h"

enum custom_layers {
    WIN_BASE,
    WIN_FN,
    MAC_BASE,
    MAC_FN,
    ADVANCED_MODE
};

enum custom_keycodes {
    BT_DEV1 = SAFE_RANGE,               // BT Device 1
    BT_DEV2,               // BT Device 2
    BT_DEV3,               // BT Device 3
    BT_DEV4,               // BT Device 4
    BT_DEV5,               // BT Device 5
    BT_DEV_24G,            // 2.4G
    BT_DEV_USB,            // USB
    BATTERY_CHECK,
    CHARGING_CHECK,
    RESET_FACTORY
};

// Keymap definition
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_BASE] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_MUTE,
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(WIN_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [WIN_FN] = LAYOUT(
        EE_CLR, KC_MSEL, KC_VOLD, KC_VOLU, KC_MUTE, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MAIL, KC_WWW_HOME, KC_CALC, KC_WWW_SEARCH, KC_INS, KC_MUTE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, KC_END,
        _______, BT_DEV1, BT_DEV2, BT_DEV3, BT_DEV_24G, _______, _______, _______, _______, _______, _______, _______, RGB_HUI, RGB_MOD, KC_PSCR,
        _______, _______,  DF(MAC_BASE), _______, _______, _______, _______, _______, _______, _______, _______, _______, CHARGING_CHECK, KC_PAUS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  MO(ADVANCED_MODE), RGB_VAI,
        _______, 0x700b, _______, BATTERY_CHECK, _______, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI
    ),

    [MAC_BASE] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_MUTE,
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_HOME,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,  KC_ENT, KC_PGDN,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, MO(MAC_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [MAC_FN] = LAYOUT(
       EE_CLR, KC_BRID, KC_BRIU, _______, _______, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_INS, KC_MUTE,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, KC_END,
       _______, BT_DEV1, BT_DEV2, BT_DEV3, BT_DEV_24G, _______, _______, _______, _______, _______, _______, _______, RGB_HUI, RGB_MOD, KC_PSCR,
       _______, DF(WIN_BASE), _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, CHARGING_CHECK, KC_PAUS,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  MO(ADVANCED_MODE), RGB_VAI,
       _______, _______, _______, BATTERY_CHECK, _______, _______, _______, RGB_SPD, RGB_VAD, RGB_SPI
    ),

    [ADVANCED_MODE] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [4] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif



bool is_reset_mode = false;  // Track if reset mode is active
uint16_t reset_timer;        // Timer for tracking hold duration

// Process custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        
        case RESET_FACTORY:
            if (record->event.pressed) {
                is_reset_mode = true;
                reset_timer = timer_read();
            } else {
                is_reset_mode = false;
            }
            return false;
        case BT_DEV1:
            if (record->event.pressed) {
                // Add your logic for BT_DEV1 here
            }
            return false;
        case BT_DEV2:
            if (record->event.pressed) {
                // Add your logic for BT_DEV2 here
            }
            return false;
        case BT_DEV3:
            if (record->event.pressed) {
                // Add your logic for BT_DEV3 here
            }
            return false;
        case BT_DEV_24G:
            if (record->event.pressed) {
                // Add your logic for BT_DEV_24G here
            }
            return false;
        case BT_DEV_USB:
            if (record->event.pressed) {
                // Add your logic for BT_DEV_USB here
            }
            return false;
        case BATTERY_CHECK:
            if (record->event.pressed) {
                // Add your logic for BATTERY_CHECK here
            }
            return false;
    }
    return true;  // Process all other keycodes as usual
}


bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case DF(WIN_BASE):
            if (record->event.pressed) {
                set_single_persistent_default_layer(WIN_BASE);
            }
            return false;
        case DF(MAC_BASE):
            if (record->event.pressed) {
                set_single_persistent_default_layer(MAC_BASE);
            }
            return false;
        default:
            return true;
    }
}

// Scan function to handle factory reset timing
void matrix_scan_user(void) {
    if (is_reset_mode) {
        if (timer_elapsed(reset_timer) > 5000) { // 5000 ms = 5 seconds
            eeconfig_init(); // Perform factory reset
            reset_keyboard(); // Restart the keyboard
            is_reset_mode = false;
        }
    }
}
