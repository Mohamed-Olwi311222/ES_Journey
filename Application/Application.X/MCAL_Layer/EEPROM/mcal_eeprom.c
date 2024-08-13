/* 
 * File:   mcal_eeprom.c
 * Author: Mohamed olwi
 *
 * Created on 13 August 2024, 07:40
 */
#include "mcal_eeprom.h"

/**
 * @brief Write a byte to a specific address in the EEPROM
 * @param byte_add the address to save the data into
 * @param byte_data the data to save inside the EEPROM memory address
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Data_EEPROM_Write_Byte(uint16 byte_add, uint8 byte_data)
{
    Std_ReturnType ret = E_OK;
    /*Save the Global Interrupt status*/
    uint8 GIE_status = INTCONbits.GIE;
    /*Set the EEPROM Address: Load the EEPROM address into the EEADR and EEADRH registers*/
    EEADRH = (uint8)((byte_add >> 8) & 0x03);
    EEADR = (uint8)(byte_add & 0xFF);
    /*Load Data: Move the data to be written into the EEDATA register*/
    EEDATA = byte_data;
    /*Configure the EECON1 register to point to EEPROM memory and enable write operations by setting the WREN bit.*/
    EEPGD_ACCESS_DATA_EEPROM_MEM();
    CFGS_ACCESS_DATA_EEPROM();
    WREN_EEPROM_ENABLE_WRITE();
    /*Disable interrupts, perform a specific unlock sequence (0x55 and 0xAA written to EECON2), and then start the write by setting the WR bit.*/
    INTERRUPT_Global_interrupt_DISABLE();
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EEPROM_BEGIN_WRITE_ERASE();
    /*Wait Until the Write operation is completed*/
    while(EECON1bits_t.WR == 1);
    /*Inhibits write cycles to Flash program/data EEPROM*/
    WREN_EEPROM_DISABLE_WRITE();
    /*Remove Interrupt Flag*/
    CLEAR_EEIF_FLAG();
    /*Restore Interrupt Status*/
    INTCONbits_t.GIE = GIE_status;
  
    return (ret);   
}

/**
 * @brief Read a byte from a specific address in the EEPROM
 * @param byte_add the address to Read the data from
 * @param byte_data the address to save the data read from the EEPROM
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Data_EEPROM_Read_Byte(uint16 byte_add, uint8 *byte_data)
{
    Std_ReturnType ret = E_OK;
    if (NULL == byte_data)
    {
        ret = E_NOT_OK;
    }
    else
    {

    }
    return (ret);  
}