/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
Std_ReturnType application_init(void);
uint8 lcd_counter_txt[4];
uint8 number = 0;
uint8 lcd_counter_txt2[6];
uint16 number2 = 65535;
int main(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }

    while (1)
    {
        if (0 == number2) {ret = lcd_8bit_send_command(&lcd_2, _LCD_CLEAR);}
        ret = convert_uint16_to_string(number2, lcd_counter_txt2);
        ret = lcd_8bit_send_string_pos(&lcd_2, 1, 1, lcd_counter_txt2);
        number2++;
    }
    
   return (0);
}
Std_ReturnType application_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();

    return (ret);
}
