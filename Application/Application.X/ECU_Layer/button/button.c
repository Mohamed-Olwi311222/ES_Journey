/* 
 * File:   ecu_button.h
 * Author: Mohamed olwi
 *
 * Created on April 21, 2024, 3:11 PM
 */
#include "ecu_button.h"
/**
 * @brief initialize the the assigned pin to be input
 * @param btn pointer to the button configurations @ref button_t
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType button_initialize(const button_t *btn)
{
    Std_ReturnType ret = E_OK;
    if (NULL == btn)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(&(btn->button_pin));
    }
    return (ret);
}
#define THRESHOLD_VALUE 200
/**
 * 
 * @param btn pointer to the button configurations @ref button_t
 * @param btn_state a pointer to the button_state @ref button_state_t
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state)
{
    Std_ReturnType ret = E_OK;
    logic_t pin_logic_status = GPIO_LOW;
    button_state_t btn_high_valid_state = BUTTON_RELEASED;
    button_state_t btn_low_valid_status = BUTTON_RELEASED;
    static uint32 btn_high_valid = 0;
    static uint32 btn_low_valid = 0;
 
    if (NULL == btn || NULL == btn_state)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_read_logic(&(btn->button_pin), &pin_logic_status);
        if (BUTTON_ACTIVE_HIGH == btn->button_connection)
        {
            if (GPIO_HIGH == pin_logic_status)
            {
                btn_high_valid++;
                if (btn_high_valid > THRESHOLD_VALUE)
                {
                    btn_high_valid_state = BUTTON_PRESSED;
                }
                else
                {
                    btn_high_valid_state = BUTTON_RELEASED;
                }
            }
            else
            {
                btn_high_valid = 0;
                btn_high_valid_state = BUTTON_RELEASED;
            }
            *btn_state = btn_high_valid_state;
        }
        else
        {
            if (GPIO_HIGH == pin_logic_status)
            {
                btn_low_valid_status = BUTTON_RELEASED;
                btn_low_valid = 0;
            }
            else
            {
                btn_low_valid++;
                if (btn_low_valid > THRESHOLD_VALUE)
                {
                    btn_low_valid_status =  BUTTON_PRESSED;
                }
                else
                {
                    btn_low_valid_status = BUTTON_RELEASED;
                }
            }
            *btn_state = btn_low_valid_status;
        }
    }
    return (ret);
}
/**
 * @brief Make a button be a magic button
 * @param btn pointer to the button configurations @ref button_t
 * @param led the led to turn on and off
 * @param btn_high_status the current status of the buttom
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType btn_high_magic_button(const button_t *btn, led_t *led,const button_state_t *btn_high_status)
{
    Std_ReturnType ret = E_OK;
    static button_state_t btn_high_last_valid_status = BUTTON_RELEASED;
    static led_status led_status = LED_OFF;

    if (NULL == btn || NULL == led || NULL == btn_high_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (*btn_high_status != btn_high_last_valid_status)
        {
            btn_high_last_valid_status = *btn_high_status;
            if (BUTTON_PRESSED == *btn_high_status)
            {
                if (LED_OFF == led_status)
                {
                    led_status = LED_ON;
                    led_turn_on(led);
                }
                else
                {
                    led_turn_off(led);
                    led_status = LED_OFF;
                }
            }
        }
        ret = E_OK;
    }
    return (ret);
}