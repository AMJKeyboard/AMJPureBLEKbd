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

#include "nordic_common.h"
#include "nrf_log.h"

#include "keyboard_config.h"
#include "matrix.h"
#include "layer.h"


static bool layer_prev[MATRIX_ROWS][MATRIX_COLS] = {0};
static bool layer_current[MATRIX_ROWS][MATRIX_COLS] = {0};

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
                NRF_LOG_DEBUG("Layer diff: Row[%d] Col[%d] Value[%d] \r\n", key_ev.row, key_ev.col, key_ev.stat);
            }
        }
    }
}

void layer_init(void){
    matrix_init();
}

void layer_process_timeout_handler(void * p_context){
    UNUSED_PARAMETER(p_context);
    layer_read();
    layer_diff();
    memcpy(layer_prev, layer_current, sizeof(layer_prev));
}
