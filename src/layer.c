/*
 * =====================================================================================
 *
 *       Filename:  layers.c
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

#include "nrf.h"
#include "nordic_common.h"
#include "nrf_gpiote.h"
#include "nrf_gpio.h"

#include "nrf_log.h"

#include "keyboard_config.h"
#include "matrix.h"
#include "layer.h"
#include "actions.h"



static bool layer_key_info_match(key_info_t * key_ev);
static void layer_read(void);
static void layer_diff(void);

uint8_t layer_prev[MATRIX_ROWS][MATRIX_COLS];
uint8_t layer_current[MATRIX_ROWS][MATRIX_COLS];

static void layer_read(void){
    uint32_t cols_value = -1;
    for (uint8_t i=0; i < MATRIX_ROWS; i++)
    {
        matrix_select_row(i);
        cols_value = matrix_read_col();
        for (uint8_t j=0; j < MATRIX_COLS; j++)
        {
            layer_current[i][j] = (cols_value & 1<<j) ? 1 : 0;
        }
        matrix_unselect_row(i);
    }
}
bool layer_key_check(key_info_t *key_ev){
    layer_read();
    return layer_key_info_match(key_ev);
}


static bool layer_key_info_match(key_info_t *key_ev){
    return layer_current[key_ev->row][key_ev->col] == key_ev->stat;
}



static void layer_diff(void){
    for (uint8_t i=0; i < MATRIX_ROWS; i++)
    {
        for (uint8_t j=0; j < MATRIX_COLS; j++)
        {

            if (layer_current[i][j] != layer_prev[i][j])
            {
                key_info_t key_ev;
                key_ev.row = i;
                key_ev.col = j;
                key_ev.stat = layer_current[i][j];
                action_key_event(&key_ev);
            }
        }
    }
}

void layer_init(void){
    matrix_init();
    memset(layer_prev, 0, sizeof(layer_prev));
    memset(layer_current,0, sizeof(layer_current));
    action_report_init();
}

void layer_process_timeout_handler(void * p_context){
    UNUSED_PARAMETER(p_context);
    layer_read();
    layer_diff();
    memcpy(layer_prev, layer_current, sizeof(layer_prev));
    action_report_send();
}
