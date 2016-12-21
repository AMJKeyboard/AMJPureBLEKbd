/*
 * =====================================================================================
 *
 *       Filename:  uart_service.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/21/2016 08:30:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "nrf.h"
#include "nordic_common.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"

#include "nrf_log.h"

#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_nus.h"

#include "nus_service.h"

extern ble_nus_t m_nus;

void nus_data_handler(ble_nus_t * p_nus, uint8_t * p_data, uint16_t length)
{
    NRF_LOG_INFO("NUS_DATA read 0x%X len:%d \r\n", p_data[0],  length);
}

void nus_init(void)
{
    uint32_t       err_code;
    ble_nus_init_t nus_init;

    memset(&nus_init, 0, sizeof(nus_init));

    nus_init.data_handler = nus_data_handler;

    err_code = ble_nus_init(&m_nus, &nus_init);
    APP_ERROR_CHECK(err_code);
}


void nus_send(uint8_t *p_data, uint16_t length){
    uint32_t       err_code;
    err_code = ble_nus_string_send(&m_nus, p_data, length);
    APP_ERROR_CHECK(err_code);
}
