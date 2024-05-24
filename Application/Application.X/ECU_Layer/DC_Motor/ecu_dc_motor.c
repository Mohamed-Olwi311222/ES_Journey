/* 
 * File:   ecu_dc_motor.c
 * Author: Mohamed olwi
 *
 * Created on May 24, 2024, 2:00 AM
 */

#include "ecu_dc_motor.h"
static pin_config_t motor_pin1;
static pin_config_t motor_pin2;
/**
 * @brief initialize the dc_motor 
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_t
 * @return E_OK if success otherwise E_NOT_OK 
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;

    if (NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*DC_MOTOR PIN1*/
        motor_pin1.port = dc_motor->dc_motor[DC_MOTOR_PIN1].dc_motor_port;
        motor_pin1.pin = dc_motor->dc_motor[DC_MOTOR_PIN1].dc_motor_pin;
        motor_pin1.logic = dc_motor->dc_motor[DC_MOTOR_PIN1].dc_motor_status;
        motor_pin1.direction = GPIO_DIRECTION_OUTPUT;

        /*DC_MOTOR PIN2*/
        motor_pin2.port = dc_motor->dc_motor[DC_MOTOR_PIN2].dc_motor_port;
        motor_pin2.pin = dc_motor->dc_motor[DC_MOTOR_PIN2].dc_motor_pin;
        motor_pin2.logic = dc_motor->dc_motor[DC_MOTOR_PIN2].dc_motor_status;
        motor_pin2.direction = GPIO_DIRECTION_OUTPUT;

        gpio_pin_initialize(&motor_pin1);
        gpio_pin_initialize(&motor_pin2);
    }
    return (ret);
}

/**
 * @brief make the motor turn right or forward
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType dc_motor_move_forward(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;

    if (NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&motor_pin1, GPIO_HIGH);
        gpio_pin_write_logic(&motor_pin2, GPIO_LOW);
    }
    return (ret);
}

/**
 * @brief make the motor turn left or backward
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType dc_motor_move_backward(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;

    if (NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        
        gpio_pin_write_logic(&motor_pin1, GPIO_LOW);
        gpio_pin_write_logic(&motor_pin2, GPIO_HIGH);
    }
    return (ret); 
}

/**
 * @brief make the motor stop
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor)
{
    Std_ReturnType ret = E_OK;

    if (NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&motor_pin1, GPIO_LOW);
        gpio_pin_write_logic(&motor_pin2, GPIO_LOW);
    }
    return (ret);
}