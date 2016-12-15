/*
 * =====================================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/03/2016 10:51:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#pragma once

#define ROW_PIN_0 4
#define ROW_PIN_1 5
#define ROW_PIN_2 6
#define ROW_PIN_3 7

#define COL_IC_DIN_PIN_0 10
#define COL_IC_DIN_PIN_1 9
#define COL_IC_CP_PIN 13
#define COL_IC_CE_PIN 12
#define COL_IC_PL_PIN 11

void matrix_init(void);

void matrix_select_row(uint8_t row);

void matrix_unselect_row(uint8_t row);

uint16_t matrix_read_col(void);
