/*
 * =====================================================================================
 *
 *       Filename:  ble_status_led.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/08/2017 08:38:47 PM
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
#include "nrf_gpiote.h"
#include "nrf_gpio.h"
#include "led_softblink.h"

#include "keyboard_config.h"

#include "ble_status_led.h"

#define LEDS_MASK (1<<GPIO_LED_OUTPUT_PIN_NUMBER)

void status_led_init(void){
    ret_code_t ret;
    const led_sb_init_params_t led_sb_init_param = LED_SB_INIT_DEFAULT_PARAMS(LEDS_MASK);
    ret = led_softblink_init(&led_sb_init_param);
    APP_ERROR_CHECK(ret);
    ret = led_softblink_start(LEDS_MASK);
    APP_ERROR_CHECK(ret);
}

void status_led_start(void){
    ret_code_t ret;
    ret = led_softblink_start(LEDS_MASK);
    APP_ERROR_CHECK(ret);
}

void status_led_stop(void){
    ret_code_t ret;
    ret = led_softblink_stop();
    APP_ERROR_CHECK(ret);
}

