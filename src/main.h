/*
 * =====================================================================================
 *
 *       Filename:  main.h
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

#pragma once

int main(void);

void timer_dummy_handler(nrf_timer_event_t event_type, void * p_context);

void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action);

static void led_blinking_setup();

static void button_event_setup();
