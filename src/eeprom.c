/*
 * =====================================================================================
 *
 *       Filename:  eeprom.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/19/2016 10:03:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdint.h>

#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "nrf_delay.h"

#include "keyboard_config.h"
#include "eeprom.h"

#define TWI_INSTANCE_ID     0

#define EEPROM_BASE_ADDRESS  0b10100000
#define EEPROM_DELAY  100

static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

void nrf_drv_twi_evt_handler(nrf_drv_twi_evt_t const *p_event, void *p_context);

void nrf_drv_twi_evt_handler(nrf_drv_twi_evt_t const *p_event, void *p_context)
{
    if (p_event->type == NRF_DRV_TWI_EVT_DONE ){
        NRF_LOG_DEBUG("NRF_DRV_TWI_EVT_DONE \r\n");
    }
    else if (p_event->type == NRF_DRV_TWI_EVT_ADDRESS_NACK ){
        NRF_LOG_DEBUG("NRF_DRV_TWI_EVT_ADDRESS_NACK \r\n");
    }
    else if (p_event->type == NRF_DRV_TWI_EVT_DATA_NACK ){
        NRF_LOG_DEBUG("NRF_DRV_TWI_EVT_DATA_NACK \r\n");
    }
}

/**
 * @brief TWI initialization.
 */
void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_config = {
       .scl                = GPIO_EEPROM_SCL_PIN_NUMBERS,
       .sda                = GPIO_EEPROM_SDA_PIN_NUMBERS,
       .frequency          = NRF_TWI_FREQ_400K,
       .interrupt_priority = 1,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, &nrf_drv_twi_evt_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}

uint8_t twi_eeprom_slave_address(eeprom_block_e block)
{
    uint8_t i2c_address = (EEPROM_BASE_ADDRESS | block )>>1;
    return i2c_address;
}

void twi_eeprom_write_byte(eeprom_block_e block, uint16_t address, uint8_t data)
{
    ret_code_t err_code;
    uint8_t slave_address = twi_eeprom_slave_address(block);
    uint8_t tx_data[] = {address >> 8, address & 0xFF, data};
    err_code = nrf_drv_twi_tx(&m_twi, slave_address, (uint8_t *)&tx_data, sizeof(tx_data), false);
    APP_ERROR_CHECK(err_code);
    nrf_delay_us(EEPROM_DELAY);
}


uint8_t twi_eeprom_read_byte(eeprom_block_e block, uint16_t address)
{
    ret_code_t err_code;
    uint8_t data = 0xFF;
    uint8_t tx_data[] = {address >> 8, address & 0xFF};
    uint8_t slave_address = twi_eeprom_slave_address(block);
    err_code = nrf_drv_twi_tx(&m_twi, slave_address, (uint8_t *)&tx_data, sizeof(tx_data), true);
    APP_ERROR_CHECK(err_code);
    nrf_delay_us(EEPROM_DELAY);
    err_code = nrf_drv_twi_rx(&m_twi, slave_address, &data, sizeof(data));
    APP_ERROR_CHECK(err_code);
    nrf_delay_us(EEPROM_DELAY);
    return data;
}

