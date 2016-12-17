/*
 * =====================================================================================
 *
 *       Filename:  keymap_default.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/15/2016 12:01:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdint.h>

#include "keyboard_config.h"
#include "keycode.h"
#include "keymap_common.h"

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     * ,-------------------------------------------------.
     * |Esc | Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P| Bs  |
     * |-------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  Ent |
     * |-------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  .| SFT|FN0|
     * |-------------------------------------------------|
     * |Tab |Win |Alt |        Space            |Alt |Win|
     * `-------------------------------------------------'
     */
    KEYMAP(
        ESC, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P, BSPC,\
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,       ENT,\
        LSFT,     Z,   X,   C,   V,   B,   N,   M, DOT,RSFT,  FN0,\
        TAB,LGUI,LALT,          SPC,                  RALT, RGUI),

    /* Keymap 1: FN Layer
     * ,-------------------------------------------------.
     * | ` |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|Del  |
     * |-------------------------------------------------|
     * |      | [ | Up | ] | \| , | . | / | ; | '  |     |
     * |-------------------------------------------------|
     * |      |Lef|Dow|Rig|VolU|VoD|Mut| - | = |     |   |
     * |-------------------------------------------------|
     * |    |    |    |         FN1            |    | FN2|
     * `-------------------------------------------------'
     */
    KEYMAP(
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,  DEL,\
        TRNS,   LBRC,UP,RBRC,BSLS,COMM,DOT,SLSH,SCLN,  QUOT,  TRNS,\
        TRNS,  LEFT,DOWN,RGHT,VOLU,VOLD,MUTE,MINS,EQL, TRNS, TRNS,\
        TRNS,TRNS,TRNS,          FN1,                   TRNS,FN2)
};
