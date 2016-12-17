/*
 * =====================================================================================
 *
 *       Filename:  battery_service.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/12/2016 07:53:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdint.h>
#include "nordic_common.h"
#include "nrf_delay.h"
#include "nrf_adc.h"
#include "nrf_log.h"

#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_bas.h"

#include "app_timer.h"
#include "app_timer_appsh.h"
#include "app_error.h"
#include "battery_service.h"

#ifndef BATTERY_ADC_INPUT_PIN
#define BATTERY_ADC_INPUT_PIN NRF_ADC_CONFIG_INPUT_2
#endif

extern ble_bas_t  m_bas;

/**@brief Function for initializing Battery Service.
 */
void bas_init(void)
{
    uint32_t       err_code;
    ble_bas_init_t bas_init_obj;

    memset(&bas_init_obj, 0, sizeof(bas_init_obj));

    bas_init_obj.evt_handler          = NULL;
    bas_init_obj.support_notification = true;
    bas_init_obj.p_report_ref         = NULL;
    bas_init_obj.initial_batt_level   = 100;

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&bas_init_obj.battery_level_char_attr_md.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&bas_init_obj.battery_level_char_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&bas_init_obj.battery_level_char_attr_md.write_perm);

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&bas_init_obj.battery_level_report_read_perm);

    err_code = ble_bas_init(&m_bas, &bas_init_obj);
    APP_ERROR_CHECK(err_code);
}

void bas_adc_init(void)
{

    nrf_adc_config_t adc_config = NRF_ADC_CONFIG_DEFAULT;
    adc_config.resolution = NRF_ADC_CONFIG_RES_8BIT;
    nrf_adc_configure(&adc_config);
}

/**@brief Function for performing a battery measurement, and update the Battery Level characteristic in the Battery Service.
 */
void battery_level_update(void)
{
    uint32_t err_code;
    uint8_t  battery_level;
    uint16_t adc_value = -1;
    nrf_adc_enable();
    adc_value = nrf_adc_convert_single (BATTERY_ADC_INPUT_PIN);
    nrf_adc_disable();
    battery_level = (uint8_t)adc_value;
    err_code = ble_bas_battery_level_update(&m_bas, battery_level);
    if ((err_code != NRF_SUCCESS) &&
        (err_code != NRF_ERROR_INVALID_STATE) &&
        (err_code != BLE_ERROR_NO_TX_PACKETS) &&
        (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
       )
    {
        APP_ERROR_HANDLER(err_code);
    }
}

/**@brief Function for handling the Battery measurement timer timeout.
 *
 * @details This function will be called each time the battery level measurement timer expires.
 *
 * @param[in]   p_context   Pointer used for passing some arbitrary information (context) from the
 *                          app_start_timer() call to the timeout handler.
 */
void battery_level_meas_timeout_handler(void * p_context)
{
    UNUSED_PARAMETER(p_context);
    battery_level_update();
}
