/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "device_config.h"
#include "MCAL_Layer/Timers/Timer1/hal_timer1.h"

void timer1_interrupt();

timer1_t timer1_obj = {
  .timer1_preloaded_value = 0x8000,
  .prescaler_value = TIMER1_PRESCALER_DISABLE,
  .clock_src = _TIMER1_EXT_SRC,
  .ext_clk_sync = _TIMER1_SYNC,
  .rw_mode = _TIMER1_RW_16bit_OP,
  .ext_osc_enable = _TIMER1_OSC_ENABLE,
  .timer1_interrupt_handler = timer1_interrupt,
  .timer1_interrupt_priority = INTERRUPT_LOW_PRIORITY
};
char_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTD_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTD_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTD_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTD_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTD_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTD_INDEX,
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

void timer1_interrupt()
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
    ret |= timer1_init(&timer1_obj);
    ret |= lcd_4bit_initialize(&lcd_1);
    
    ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 6, "Timer1 test");
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

