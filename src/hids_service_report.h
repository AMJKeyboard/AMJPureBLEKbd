/*
 * =====================================================================================
 *
 *       Filename:  hids_service_report.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/18/2016 01:30:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

bool send_key_report(uint8_t * data, uint8_t len);
bool send_consumer_report(uint16_t data);
