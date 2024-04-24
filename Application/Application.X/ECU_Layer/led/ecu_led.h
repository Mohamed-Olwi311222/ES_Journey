/* 
 * File:   ecu_led.h
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:20 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*----------------------------Header Files------------------------------------*/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"
/*----------------------------Macros Declarations-----------------------------*/

/*----------------------------Macros Functions Declarations-------------------*/

/*----------------------------DataTypes---------------------------------------*/
typedef enum
{
    LED_OFF,
    LED_ON
}led_status;

typedef struct
{
    uint8 port_name : 4;
    uint8 pin : 3;
    uint8 led_status : 1;
}led_t;
/*----------------------------Function Prototypes-----------------------------*/
Std_ReturnType turn_on_leds(void);

/**
 * @brief initialize the assigned pin to be output and turn the led off
 * @param led pointer to the led module configurations
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType led_intitialize(const led_t *led);

/**
 * @brief turn the led on
 * @param led pointer to the led module configurations
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType led_turn_on(const led_t *led);

/**
 * @brief turn the led off
 * @param led pointer to the led module configurations
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType led_turn_off(const led_t *led);

/**
 * @brief toggle the light of the led
 * @param led pointer to the led module configurations
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType led_toggle(const led_t *led);
#endif	/* ECU_LED_H */

