/*
 * =====================================================================================
 *
 *       Filename:  timers.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/15/2016 07:55:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#define APP_TIMER_PRESCALER              0                                          /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE          6                                          /**< Size of timer operation queues. */

void timer_init(void);
void bas_timer_start(void);
void layer_timer_start(void);
