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
#include "hids_service_report.h"
#include "ble_status.h"
#include "keycode.h"
#include "keymap_common.h"
#include "layer.h"
#include "actions.h"

#define INPUT_REPORT_KEYS_MAX_LEN        8

#ifdef KEYCODE_DEBUG
#define KEYCODE_DEBUG_LOG(...)  NRF_LOG_DEBUG(__VA_ARGS__)
#else
#define KEYCODE_DEBUG_LOG(...)
#endif

static kb_report_data_t kb_data = {0};

void action_report_init(void)
{
    memset(&kb_data, 0, sizeof(kb_data));
}


bool action_key_event(key_info_t *key_ev)
{
    bool ret_code = false;
    uint8_t code = get_keycode(key_ev->row, key_ev->col);
    if (IS_KEY(code)){
        if(key_ev->stat)
        {
            ret_code = add_key(code);
        }
        else
        {
            ret_code = del_key(code);
        }
        KEYCODE_DEBUG_LOG("KEY : 0x%X Status : %d Ret: %d \r\n" , code, key_ev->stat, ret_code);

    }
    else if (IS_MOD(code)){
        if(key_ev->stat)
        {
            ret_code = add_mod(code);
        }
        else
        {
            ret_code = del_mod(code);
        }
        KEYCODE_DEBUG_LOG("MOD : 0x%X Status : %d Ret: %d \r\n" , code, key_ev->stat, ret_code);
    }
    else if (IS_FN(code)){
        ret_code = false;
        KEYCODE_DEBUG_LOG("FN : 0x%X Status : %d \r\n" , code, key_ev->stat);
    }
    else {
        ret_code = false;
        KEYCODE_DEBUG_LOG("Other: 0x%X Status : %d \r\n", code, key_ev->stat);
    }
    return ret_code;
}


bool action_report_send(void)
{
    bool ret = false;
    uint8_t data[INPUT_REPORT_KEYS_MAX_LEN];
    memset(&data, 0, INPUT_REPORT_KEYS_MAX_LEN);
    memcpy(&data, &kb_data, kb_data.pos + 2);

    if (ble_has_connect()){
#ifdef HID_REPORT_DEBUG
        NRF_LOG_HEXDUMP_DEBUG(&data, INPUT_REPORT_KEYS_MAX_LEN);
#endif
        ret = send_key_report((uint8_t *)&data, INPUT_REPORT_KEYS_MAX_LEN);
#ifdef HID_REPORT_DEBUG
        if (!ret){
            NRF_LOG_INFO("send_key_report fail.\r\n");
        }
#endif
    }
    return ret;
}


int8_t key_index(uint8_t code)
{
    int8_t key_pos = -1;
    for(uint8_t i = 0; i < kb_data.pos; i++)
    {
        if(kb_data.array[i] == code)
        {
            key_pos = i;
        }
    }
    return key_pos;
}

bool add_key(uint8_t code){
    if (kb_data.pos < KB_REPORT_ARRAY_MAX && key_index(code) == -1){
        kb_data.array[kb_data.pos] = code;
        kb_data.pos ++;
        return true;
    }
    return false;
}

bool del_key(uint8_t code)
{
    int8_t key_pos = key_index(code);

    if(key_pos != -1)
    {
        for (uint8_t i = key_pos; i < (kb_data.pos - 1); i++)
        {
            kb_data.array[i] = kb_data.array[i+1];
        }

        if (kb_data.pos > 0)
        {
            kb_data.pos -- ;
        }
        return true;
    }
    return false;
}

bool add_mod(uint8_t code)
{
    kb_data.modifier |= MOD_BIT(code);
    return true;
}

bool del_mod(uint8_t code)
{
    kb_data.modifier &= ~MOD_BIT(code);
    return true;
}
