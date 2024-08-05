/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
Std_ReturnType application_init(void);
 void INT0_App_ISR(void)
{
    led_toggle(&led1);
}
interrupt_INTx_t int0_obj = {
    .EXT_interrupt_handler = INT0_App_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .source = INTERRUPT_EXTERNAL_INT0,
    .priortiy = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

int main(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret |= Interrupt_INTx_Init(&int0_obj);
    ret |= led_initialize(&led1);
    while (1)
    {
    }
   return (0);
}
Std_ReturnType application_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();

    return (ret);
}
