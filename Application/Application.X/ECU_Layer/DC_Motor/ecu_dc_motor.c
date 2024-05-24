/* 
 * File:   ecu_dc_motor.c
 * Author: Mohamed olwi
 *
 * Created on May 24, 2024, 2:00 AM
 */

#include "ecu_dc_motor.h"

/**
 * @brief initialize the dc_motor 
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_pin_t
 * @return E_OK if success otherwise E_NOT_OK 
 */
Std_ReturnType dc_motor_initialize(const dc_motor_pin_t *dc_motor)
{
    Std_ReturnType ret = E_OK;

    if (NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        
    }
    return (ret);
}

/**
 * @brief make the motor turn right or forward
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_pin_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType dc_motor_move_forward(const dc_motor_pin_t *dc_motor)
{
    Std_ReturnType ret = E_OK;

    if (NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        
    }
    return (ret);
}

/**
 * @brief make the motor turn left or backward
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_pin_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType dc_motor_move_backward(const dc_motor_pin_t *dc_motor)
{
    Std_ReturnType ret = E_OK;

    if (NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        
    }
    return (ret); 
}

/**
 * @brief make the motor stop
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_pin_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType dc_motor_stop(const dc_motor_pin_t *dc_motor)
{
    Std_ReturnType ret = E_OK;

    if (NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {    
        
    }
    return (ret);
}