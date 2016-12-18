/*
 * =====================================================================================
 *
 *       Filename:  layers.h
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

typedef struct key_info {
    uint8_t col;
    uint8_t row;
    uint8_t stat;
} key_info_t;

void layer_init(void);
void layer_process_timeout_handler(void * p_context);
bool layer_key_check(key_info_t * key_ev);
