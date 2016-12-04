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

#include "FreeRTOS.h"
#include "task.h"

#include "nrf.h"
#include "nordic_common.h"
#include "nrf_drv_clock.h"
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

#define LED_TOGGLE_TASK_DELAY 200

static nrf_drv_timer_t timer = NRF_DRV_TIMER_INSTANCE(0);

TaskHandle_t  led_toggle_task_handle;   /**< Reference to LED0 toggling FreeRTOS task. */


void timer_dummy_handler(nrf_timer_event_t event_type, void * p_context){}


void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    NRF_LOG_INFO("in_pin_handler \r\n");
}

static void button_event_setup()
{
    ret_code_t err_code;

    nrf_drv_gpiote_out_config_t config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(false);

    err_code = nrf_drv_gpiote_out_init(GPIO_LED_OUTPUT_PIN_NUMBER, &config);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(false);

    err_code = nrf_drv_gpiote_out_init(GPIO_DEBUG_OUTPUT_PIN_NUMBER, &out_config);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    in_config.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(GPIO_BUTTON_INPUT_PIN_NUMBER, &in_config, in_pin_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_event_enable(GPIO_BUTTON_INPUT_PIN_NUMBER, true);

}

static void led_toggle_task_function (void * pvParameter)
{
    NRF_LOG_INFO("task led_toggle_task_function. \r\n");
    UNUSED_PARAMETER(pvParameter);
    while (true)
    {

        NRF_LOG_INFO("led toggle. \r\n");
        nrf_drv_gpiote_out_toggle(GPIO_LED_OUTPUT_PIN_NUMBER);
        /* Delay a task for a given number of ticks */
        nrf_delay_ms(100);
        /* Tasks must be implemented to never return... */
    }
}


int main(void)
{
    ret_code_t err_code;

    /* Initialize clock driver for better time accuracy in FREERTOS */
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEBUG("button_event_setup.\n");
    button_event_setup();

    NRF_LOG_DEBUG("matrix_init.\n");
    matrix_init();

    NRF_LOG_DEBUG("create task led_toggle_task.\n");
    /* Create task for LED0 blinking with priority set to 2 */
    UNUSED_VARIABLE(xTaskCreate(led_toggle_task_function, "LED0", configMINIMAL_STACK_SIZE + 200, NULL, 2, &led_toggle_task_handle));

    NRF_LOG_DEBUG("vTaskStartScheduler.\n");
    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();
    // bocking..

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
