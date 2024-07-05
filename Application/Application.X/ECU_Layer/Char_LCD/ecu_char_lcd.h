/* 
 * File:   ecu_char_lcd.h
 * Author: acemido
 *
 * Created on July 2, 2024, 5:18 PM
 */

#ifndef ECU_CHAR_LCD_H
#define	ECU_CHAR_LCD_H
/*----------------------------Header Files------------------------------------*/
#include "ecu_char_lcd_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include <string.h>
/*----------------------------Macros Declarations-----------------------------*/
#define _LCD_CLEAR                      0x01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE                 0x06
#define _LCD_CURSOR_OFF_DISPLAY_ON      0x0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF     0x08
#define _LCD_CURSOR_ON_BLINK_ON         0x0F
#define _LCD_CURSOR_ON_BLINK_OFF        0x0E
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define _LCD_DISPLAY_SHIFT_LEFT         0x18
#define _LCD_8BIT_MODE_2_LINE           0x38
#define _LCD_4BIT_MODE_2_LINE           0x28
#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_START                0x80

#define ROW1                            1
#define ROW2                            2
#define ROW3                            3
#define ROW4                            4
/*----------------------------Macros Functions Declarations-------------------*/

/*----------------------------DataTypes---------------------------------------*/
typedef struct 
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
} char_lcd_4bit_t;

typedef struct 
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
} char_lcd_8bit_t;
/*----------------------------Function Prototypes-----------------------------*/
Std_ReturnType lcd_4bit_initialize(const char_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const char_lcd_4bit_t *lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const char_lcd_4bit_t *lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const char_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 data); 
Std_ReturnType lcd_4bit_send_string(const char_lcd_4bit_t *lcd, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const char_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const char_lcd_4bit_t *lcd, uint8 row, uint8 col, const uint8 _char[], uint8 mem_pos);


Std_ReturnType lcd_8bit_initialize(const char_lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const char_lcd_8bit_t *lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const char_lcd_8bit_t *lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const char_lcd_8bit_t *lcd, uint8 row, uint8 col, uint8 data); 
Std_ReturnType lcd_8bit_send_string(const char_lcd_8bit_t *lcd, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const char_lcd_8bit_t *lcd, uint8 row, uint8 col, uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const char_lcd_8bit_t *lcd, uint8 row, uint8 col, const uint8 _char[], uint8 mem_pos);

Std_ReturnType convert_byte_to_string(uint8 value, uint8 *str);
Std_ReturnType convert_short_to_string(uint16 value, uint8 *str);
Std_ReturnType convert_int_to_string(uint32 value, uint8 *str);
#endif	/* ECU_CHAR_LCD_H */

