/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */

#include "app.h"


int main(void)
{
    Std_ReturnType ret = ecu_layer_initialize();
    if (E_NOT_OK == ret)
    {
        return (-1);
    }
   while (1)
   {

   }
   return (0);
}

