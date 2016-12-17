/*
 * =====================================================================================
 *
 *       Filename:  keymap.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/15/2016 11:44:12 AM
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

extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];

uint8_t keymap_default_layer = 0;


uint8_t get_keycode(uint8_t row, uint8_t col){
    return keymaps[keymap_default_layer][row][col];
}

