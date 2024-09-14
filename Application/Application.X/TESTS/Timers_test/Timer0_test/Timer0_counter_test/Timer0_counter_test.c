/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../../../ecu_test_init.h"

void timer0_interrupt_handler(void);

timer0_t timer0_counter_obj = {
    .timer0_preloaded_value = 0,
    .clock_src = _TIMER0_EXT_SRC,
    .edge = _TIMER0_RISING_EDGE,
    .resolution_bits = _TIMER0_8bit_RES,
    .prescaler_enable = _TIMER0_PRESCALER_DISABLE,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
    .timer0_interrupt_handler = timer0_interrupt_handler,
    .timer0_interrupt_priority = INTERRUPT_HIGH_PRIORITY
};

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
volatile uint16 even_flag = 0;
uint16 timer_val = 0;

void timer0_interrupt_handler(void)
{
    even_flag++;
    if (even_flag % 2 == 0)
        led_turn_on(&led1);
    else
        led_turn_off(&led1);
}

int Timer0_counter_test(void)
{
    Std_ReturnType ret = E_OK;

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret |= timer0_init(&timer0_counter_obj);
    ret |= led_initialize(&led1);

    while(1)
    {
        ret |= timer0_read_value(&timer0_counter_obj, &timer_val);
    }
    return (0);
}

