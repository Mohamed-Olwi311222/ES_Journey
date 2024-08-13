/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "MCAL_Layer/EEPROM/mcal_eeprom.h"

Std_ReturnType application_init(void);

int main(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret = Data_EEPROM_Write_Byte( 0x232, 0x22);
    while(1)
    {

    }
   return (0);
}
Std_ReturnType application_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();

    return (ret);
}
