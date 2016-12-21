/*
 * =====================================================================================
 *
 *       Filename:  nus_service.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/21/2016 09:08:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

void nus_init(void);
void nus_data_handler(ble_nus_t * p_nus, uint8_t * p_data, uint16_t length);
void nus_send(uint8_t *p_data, uint16_t length);
