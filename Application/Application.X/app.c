/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
Std_ReturnType application_init(void);

uint8 custom1[] = {
  0x0E,
  0x0A,
  0x1B,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x00
};

uint8 custom2[] = {
  0x0E,
  0x0A,
  0x1B,
  0x11,
  0x11,
  0x1F,
  0x1F,
  0x00
};

uint8 custom3[] = {
  0x0E,
  0x0A,
  0x1B,
  0x11,
  0x1F,
  0x1F,
  0x1F,
  0x00
};

uint8 custom4[] = {
  0x0E,
  0x0A,
  0x1B,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00
};

uint8 custom5[] = {
  0x0E,
  0x0A,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00
};

uint8 custom6[] = {
  0x0E,
  0x0E,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x00
};
int main(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret = lcd_8bit_send_string_pos(&lcd_2, 2, 5, " the World");
    ret = lcd_4bit_send_char_data_pos(&lcd_1, 1, 5, 'I');
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 6, "Will Conquer");
    while (1)
    {
        ret = lcd_4bit_send_custom_char(&lcd_1, 1, 20, custom1, 0);
        ret = lcd_8bit_send_custom_char(&lcd_2, 1, 20, custom1, 0);
        __delay_ms(250);
        ret = lcd_4bit_send_custom_char(&lcd_1, 1, 20, custom2, 0);
        ret = lcd_8bit_send_custom_char(&lcd_2, 1, 20, custom2, 0);
        __delay_ms(250);
        ret = lcd_4bit_send_custom_char(&lcd_1, 1, 20, custom3, 0);
        ret = lcd_8bit_send_custom_char(&lcd_2, 1, 20, custom3, 0);
        __delay_ms(250);
        ret = lcd_4bit_send_custom_char(&lcd_1, 1, 20, custom4, 0);
        ret = lcd_8bit_send_custom_char(&lcd_2, 1, 20, custom4, 0);
        __delay_ms(250);
        ret = lcd_4bit_send_custom_char(&lcd_1, 1, 20, custom5, 0);
        ret = lcd_8bit_send_custom_char(&lcd_2, 1, 20, custom5, 0);
        __delay_ms(250);
        ret = lcd_4bit_send_custom_char(&lcd_1, 1, 20, custom6, 0);
        ret = lcd_8bit_send_custom_char(&lcd_2, 1, 20, custom6, 0);
        __delay_ms(250);
    }
    
   return (0);
}
Std_ReturnType application_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();

    return (ret);
}
