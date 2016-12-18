/*
 * =====================================================================================
 *
 *       Filename:  timers.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/15/2016 07:55:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "app_timer.h"
#include "app_timer_appsh.h"
#include "app_error.h"

#include "timers.h"
#include "battery_service.h"
#include "layer.h"


#define BATTERY_LEVEL_MEAS_INTERVAL      APP_TIMER_TICKS(2000, APP_TIMER_PRESCALER) /**< Battery level measurement interval (ticks). */
#define LAYER_PROCESS_INTERVAL      APP_TIMER_TICKS(100, APP_TIMER_PRESCALER)

APP_TIMER_DEF(m_battery_timer_id);                          /**< Battery timer. */
APP_TIMER_DEF(m_layout_timer_id);                          /**< Battery timer. */

/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
void timer_init(void)
{
    uint32_t err_code;

    // Initialize timer module, making it use the scheduler.
    APP_TIMER_APPSH_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, true);

    // Create battery timer.
    err_code = app_timer_create(&m_battery_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                battery_level_meas_timeout_handler);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create(&m_layout_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                layer_process_timeout_handler);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for starting timers.
 */
void bas_timer_start(void)
{
    uint32_t err_code;

    err_code = app_timer_start(m_battery_timer_id, BATTERY_LEVEL_MEAS_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}

void layer_timer_start(void)
{
    uint32_t err_code;
    err_code = app_timer_start(m_layout_timer_id, LAYER_PROCESS_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}
