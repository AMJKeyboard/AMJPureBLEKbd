/*
 * =====================================================================================
 *
 *       Filename:  eeprom.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/20/2016 09:15:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

typedef enum eeprom_block {
    EEPROM_BLOCK_0 = 0,
    EEPROM_BLOCK_1,
    EEPROM_BLOCK_2,
    EEPROM_BLOCK_3,
    EEPROM_BLOCK_4,
    EEPROM_BLOCK_5,
    EEPROM_BLOCK_6,
    EEPROM_BLOCK_7
} eeprom_block_e;

void twi_init (void);
uint8_t twi_eeprom_slave_address(eeprom_block_e block);
void twi_eeprom_write_byte(eeprom_block_e block, uint16_t address, uint8_t data);
uint8_t twi_eeprom_read_byte(eeprom_block_e block, uint16_t address);
