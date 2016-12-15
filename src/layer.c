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

#include "keyboard_config.h"
#include "matrix.h"

static uint8_t layer_prev[MATRIX_ROWS][MATRIX_COLS] = {0};
static uint8_t layer_current[MATRIX_ROWS][MATRIX_COLS] = {0};
static uint8_t layer_ghost[MATRIX_ROWS][MATRIX_COLS] = {0};

static void layer_read(void){

    for (uint8_t i=0; i < MATRIX_ROWS; i++){
        matrix_select_row(i);
        layer_current[i] = matrix_read_col();
        matrix_unselect_row(i);
    }
}

void layer_process_timeout_handler(void * p_context){
    UNUSED_PARAMETER(p_context);
    layer_read();
}

static void layer_diff(void){

}

void layer_init(void){
    matrix_init();
}
