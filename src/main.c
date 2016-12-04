/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/03/2016 08:32:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_gpiote.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_delay.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_uart.h"
#include "nrf_log_ctrl.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"

#include "matrix.h"


#define GPIO_DEBUG_OUTPUT_PIN_NUMBER 2
#define GPIO_LED_OUTPUT_PIN_NUMBER 3
#define GPIO_BUTTON_INPUT_PIN_NUMBER 8
#define GPIO_TX_PIN_NUMBER 23
#define GPIO_RX_PIN_NUMBER 24

static nrf_drv_timer_t timer = NRF_DRV_TIMER_INSTANCE(0);


void timer_dummy_handler(nrf_timer_event_t event_type, void * p_context){}


void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    nrf_drv_gpiote_out_toggle(GPIO_DEBUG_OUTPUT_PIN_NUMBER);
}

static void led_blinking_setup()
{
    uint32_t compare_evt_addr;
    uint32_t gpiote_task_addr;
    nrf_ppi_channel_t ppi_channel;
    ret_code_t err_code;
    nrf_drv_gpiote_out_config_t config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(false);

    err_code = nrf_drv_gpiote_out_init(GPIO_LED_OUTPUT_PIN_NUMBER, &config);
    APP_ERROR_CHECK(err_code);


    nrf_drv_timer_extended_compare(&timer, (nrf_timer_cc_channel_t)0, 200 * 1000UL, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, false);

    err_code = nrf_drv_ppi_channel_alloc(&ppi_channel);
    APP_ERROR_CHECK(err_code);

    compare_evt_addr = nrf_drv_timer_event_address_get(&timer, NRF_TIMER_EVENT_COMPARE0);
    gpiote_task_addr = nrf_drv_gpiote_out_task_addr_get(GPIO_LED_OUTPUT_PIN_NUMBER);

    err_code = nrf_drv_ppi_channel_assign(ppi_channel, compare_evt_addr, gpiote_task_addr);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_enable(ppi_channel);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_out_task_enable(GPIO_LED_OUTPUT_PIN_NUMBER);
}


static void button_event_setup()
{
    ret_code_t err_code;

    nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(false);

    err_code = nrf_drv_gpiote_out_init(GPIO_DEBUG_OUTPUT_PIN_NUMBER, &out_config);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    in_config.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(GPIO_BUTTON_INPUT_PIN_NUMBER, &in_config, in_pin_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_event_enable(GPIO_BUTTON_INPUT_PIN_NUMBER, true);

}

int main(void)
{
    ret_code_t err_code;

    err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);


    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    err_code = nrf_drv_timer_init(&timer, &timer_cfg, timer_dummy_handler);
    APP_ERROR_CHECK(err_code);

#ifdef NRF51
    //Workaround for PAN-73.
    *(uint32_t *)0x40008C0C = 1;
#endif
    NRF_LOG_DEBUG("led_blinking_setup.\n");
    led_blinking_setup();
    NRF_LOG_DEBUG("button_event_setup.\n");
    button_event_setup();


    NRF_LOG_DEBUG("matrix_init.\n");
    matrix_init();

    // Enable timer
    NRF_LOG_DEBUG("enable blink timer.\n");
    //nrf_drv_timer_enable(&timer);
    uint16_t col_value = 0;

    while (true)
    {
        NRF_LOG_INFO("========================================\r\n")
        for (uint8_t i=0; i < ROW_COUNT; i++){
            matrix_select_row(i);
            col_value = matrix_read_col();
            matrix_unselect_row(i);
            NRF_LOG_DEBUG("matrix value: 0x%X \n", col_value);
        }
        NRF_LOG_INFO("========================================\r\n")
        nrf_delay_ms(1500);
    }
}
