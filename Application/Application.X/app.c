/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"

Std_ReturnType application_init(void);

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};
led_t led3 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};
led_t led4 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN3, .led_status = GPIO_LOW};


void RB4_INT_APP_ISR_HIGH(void)
{
    led_turn_on(&led1);
}
void RB4_INT_APP_ISR_LOW(void)
{
    led_turn_on(&led2);
}

void RB5_INT_APP_ISR_HIGH(void)
{
    led_turn_off(&led2);
}
void RB5_INT_APP_ISR_LOW(void)
{
    led_turn_off(&led1);
}

void RB6_INT_APP_ISR_HIGH(void)
{
    led_turn_on(&led3);
}
void RB6_INT_APP_ISR_LOW(void)
{
    led_turn_on(&led4);
}

void RB7_INT_APP_ISR_HIGH(void)
{
    led_turn_off(&led4);
}
void RB7_INT_APP_ISR_LOW(void)
{
    led_turn_off(&led3);
}
interrupt_RBx_t RB4_obj =
{
    .EXT_interrupt_handler_High = RB4_INT_APP_ISR_HIGH,
    .EXT_interrupt_handler_Low = RB4_INT_APP_ISR_LOW,
    .priority = INTERRUPT_LOW_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN4,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_RBx_t RB5_obj =
{
    .EXT_interrupt_handler_High = RB5_INT_APP_ISR_HIGH,
    .EXT_interrupt_handler_Low = RB5_INT_APP_ISR_LOW,
    .priority = INTERRUPT_LOW_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN5,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_RBx_t RB6_obj =
{
    .EXT_interrupt_handler_High = RB6_INT_APP_ISR_HIGH,
    .EXT_interrupt_handler_Low = RB6_INT_APP_ISR_LOW,
    .priority = INTERRUPT_LOW_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN6,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
interrupt_RBx_t RB7_obj =
{
    .EXT_interrupt_handler_High = RB7_INT_APP_ISR_HIGH,
    .EXT_interrupt_handler_Low = RB7_INT_APP_ISR_LOW,
    .priority = INTERRUPT_LOW_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN7,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
int main(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret |= Interrupt_RBx_Init(&RB4_obj);
    ret |= Interrupt_RBx_Init(&RB5_obj);
    ret |= Interrupt_RBx_Init(&RB6_obj);
    ret |= Interrupt_RBx_Init(&RB7_obj);

    ret |= led_initialize(&led1);
    ret |= led_initialize(&led2);
    ret |= led_initialize(&led3);
    ret |= led_initialize(&led4);
    while(1)
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
