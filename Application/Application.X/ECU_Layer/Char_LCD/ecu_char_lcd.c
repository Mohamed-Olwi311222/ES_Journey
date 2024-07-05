/* 
 * File:   ecu_char_lcd.c
 * Author: acemido
 *
 * Created on July 2, 2024, 5:18 PM
 */
#include "ecu_char_lcd.h"
static Std_ReturnType lcd_send_4bits(const char_lcd_4bit_t *lcd, uint8 data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const char_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const char_lcd_4bit_t *lcd, uint8 row, uint8 col);
static Std_ReturnType lcd_8bit_send_enable_signal(const char_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const char_lcd_8bit_t *lcd, uint8 row, uint8 col);

Std_ReturnType lcd_4bit_initialize(const char_lcd_4bit_t *lcd)
{
	Std_ReturnType ret = E_OK; 
    uint8 lcd_data_counter = ZERO_INIT;
	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        if (E_OK == ret)
        {
            ret = gpio_pin_initialize(&(lcd->lcd_en));
            if (E_OK == ret)
            {
                for (lcd_data_counter = ZERO_INIT; lcd_data_counter < 4; lcd_data_counter++)
                {
                    ret = gpio_pin_initialize(&(lcd->lcd_data[lcd_data_counter]));
                    if (E_NOT_OK == ret)
                    {
                        break;
                    }
                }
                if (E_OK == ret)
                {
                    /*The Initialization by instructions*/
                    __delay_ms(20);
                    ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
                    __delay_ms(5);
                    ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
                    __delay_us(150);
                    ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
                    /*Optional Instruction*/
                    if (E_OK == ret)
                    {
                        ret |= lcd_4bit_send_command(lcd, _LCD_CLEAR);
                        ret |= lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
                        ret |= lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE);
                        ret |= lcd_4bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
                        ret |= lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
                        ret |= lcd_4bit_send_command(lcd, _LCD_DDRAM_START);
                    }
                }
            }
        }
    }
	return (ret);
}

Std_ReturnType lcd_4bit_send_command(const char_lcd_4bit_t *lcd, uint8 command)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        if (E_OK == ret)
        {
            ret = lcd_send_4bits(lcd, command >> 4);
            if (E_OK == ret)
                ret = lcd_4bit_send_enable_signal(lcd);
            if (E_OK == ret)
            {
                ret = lcd_send_4bits(lcd, command);
                if (E_OK == ret)
                    ret = lcd_4bit_send_enable_signal(lcd);
            }
        }
    }
	return (ret);
}

Std_ReturnType lcd_4bit_send_char_data(const char_lcd_4bit_t *lcd, uint8 data)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        if (E_OK == ret)
        {
            ret = lcd_send_4bits(lcd, data >> 4);
            if (E_OK == ret)
                ret = lcd_4bit_send_enable_signal(lcd);
            if (E_OK == ret)
            {
                ret = lcd_send_4bits(lcd, data);
                if (E_OK == ret)
                    ret = lcd_4bit_send_enable_signal(lcd);
            }
        }
    }


	return (ret);
}

Std_ReturnType lcd_4bit_send_char_data_pos(const char_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 data)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{
        ret = lcd_4bit_set_cursor(lcd, row, col);
        if (E_OK == ret)
            ret = lcd_4bit_send_char_data(lcd, data);
    }


	return (ret);
}
 
Std_ReturnType lcd_4bit_send_string(const char_lcd_4bit_t *lcd, uint8 *str)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd || NULL == str)
	{
	    ret = E_NOT_OK;
	}
	else
	{
        while (*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
            if (E_NOT_OK == ret)
            {
                break;
            }
        }
    }


	return (ret);
}

Std_ReturnType lcd_4bit_send_string_pos(const char_lcd_4bit_t *lcd, uint8 row, uint8 col, uint8 *str)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd || NULL == str)
	{
	    ret = E_NOT_OK;
	}
	else
	{
        ret = lcd_4bit_set_cursor(lcd, row, col);
        if (E_OK == ret)
        {
            ret = lcd_4bit_send_string(lcd, str);
        }
    }
	return (ret);
}

Std_ReturnType lcd_4bit_send_custom_char(const char_lcd_4bit_t *lcd, uint8 row, uint8 col, const uint8 _char[], uint8 mem_pos)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd)
	{
    	ret = E_NOT_OK;
	}
	else
	{

    }


	return (ret);
}



Std_ReturnType lcd_8bit_initialize(const char_lcd_8bit_t *lcd)
{
	Std_ReturnType  ret = E_OK; 
    uint8 lcd_data_counter = ZERO_INIT;
	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        if (E_OK == ret)
        {
            ret = gpio_pin_initialize(&(lcd->lcd_en));
            if (E_OK == ret)
            {
                for (lcd_data_counter = ZERO_INIT; lcd_data_counter < 8; lcd_data_counter++)
                {
                    ret = gpio_pin_initialize(&(lcd->lcd_data[lcd_data_counter]));
                    if (E_NOT_OK == ret)
                    {
                        break;
                    }
                }
            }
			/*The Initialization by instructions*/
			__delay_ms(20);
			ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
			__delay_ms(5);
			ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
			__delay_us(150);
			ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
			/*Optional Instruction*/
			if (E_OK == ret)
			{
				ret |= lcd_8bit_send_command(lcd, _LCD_CLEAR);
				ret |= lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
				ret |= lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE);
				ret |= lcd_8bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
				ret |= lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
				ret |= lcd_8bit_send_command(lcd, _LCD_DDRAM_START);
			}
        }
    }
	return (ret);
}

Std_ReturnType lcd_8bit_send_command(const char_lcd_8bit_t *lcd, uint8 command)
{
	Std_ReturnType  ret = E_OK; 
	uint8 counter = ZERO_INIT;

	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
		if (E_OK == ret)
		{
			for (counter = ZERO_INIT; counter < 8; counter++)
			{
				ret = gpio_pin_write_logic(&(lcd->lcd_data[counter]), (command >> counter) & BIT_MASK);
				if (E_NOT_OK == ret)
				{
					break;
				}
			}
			if (E_OK == ret)
			{
				ret = lcd_8bit_send_enable_signal(lcd);
			}
		}
    }
	return (ret);
}

Std_ReturnType lcd_8bit_send_char_data(const char_lcd_8bit_t *lcd, uint8 data)
{
	Std_ReturnType  ret = E_OK; 
	uint8 counter = ZERO_INIT;

	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
		if (E_OK == ret)
		{
			for (counter = ZERO_INIT; counter < 8; counter++)
			{
				ret = gpio_pin_write_logic(&(lcd->lcd_data[counter]), (data >> counter) & BIT_MASK);
				if (E_NOT_OK == ret)
				{
					break;
				}
			}
			if (E_OK == ret)
			{
				ret = lcd_8bit_send_enable_signal(lcd);
			}
		}
    }
	return (ret);
}

Std_ReturnType lcd_8bit_send_char_data_pos(const char_lcd_8bit_t *lcd, uint8 row, uint8 col, uint8 data)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{
		ret = lcd_8bit_set_cursor(lcd, row, col);
		if (E_OK == ret)
		{
			ret = lcd_8bit_send_char_data(lcd, data);
		}
    }
	return (ret);
}
 
Std_ReturnType lcd_8bit_send_string(const char_lcd_8bit_t *lcd, uint8 *str)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{
		while (*str)
		{
			ret = lcd_8bit_send_char_data(lcd, *str++);
			if (E_NOT_OK == ret)
			{
				break;
			}
		}
    }
	return (ret);
}

Std_ReturnType lcd_8bit_send_string_pos(const char_lcd_8bit_t *lcd, uint8 row, uint8 col, uint8 *str)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd || NULL == str)
	{
	    ret = E_NOT_OK;
	}
	else
	{
		ret = lcd_8bit_set_cursor(lcd, row, col);
		if (E_OK == ret)
		{
			ret = lcd_8bit_send_string(lcd, str);
		}
    }
	return (ret);
}

Std_ReturnType lcd_8bit_send_custom_char(const char_lcd_8bit_t *lcd, uint8 row, uint8 col, const uint8 _char[], uint8 mem_pos)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == lcd)
	{
	    ret = E_NOT_OK;
	}
	else
	{

    }


	return (ret);
}

static Std_ReturnType lcd_send_4bits(const char_lcd_4bit_t *lcd, uint8 data_command)
{
    Std_ReturnType ret = E_OK;
    uint8 counter = ZERO_INIT;

    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for (counter = ZERO_INIT; counter < 4; counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[counter]), (data_command >> counter) & BIT_MASK);
            if (E_NOT_OK == ret)
            {
                break;
            }
        }
    }
    return (ret);
}
static Std_ReturnType lcd_4bit_set_cursor(const char_lcd_4bit_t *lcd, uint8 row, uint8 col)
{
	Std_ReturnType ret = E_OK;

	if (NULL == lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		col--;
		if (UINT8_MAX == col)
		{
			col = 0;
		}
		switch (row)
		{
            case ROW1:
                ret = lcd_4bit_send_command(lcd, _LCD_DDRAM_START + col);
                break;
            case ROW2:
                ret = lcd_4bit_send_command(lcd, 0xC0 + col);
                break;
            case ROW3:
                ret = lcd_4bit_send_command(lcd, 0x94 + col);
                break;
            case ROW4:
                ret = lcd_4bit_send_command(lcd, 0xD4 + col);
                break;
            default:
                ret = E_NOT_OK;
                break;
		}
	}
	return (ret);
}
static Std_ReturnType lcd_4bit_send_enable_signal(const char_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;

    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        if (E_OK == ret)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
        }
    }
    return (ret);
}
static Std_ReturnType lcd_8bit_send_enable_signal(const char_lcd_8bit_t *lcd)
{
	Std_ReturnType ret = E_OK;

	if (NULL == lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
		ret |= gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
	}
	return (ret);
}
static Std_ReturnType lcd_8bit_set_cursor(const char_lcd_8bit_t *lcd, uint8 row, uint8 col)
{
	Std_ReturnType ret = E_OK;

	if (NULL == lcd)
	{
		ret = E_NOT_OK;
	}
	else
	{
		col--;
		if (UINT8_MAX == col)
		{
			col = 0;
		}
		switch (row)
		{
            case ROW1:
                ret = lcd_8bit_send_command(lcd, _LCD_DDRAM_START + col);
                break;
            case ROW2:
                ret = lcd_8bit_send_command(lcd, 0xC0 + col);
                break;
            case ROW3:
                ret = lcd_8bit_send_command(lcd, 0x94 + col);
                break;
            case ROW4:
                ret = lcd_8bit_send_command(lcd, 0xD4 + col);
                break;
            default:
                ret = E_NOT_OK;
                break;
		}
	}
	return (ret);
}

Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == str)
	{
	    ret = E_NOT_OK;
	}
	else
	{
		memset(str, '\0', BYTE_STR_SIZE);
		if (snprintf((char *)str, BYTE_STR_SIZE, "%u", value) < 0)
		{
			ret = E_NOT_OK;
		}
    }
	return (ret);
}

Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str)
{
	Std_ReturnType  ret = E_OK; 
	if (NULL == str)
	{
	    ret = E_NOT_OK;
	}
	else
	{
		memset(str, '\0', SHORT_STR_SIZE);
		if (snprintf((char *)str, SHORT_STR_SIZE, "%u", value) < 0)
		{
			ret = E_NOT_OK;
		}
    }
	return (ret);
}
