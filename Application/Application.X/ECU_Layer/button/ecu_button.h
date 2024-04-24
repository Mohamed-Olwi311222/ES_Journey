/* 
 * File:   ecu_button.h
 * Author: Mohamed olwi
 *
 * Created on April 21, 2024, 3:11 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
/*----------------------------Header Files------------------------------------*/
#include "ecu_button_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../led/ecu_led.h"
/*----------------------------Macros Declarations-----------------------------*/

/*----------------------------Macros Functions Declarations-------------------*/

/*----------------------------DataTypes---------------------------------------*/
typedef enum
{
    BUTTON_RELEASED,
    BUTTON_PRESSED
} button_state_t;

typedef enum
{
    BUTTON_ACTIVE_HIGH, 
    BUTTON_ACTIVE_LOW
} button_active_t;

typedef struct
{
    pin_config_t button_pin;           /* @ref pin_config_t */
    button_state_t button_state_t;     /* @ref button_state_t */
    button_active_t button_connection; /* @ref button_active_t */
} button_t;
/*----------------------------Function Prototypes-----------------------------*/

/**
 * @brief initialize the the assigned pin to be input
 * @param btn pointer to the button configurations @ref button_t
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType button_initialize(const button_t *btn);

/**
 * 
 * @param btn pointer to the button configurations @ref button_t
 * @param state a pointer to the button_state @ref button_state_t
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

Std_ReturnType btn_high_magic_button(const button_t *btn, led_t *led, const button_state_t *btn_high_status);
#endif	/* ECU_BUTTON_H */

