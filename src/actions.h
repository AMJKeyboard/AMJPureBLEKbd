/*
 * =====================================================================================
 *
 *       Filename:  actions.h
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

#define KB_REPORT_ARRAY_MAX 7

typedef struct kb_report_data{
    uint8_t modifier;
    uint8_t array[KB_REPORT_ARRAY_MAX];
    uint8_t pos;
} kb_report_data_t;

bool add_key(uint8_t code);
bool del_key(uint8_t code);

int8_t key_index(uint8_t code);

bool add_mod(uint8_t code);
bool del_mod(uint8_t code);
void kb_report_init(void);
void kb_report_debug(void);
bool action_key_event(key_info_t *key_ev);
