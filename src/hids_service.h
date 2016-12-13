/*
 * =====================================================================================
 *
 *       Filename:  hids_service.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/13/2016 10:14:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

void buffer_init(void);
uint32_t buffer_enqueue(ble_hids_t * p_hids,
                               uint8_t    * p_key_pattern,
                               uint16_t     pattern_len,
                               uint16_t     offset);
uint32_t buffer_dequeue(bool tx_flag);

void on_hid_rep_char_write(ble_hids_evt_t * p_evt);
void on_hids_evt(ble_hids_t * p_hids, ble_hids_evt_t * p_evt);
void keys_send(uint8_t key_pattern_len, uint8_t * p_key_pattern);
void key_scan_task(void);
void service_error_handler(uint32_t nrf_error);
