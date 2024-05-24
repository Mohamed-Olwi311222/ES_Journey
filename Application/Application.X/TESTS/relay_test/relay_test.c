/*
 * File:   relay_test.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */

#include "../../app.h"

Std_ReturnType relay_application_initialize(void);
relay_t relay1 = {
    .relay_port = PORTC_INDEX,
    .relay_pin = GPIO_PIN0,
    .relay_status = RELAY_OFF_STATUS
};
relay_t relay2 = {
    .relay_port = PORTC_INDEX,
    .relay_pin = GPIO_PIN1,
    .relay_status = RELAY_OFF_STATUS
};
int relay_test(void)
{
    Std_ReturnType ret = relay_application_initialize();
    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    while (1)
    {
        relay_turn_on(&relay1);
        relay_turn_off(&relay2);
        __delay_ms(5000);

        relay_turn_off(&relay1);
        relay_turn_on(&relay2);
        __delay_ms(5000);

    }
    
   

    return (0);
}
Std_ReturnType relay_application_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = relay_initialize(&relay1);
    ret = relay_initialize(&relay2);

    return (ret);
}
