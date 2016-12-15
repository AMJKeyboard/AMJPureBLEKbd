/*
 * =====================================================================================
 *
 *       Filename:  layers.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/15/2016 12:28:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

void layer_init(void);
void layer_process_timeout_handler(void * p_context);
static void layer_read(void);
static void layer_diff(void);
