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
/*----------------------------Macros Functions Declarations-------------------*/

/*EEPGD bit*/
#define EEPGD_ACCESS_FLASH_PROGRAM_MEM()                (EECON1bits_t.EEPGD = 1) /*Access Flash program memory*/
#define EEPGD_ACCESS_DATA_EEPROM_MEM()                  (EECON1bits_t.EEPGD = 0) /*Access data EEPROM memory*/

/*CFGS bit*/
#define CFGS_ACCESS_CONFIG_REGS()                       (EECON1bits_t.CFGS = 1)  /*Access Configuration registers*/
#define CFGS_ACCESS_FLASH_PROG_MEM()                    (EECON1bits_t.CFGS = 0)  /*Access Flash program*/
#define CFGS_ACCESS_DATA_EEPROM()                       (EECON1bits_t.CFGS = 0)  /*Access data EEPROM memory*/

/*WREN bit*/
#define WREN_EEPROM_ENABLE_WRITE()                      (EECON1bits_t.WREN = 1)  /*1 = Allows write cycles to Flash program/data EEPROM*/
#define WREN_EEPROM_DISABLE_WRITE()                     (EECON1bits_t.WREN = 0)  /*Inhibits write cycles to Flash program/data EEPROM*/

/*WR bit*/
#define EEPROM_BEGIN_WRITE_ERASE()                      (EECON1bits_t.WR = 1)    /*Initiates a data EEPROM erase/write cycle or a program memory erase cycle or write cycle*/

/*PIR2 EEIF flag*/
#define CLEAR_EEIF_FLAG()                               (PIR2bits_t.EEIF = 0) 

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

