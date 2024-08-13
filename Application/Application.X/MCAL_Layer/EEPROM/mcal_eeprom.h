/* 
 * File:   mcal_eeprom.h
 * Author: Mohamed olwi
 *
 * Created on 13 August 2024, 07:40
 */

#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H
/*----------------------------Header Files------------------------------------*/
#include "../mcal_std_types.h"
#include <xc.h>
#include "../Interrupt/mcal_internal_interrupt.h"
/*----------------------------DataTypes---------------------------------------*/

/*----------------------------Macros Declarations-----------------------------*/

/*----------------------------Macros Functions Declarations-------------------*/




/*----------------------------Function Prototypes-----------------------------*/

/**
 * @brief Write a byte to a specific address in the EEPROM
 * @param byte_add the address to save the data into
 * @param byte_data the data to save inside the EEPROM memory address
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Data_EEPROM_Write_Byte(uint16 byte_add, uint8 byte_data);

/**
 * @brief Read a byte from a specific address in the EEPROM
 * @param byte_add the address to Read the data from
 * @param byte_data the address to save the data read from the EEPROM
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Data_EEPROM_Read_Byte(uint16 byte_add, uint8 *byte_data);

#endif	/* MCAL_EEPROM_H */

