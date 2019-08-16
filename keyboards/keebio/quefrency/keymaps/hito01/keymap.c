#include QMK_KEYBOARD_H
#include <print.h>

extern keymap_config_t keymap_config;

enum custom_keycodes {
  INCCOL = SAFE_RANGE,
  DECCOL,
  LARROW,
  RARROW,
  LDARROW,
  RDARROW,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_65(
    KC_GRV,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_INS, \
    KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, \
    KC_GESC, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,  KC_PGUP, \
    KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,   KC_PGDN, \
    KC_LCTL, TG(1), KC_LALT, KC_LGUI, LT(1, KC_SPC),       KC_SPC,  KC_SPC,  KC_RGUI, KC_RCTL, MO(1),    KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [1] = LAYOUT_65(
    RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL,  KC_BSPC, _______, \
    RGB_TOG, RGB_MOD, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, LARROW,  RARROW,  _______, _______, \
    _______, _______, KC_LEFT, INCCOL,  DECCOL,  _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, LDARROW, RDARROW, _______, _______, _______, _______, \
    KC_TILD, KC_TRNS, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  )
};

void keyboard_post_init_user(void) {
  debug_enable=true;

  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(206, 255, 255);
}

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case 1:
      rgblight_sethsv_noeeprom(35, 255, 255);
      break;
    default:
      rgblight_sethsv_noeeprom(206, 255, 255);
      default_layer_state_set_user(default_layer_state);
      break;
  }

  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    #ifdef CONSOLE_ENABLE
      uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u, hue: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, rgblight_get_hue());
    #endif
    switch (keycode) {
      case INCCOL:
        rgblight_increase_hue_noeeprom();
        break;
      case DECCOL:
        rgblight_decrease_hue_noeeprom();
        break;
      case LARROW:
        SEND_STRING ("<-");
        break;
      case RARROW:
        SEND_STRING ("->");
        break;
      case LDARROW:
        SEND_STRING ("<=");
        break;
      case RDARROW:
        SEND_STRING ("=>");
        break;
    }
  }
  return true;
};
