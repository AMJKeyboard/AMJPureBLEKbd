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

#define KB_REPORT_ARRAY_MAX 6

typedef struct kb_report_data{
    uint8_t modifier;
    uint8_t padding;
    uint8_t array[KB_REPORT_ARRAY_MAX];
    uint8_t pos;
} kb_report_data_t;

bool add_key(uint8_t code);
bool del_key(uint8_t code);

int8_t key_index(uint8_t code);

bool add_mod(uint8_t code);
bool del_mod(uint8_t code);
bool action_key_event(key_info_t *key_ev);
void action_report_init(void);
bool action_report_send(void);
