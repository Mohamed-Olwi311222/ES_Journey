/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "device_config.h"
#include "MCAL_Layer/Timers/Timer2/hal_timer2.h"

void timer2_interrupt_handler();

timer2_t timer2_obj = {
    .postscaler_value = TIMER2_POSTSCALERR_DIV_BY_16,
    .prescaler_value = TIMER2_PRESCALER_DIV_BY_1,
    .PR2_preloaded_value = 249,
    .TMR2_preloaded_value = 0,
    .timer2_interrupt_handler = timer2_interrupt_handler,
    .timer2_interrupt_priority = INTERRUPT_LOW_PRIORITY
};
led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

void timer2_interrupt_handler()
{
    led_toggle(&led1);
}
int main(void)
{
    Std_ReturnType ret = application_init();
    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret |= timer2_init(&timer2_obj);
    ret |= led_initialize(&led1);
    while(1)
    {
       
    }
    return (0);
}

Std_ReturnType application_init(void)
{
    Std_ReturnType ret = E_OK;
    ret = ecu_layer_initialize();

    return (ret);
}

