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

#include "keyboard_config.h"
#include "matrix.h"

static uint16_t layer_prev[MATRIX_ROWS] = {0};
static uint16_t layer_current[MATRIX_ROWS] = {0};
static uint16_t layer_ghost[MATRIX_ROWS] = {0};

static void layer_read(void){
    for (uint8_t i=0; i < MATRIX_ROWS; i++){
        matrix_select_row(i);
        layer_current[i] = matrix_read_col();
        matrix_unselect_row(i);
    }
}

static void layers_diff(void){

}


void layers_process(void){
    layer_read();
}

void layers_init(void){
    matrix_init();
}
