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
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status
        };
        gpio_pin_initialize(&pin_obj);
    }
    return (ret);
}

/**
 * @brief turns on the relay
 * @param relay a pointer to relay_t datatype @ref relay_t
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
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return (ret);
}

/**
 * @brief turns off the relay
 * @param relay a pointer to relay_t datatype @ref relay_t
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
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status
        };
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return (ret);
}