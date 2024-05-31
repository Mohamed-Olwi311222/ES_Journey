/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */

#include "app.h"
Std_ReturnType application_initialize(void);


int main(void)
{
    Std_ReturnType ret = application_initialize();
    if (E_NOT_OK == ret)
    {
        return (-1);
    }
   while (1)
   {
   }
   return (0);
}
Std_ReturnType application_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;


    return (ret);
}
