/*
 * File:  ccp2_capture_test.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../../../ecu_test_init.h"
/* Note this test only works with 4 MHz osc */
volatile uint8 capture_rising_edge = 0;
volatile uint8 freq_flag = 0;

volatile uint32 timer3_overflow = 0;
volatile uint16 captured_value = 0;
uint32 signal_period = 0;

uint16 signal_freq = 0;
uint8 signal_freq_str[SHORT_STR_SIZE] = {0};

void CCP2_Interrupt_Handler(void);
void Timer3_Interrupt_Handler(void);

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
cpp2_t ccp2_obj = {
  .ccp2_interrupt_handler = CCP2_Interrupt_Handler,
  .ccp2_interrupt_priority = INTERRUPT_LOW_PRIORITY,
  .ccp2_mode = CCP2_CAPTURE_MODE_SELECT,
  .ccp2_mode_variant = CCP2_CAPTURE_MODE_1_RISING_EDGE,
};
timer3_t timer3_obj = {
  .timer3_interrupt_handler = Timer3_Interrupt_Handler,
  .timer3_interrupt_priority = INTERRUPT_LOW_PRIORITY,
  .timer3_preloaded_value = 0,
  .rw_mode = _TIMER3_RW_16bit_OP,
  .prescaler_value = TIMER3_PRESCALER_DIV_BY_1,
  .clock_src = _TIMER3_INT_SRC,
  .clk_src_for_ccpx = TIMER3_FOR_CCPx_MODULES,
};
int ccp1_capture_test(void)
{
    Std_ReturnType ret = E_OK;
    
    ret |= lcd_4bit_initialize(&lcd_1);
    ret |= lcd_4bit_send_string_pos(&lcd_1, 1, 1, (uint8 *)"CCP2 Capture test");
    __delay_ms(2000);
    ret |= ccp2_init(&ccp2_obj);
    ret |= timer3_init(&timer3_obj);
    ret |= lcd_4bit_send_command(&lcd_1, _LCD_CLEAR);
    ret |= lcd_4bit_send_string_pos(&lcd_1, 2, 1, (uint8 *) "Frequency: ");
    while (1)
    {
        if (freq_flag)
        {
            signal_period = (uint32)((timer3_overflow * 65536) + captured_value);
            signal_freq = (uint16)(1 /(signal_period / 1000000.0)); 
            ret |= convert_uint16_to_string(signal_freq, signal_freq_str);
            ret |= lcd_4bit_send_string_pos(&lcd_1, 2, 12, signal_freq_str);
            freq_flag = 0;
            timer3_overflow = 0;
        }
    }
    return (ret);
}
void CCP2_Interrupt_Handler(void)
{
    capture_rising_edge++;
    if (1 == capture_rising_edge)
    {
        (void)timer3_write_value(&timer3_obj, 0);
        timer3_overflow = 0;
    }
    else if (2 == capture_rising_edge)
    {
        (void)ccp2_capture_mode_read_value((uint16 *)&captured_value);
        capture_rising_edge = 0;
        freq_flag = 1;
    }
}
void Timer3_Interrupt_Handler(void)
{
    timer3_overflow++;
}