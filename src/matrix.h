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

void matrix_init(void);

void matrix_select_row(uint8_t row);

void matrix_unselect_row(uint8_t row);

uint16_t matrix_read_col(void);
