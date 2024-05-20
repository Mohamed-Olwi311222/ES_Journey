/* 
 * File:   ecu_relay.c
 * Author: Mohamed olwi
 *
 * Created on May 20, 2024, 12:04 PM
 */
#include "ecu_relay.h"

/**
 * @breif initialize the relay module
 * @param relay a pointer to relay_t datatype @ref relay_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType relay_initialize(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;

    if (NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return (ret);
}

/**
 * 
 * @param relay
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType relay_turn_on(relay_t *relay)
{
    Std_ReturnType ret = E_OK;

    if (NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {

    }
    return (ret);
}

/**
 * 
 * @param relay
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType relay_turn_off(relay_t *relay)
{
    Std_ReturnType ret = E_OK;

    if (NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {

    }
    return (ret);
}