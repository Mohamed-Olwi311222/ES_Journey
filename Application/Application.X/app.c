/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "MCAL_Layer/ADC/hal_adc.h"

void adc_interrupt_handler(void);
adc_conversion_result adc_result1 = ZERO_INIT;
adc_conversion_result adc_result2 = ZERO_INIT;
adc_conversion_result adc_result3 = ZERO_INIT;
adc_conversion_result adc_result4 = ZERO_INIT;

uint8 adc_result1_txt[6];
uint8 adc_result2_txt[6];
uint8 adc_result3_txt[6];
uint8 adc_result4_txt[6];

uint8 channel_select = ZERO_INIT;

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

adc_config_t adc = {
  .adc_interrupt_handler = adc_interrupt_handler,
  .priortiy = INTERRUPT_HIGH_PRIORITY,
  .aquisition_time = ADC_ACQUISITION_TIME_12_TAD,
  .adc_analog_channel = ADC_CHANNEL_AN0,
  .adc_port_config = ADC_AN0__AN3__ANALOG_FUNCTIONALITY,
  .conversion_clock = ADC_CONVERSION_CLOCK_FOSC16,
  .result_format = ADC_RES_RIGHT_JUSTIFY,
  .voltage_ref = ADC_VREF_INTENAL
};

void adc_interrupt_handler(void)
{
    if (ADC_CHANNEL_AN0 == channel_select)
    {
        adc_read_result(&adc, &adc_result1);
        channel_select = ADC_CHANNEL_AN1;
    }
    else if (ADC_CHANNEL_AN1 == channel_select)
    {
        adc_read_result(&adc, &adc_result2);
        channel_select = ADC_CHANNEL_AN2;
    }
    else if (ADC_CHANNEL_AN2 == channel_select)
    {
        adc_read_result(&adc, &adc_result3);
        channel_select = ADC_CHANNEL_AN3;
    }
    else
    {
        adc_read_result(&adc, &adc_result4);
        channel_select = ADC_CHANNEL_AN0;
    }
}
int main(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret |= adc_init(&adc);
    ret |= lcd_4bit_initialize(&lcd_1);
    ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 6, "ADC test");
    __delay_ms(2000);
    ret |= lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 1, "POT1: ");
    ret |= lcd_4bit_send_string_pos(&lcd_1, 2, 1, "POT2: ");
    ret |= lcd_4bit_send_string_pos(&lcd_1, 3, 1, "POT3: ");
    ret |= lcd_4bit_send_string_pos(&lcd_1, 4, 1, "POT4: ");

    while(1)
    {
        if (ADC_CHANNEL_AN0 == channel_select)
        {
            ret |= adc_get_conversion_interrupt(&adc, ADC_CHANNEL_AN0);
        }
        else if (ADC_CHANNEL_AN1 == channel_select)
        {
            ret |= adc_get_conversion_interrupt(&adc, ADC_CHANNEL_AN1);
        }
        else if (ADC_CHANNEL_AN2 == channel_select)
        {
            ret |= adc_get_conversion_interrupt(&adc, ADC_CHANNEL_AN2);
        }
        else
        {
            ret |= adc_get_conversion_interrupt(&adc, ADC_CHANNEL_AN3);
        }
        
        ret |= convert_uint16_to_string(adc_result1, adc_result1_txt);
        ret |= convert_uint16_to_string(adc_result2, adc_result2_txt);
        ret |= convert_uint16_to_string(adc_result3, adc_result3_txt);
        ret |= convert_uint16_to_string(adc_result4, adc_result4_txt);

        ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 7, adc_result1_txt);
        ret |= lcd_4bit_send_string_pos(&lcd_1, 2, 7, adc_result2_txt);
        ret |= lcd_4bit_send_string_pos(&lcd_1, 3, 7, adc_result3_txt);
        ret |= lcd_4bit_send_string_pos(&lcd_1, 4, 7, adc_result4_txt);
    }
   return (0);
}
Std_ReturnType application_init(void)
{
    Std_ReturnType ret = E_OK;
    ret = ecu_layer_initialize();

    return (ret);
}
