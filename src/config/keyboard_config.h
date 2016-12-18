/*
 * =====================================================================================
 *
 *       Filename:  keyboard_config.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/15/2016 11:44:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#define DEVICE_NAME                      "AMJ_Keyboard"                          /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                "AMJ By Jieshao"                      /**< Manufacturer. Will be passed to Device Information Service. */

#define PNP_ID_VENDOR_ID                 0x1915                                     /**< Vendor ID. */
#define PNP_ID_PRODUCT_ID                0xEEEE                                     /**< Product ID. */
#define PNP_ID_PRODUCT_VERSION           0x0001                                     /**< Product Version. */

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define GPIO_DEBUG_OUTPUT_PIN_NUMBER 2
#define GPIO_LED_OUTPUT_PIN_NUMBER 3
#define GPIO_BUTTON_INPUT_PIN_NUMBER 8
#define GPIO_TX_PIN_NUMBER 23
#define GPIO_RX_PIN_NUMBER 24


//#define MATRIX_DEBUG
//#define KEYCODE_DEBUG
#define HID_REPORT_DEBUG
