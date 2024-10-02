/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "device_config.h"
#include "MCAL_Layer/Timers/Timer3/hal_timer3.h"
void timer3_interrupt_handler(void);

timer3_t timer3_obj = {
    .timer3_preloaded_value = 3036,
    .timer3_interrupt_handler = timer3_interrupt_handler,
    .timer3_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    .clock_src = _TIMER3_INT_SRC,
    .ext_clk_sync = _TIMER3_ASYNC,
    .prescaler_value = TIMER3_PRESCALER_DIV_BY_8,
    .rw_mode = _TIMER3_RW_16bit_OP
};
led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};

void timer3_interrupt_handler(void)
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
    ret |= timer3_init(&timer3_obj);
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

