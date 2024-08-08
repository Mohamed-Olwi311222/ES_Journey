/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};
led_t led3 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};
Std_ReturnType application_init(void);

int main(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }

    ret |= led_initialize(&led1);
    ret |= led_initialize(&led2);
    ret |= led_initialize(&led3);
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
