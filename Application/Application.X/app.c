/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */

#include "app.h"

uint8 value = 0;
int main(void)
{
    Std_ReturnType ret = ecu_layer_initialize();
    if (E_NOT_OK == ret)
    {
        return (-1);
    }
   while (1)
   {
       ret = keypad_get_value(&keypad1, &value);
   }
   return (0);
}

