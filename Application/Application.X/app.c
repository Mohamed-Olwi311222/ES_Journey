/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "MCAL_Layer/Timer0/hal_timer0.h"

void timer0_interrupt_handler(void);

timer0_t timer0_obj = {
    .timer0_preloaded_value = 0x0BDC,
    .clock_src = _TIMER0_INT_SRC,
    .edge = _TIMER0_RISING_EDGE,
    .resolution_bits = _TIMER0_16bit_RES,
    .prescaler_enable = _TIMER0_PRESCALER_ENABLE,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
    .timer0_interrupt_handler = timer0_interrupt_handler,
    .timer0_interrupt_priority = INTERRUPT_HIGH_PRIORITY
};

char_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW
};

uint8 seconds = 50;
uint8 seconds_txt[6];

uint8 minutes = 59;
uint8 minutes_txt[6];

uint8 hours = 23;
uint8 hours_txt[6];

volatile uint8 update_display_flag = 0;

void timer0_interrupt_handler(void)
{
    seconds++;
    update_display_flag = 1; // Set flag to update the display
}

int main(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret |= timer0_init(&timer0_obj);
    ret |= lcd_4bit_initialize(&lcd_1);
    ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 6, "Timer0 test");
    __delay_ms(2000);
    ret |= lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Time: ");
    ret |= lcd_4bit_send_string_pos(&lcd_1, 2, 6, ":");
    ret |= lcd_4bit_send_string_pos(&lcd_1, 2, 12, ":");

    // Initial display
    convert_uint8_to_string(seconds, seconds_txt);
    convert_uint8_to_string(minutes, minutes_txt);
    convert_uint8_to_string(hours, hours_txt);

    lcd_4bit_send_string_pos(&lcd_1, 2, 3, hours_txt);
    lcd_4bit_send_string_pos(&lcd_1, 2, 8, minutes_txt);
    lcd_4bit_send_string_pos(&lcd_1, 2, 14, seconds_txt);

    while(1)
    {
        // Only update the display when the flag is set
        if (update_display_flag)
        {
            update_display_flag = 0; // Reset the flag

            if (seconds == 60)
            {
                seconds = 0;
                minutes++;
            }
            if (minutes == 60)
            {
                minutes = 0;
                hours++;
            }
            if (hours == 24)
            {
                hours = 0;
            }

            convert_uint8_to_string(hours, hours_txt);
            convert_uint8_to_string(minutes, minutes_txt);
            convert_uint8_to_string(seconds, seconds_txt);

            lcd_4bit_send_string_pos(&lcd_1, 2, 3, hours_txt);
            lcd_4bit_send_string_pos(&lcd_1, 2, 8, minutes_txt);
            lcd_4bit_send_string_pos(&lcd_1, 2, 14, seconds_txt);
        }
    }
    return (0);
}

Std_ReturnType application_init(void)
{
    Std_ReturnType ret = E_OK;
    ret = ecu_layer_initialize();

    return (ret);
}

