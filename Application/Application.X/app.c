/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "device_config.h"

int main(void)
{
    Std_ReturnType ret = application_init();
    if (E_NOT_OK == ret)
    {
        return (-1);
    }

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

