/*
 * =====================================================================================
 *
 *       Filename:  actions.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/15/2016 12:28:54 PM
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

#include "nordic_common.h"
#include "nrf_log.h"

#include "keyboard_config.h"
#include "keycode.h"
#include "keymap_common.h"
#include "layer.h"
#include "actions.h"

#ifndef KEYCODE_DEBUG(...)
#define KEYCODE_DEBUG(...)  NRF_LOG_DEBUG(__VA_ARGS__)
#endif


void action_key_event(key_info_t *key_ev){
    uint8_t code = get_keycode(key_ev->row, key_ev->col);
    if (IS_KEY(code)){
        KEYCODE_DEBUG("KEY : 0x%X Status : %s \r\n" , code, key_ev->stat ? "press": "release");
    }
    else if (IS_MOD(code)){
        KEYCODE_DEBUG("MOD : 0x%X Status : %s \r\n" , code, key_ev->stat ? "press": "release");
    }
    else if (IS_FN(code)){
        KEYCODE_DEBUG("FN : 0x%X Status : %s \r\n" , code, key_ev->stat ? "press": "release");
    }
    else {
        KEYCODE_DEBUG("Other: 0x%X Status : %s \r\n", code, key_ev->stat ? "press": "release");
    }
}
