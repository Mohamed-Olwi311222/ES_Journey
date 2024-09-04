/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "MCAL_Layer/ADC/hal_adc.h"

void adc_interrupt_handler(void);
adc_conversion_result lm35_result1 = ZERO_INIT;
adc_conversion_result lm35_result2 = ZERO_INIT;
uint16 lm35_res1_celsius_mv = ZERO_INIT;
uint16 lm35_res2_celsius_mv = ZERO_INIT;

uint8 lm35_result1_txt[6];
uint8 lm35_result2_txt[6];

uint8 channel_select = ZERO_INIT;

dc_motor_t motor1 = {
  .dc_motor_pins[0].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pins[0].logic = GPIO_LOW,
  .dc_motor_pins[0].port = PORTD_INDEX,
  .dc_motor_pins[0].pin = GPIO_PIN0,
  .dc_motor_pins[1].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pins[1].logic = GPIO_LOW,
  .dc_motor_pins[1].port = PORTD_INDEX,
  .dc_motor_pins[1].pin = GPIO_PIN1,
};
dc_motor_t motor2 = {
  .dc_motor_pins[0].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pins[0].logic = GPIO_LOW,
  .dc_motor_pins[0].port = PORTD_INDEX,
  .dc_motor_pins[0].pin = GPIO_PIN2,
  .dc_motor_pins[1].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pins[1].logic = GPIO_LOW,
  .dc_motor_pins[1].port = PORTD_INDEX,
  .dc_motor_pins[1].pin = GPIO_PIN3,
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
adc_config_t adc = {
  .adc_interrupt_handler = adc_interrupt_handler,
  .priortiy = INTERRUPT_HIGH_PRIORITY,
  .aquisition_time = ADC_ACQUISITION_TIME_12_TAD,
  .adc_analog_channel = ADC_CHANNEL_AN0,
  .adc_port_config = ADC_AN0__AN1__ANALOG_FUNCTIONALITY,
  .conversion_clock = ADC_CONVERSION_CLOCK_FOSC16,
  .result_format = ADC_RES_RIGHT_JUSTIFY,
  .voltage_ref = ADC_VREF_INTENAL
};

void adc_interrupt_handler(void)
{
    if (ADC_CHANNEL_AN0 == channel_select)
    {
        adc_read_result(&adc, &lm35_result1);
        channel_select = ADC_CHANNEL_AN1;
    }
    else
    {
        adc_read_result(&adc, &lm35_result2);
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
    ret |= dc_motor_initialize(&motor1);
    ret |= dc_motor_initialize(&motor2);
    
    ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 6, "LM35 test");
    __delay_ms(2000);
    ret |= lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 1, "Sensor1: ");
    ret |= lcd_4bit_send_string_pos(&lcd_1, 2, 1, "Sensor2: ");

    while(1)
    {
        if (ADC_CHANNEL_AN0 == channel_select)
        {
            ret |= adc_get_conversion_interrupt(&adc, ADC_CHANNEL_AN0);
        }
        else
        {
            ret |= adc_get_conversion_interrupt(&adc, ADC_CHANNEL_AN1);
        }
        lm35_res1_celsius_mv = lm35_result1 * 4.88f;
        lm35_res2_celsius_mv = lm35_result2 * 4.88f;

        lm35_res1_celsius_mv /= 10;
        lm35_res2_celsius_mv /= 10;

        ret |= convert_uint16_to_string(lm35_res1_celsius_mv, lm35_result1_txt);
        ret |= convert_uint16_to_string(lm35_res2_celsius_mv, lm35_result2_txt);

        ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 9, lm35_result1_txt);
        ret |= lcd_4bit_send_string_pos(&lcd_1, 2, 9, lm35_result2_txt);
        if (lm35_res1_celsius_mv > 20)
        {
            ret |= dc_motor_move_forward(&motor1);
        }
        else
        {
            ret |= dc_motor_stop(&motor1);
        }
        
        if (lm35_res2_celsius_mv > 25)
        {
            ret |= dc_motor_move_forward(&motor2);
        }
        else
        {
            ret |= dc_motor_stop(&motor2);
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
