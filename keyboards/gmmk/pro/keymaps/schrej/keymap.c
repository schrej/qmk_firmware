#include QMK_KEYBOARD_H


enum {
    TD_MEDIA,
};

void tap_media(qk_tap_dance_state_t *state, void *user_data) {
	switch (state->count) {
		case 2:
			tap_code(KC_MNXT);
			break;
		case 3:
			tap_code(KC_MPRV);
			break;
		default:
			tap_code(KC_MPLY);
			break;
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_MEDIA] = ACTION_TAP_DANCE_FN(tap_media),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.

	[0] = LAYOUT(
		KC_ESC,          KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5, KC_F6, KC_F7,   KC_F8,    KC_F9,    KC_F10,  KC_F11,  KC_F12,  TD(TD_MEDIA),   KC_MUTE,
		KC_GRV,          KC_1,    KC_2,    KC_3,   KC_4,    KC_5,  KC_6,  KC_7,    KC_8,     KC_9,     KC_0,    KC_MINS, KC_EQL,  KC_BSPC,        KC_DEL,
		KC_TAB,          KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,  KC_Y,  KC_U,    KC_I,     KC_O,     KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_PGUP,
		LCTL_T(KC_CAPS), KC_A,    KC_S,    KC_D,   KC_F,    KC_G,  KC_H,  KC_J,    KC_K,     KC_L,     KC_SCLN, KC_QUOT,          KC_ENT,         KC_PGDN,
		KC_LSFT,                  KC_Z,    KC_X,    KC_C,   KC_V,  KC_B,  KC_N,    KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP, KC_END,
		KC_LCTL,         KC_LGUI, KC_LALT,                         KC_SPC,                             KC_RALT, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

	
	[1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT,          KC_ENT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
	if (layer_state_is(1)) {
		if (clockwise) {
			tap_code(KC_DOWN);
		} else {
			tap_code(KC_UP);
		}
	} else {
		if (clockwise) {
			tap_code(KC_VOLU);
		} else {
			tap_code(KC_VOLD);
		}
	}
    return true;
}
