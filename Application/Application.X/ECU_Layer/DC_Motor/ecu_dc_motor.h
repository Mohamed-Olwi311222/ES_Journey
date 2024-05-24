/* 
 * File:   ecu_dc_motor.h
 * Author: Mohamed olwi
 *
 * Created on May 24, 2024, 1:58 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H
/*----------------------------Header Files------------------------------------*/
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*----------------------------Macros Declarations-----------------------------*/
#define DC_MOTOR_ON_STATUS      0x01U
#define DC_MOTOR_OFF_STATUS     0x00U

/*----------------------------Macros Functions Declarations-------------------*/

/*----------------------------DataTypes---------------------------------------*/

/**
 * struct dc_motor_pin_t - a struct defining a pin for the dc motor
 * @dc_motor_port: the port which the pin is connected to
 * @dc_motor_pin: the pin that the pin of the dc motor is connected to
 * @dc_motor_status: the status of the pin of the dc motor
 */
typedef struct
{
    uint8 dc_motor_port     : 4;
    uint8 dc_motor_pin      : 3;
    uint8 dc_motor_status   : 1;

}dc_motor_pin_t;

/**
 * struct dc_motor_t - a struct defining the 2 motor pins
 * @dc_motor: the pins of the dc_motor
 */
typedef struct
{
    dc_motor_pin_t dc_motor[2];
}dc_motor_t;
/*----------------------------Function Prototypes-----------------------------*/

/**
 * @brief initialize the dc_motor 
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_pin_t
 * @return E_OK if success otherwise E_NOT_OK 
 */
Std_ReturnType dc_motor_initialize(const dc_motor_pin_t *dc_motor);

/**
 * @brief make the motor turn right or forward
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_pin_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType dc_motor_move_forward(const dc_motor_pin_t *dc_motor);

/**
 * @brief make the motor turn left or backward
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_pin_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType dc_motor_move_backward(const dc_motor_pin_t *dc_motor);

/**
 * @brief make the motor stop
 * @param dc_motor the pointer to the dc_motor config @ref dc_motor_pin_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType dc_motor_stop(const dc_motor_pin_t *dc_motor);

#endif	/* ECU_DC_MOTOR_H */

