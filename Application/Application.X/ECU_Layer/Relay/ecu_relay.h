/* 
 * File:   ecu_relay.h
 * Author: Mohamed olwi
 *
 * Created on May 20, 2024, 12:03 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
/*----------------------------Header Files------------------------------------*/
#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*----------------------------Macros Declarations-----------------------------*/
#define RELAY_ON_STATUS             0x01U
#define RELAY_OFF_STATUS            0x00U
/*----------------------------Macros Functions Declarations-------------------*/

/*----------------------------DataTypes---------------------------------------*/

/**
 * struct relay_t - struct for relay module
 * @relay_port: the port that the relay's pin belong to
 * @relay_pin: the pin that the relay is connected to
 * @relay_status: the status of the relay
*/
typedef struct
{
    uint8 relay_port    : 4;
    uint8 relay_pin     : 3;
    uint8 relay_status  : 1;
}relay_t;
/*----------------------------Function Prototypes-----------------------------*/

/**
 * @breif initialize the relay module
 * @param relay a pointer to relay_t datatype @ref relay_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType relay_initialize(const relay_t *relay);

/**
 * @brief turns on the relay
 * @param relay a pointer to relay_t datatype @ref relay_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType relay_turn_on(relay_t *relay);

/**
 * @brief turns off the relay
 * @param relay a pointer to relay_t datatype @ref relay_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType relay_turn_off(relay_t *relay);

#endif	/* ECU_RELAY_H */

