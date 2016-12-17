/*
 * =====================================================================================
 *
 *       Filename:  battery_service.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/12/2016 09:02:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

void bas_init(void);
void bas_adc_init(void);
void battery_level_update(void);
void battery_level_meas_timeout_handler(void * p_context);
