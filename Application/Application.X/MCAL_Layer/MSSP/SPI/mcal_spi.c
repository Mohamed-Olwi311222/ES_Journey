/* 
 * File:   mcal_spi.c
 * Author: Mohamed olwi
 *
 * Created on 12 December 2024, 00:36
 */
#include "mcal_spi.h"

/*---------------Static Data types----------------------------------------------*/

/*---------------Static Data types End------------------------------------------*/

/*---------------Static Helper functions declerations---------------------------*/

/*---------------Static Helper functions declerations End-----------------------*/


/**
 * @brief: Initialize the SPI module
 * @param spi_obj the SPI module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType spi_init(const spi_t *const spi_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == spi_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = E_OK;
    }
    return (ret);
}