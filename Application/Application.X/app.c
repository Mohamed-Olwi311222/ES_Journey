/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */

#include "app.h"

Std_ReturnType application_initialize(void);
relay_t relay = {
    .relay_port = PORTC_INDEX,
    .relay_pin = GPIO_PIN0,
    .relay_status = RELAY_OFF_STATUS
};

int main(void)
{
    Std_ReturnType ret = application_initialize();

   

    return (0);
}
Std_ReturnType application_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = relay_initialize(&relay);
    return (ret);
}
