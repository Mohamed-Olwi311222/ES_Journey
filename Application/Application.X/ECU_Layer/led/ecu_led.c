#include "ecu_led.h"

Std_ReturnType turn_on_leds(void)
{
   /* MY_TRISC = 0x00;
    __delay_ms(2000);
    //USING BIT_FIELDS
    LATC_REG->LATC0 = 1;
    LATC_REG->LATC_REGISTER = 0;
   */

    /*  USING BITWISE*/
    
    MY_TRISC = 0x00;
    static uint8 _POS = 0x00;
//    while(1)
//    {
        
        TOGGLE_BIT(MY_LATC, _POS);
        __delay_ms(500);
        if (_POS < 8)
        {
            _POS++;
        }
        else
            _POS = 0;
//    }
    return (E_OK);
}
/**
 * @brief initialize the assigned pin to be output and turn the led off
 * @param led pointer to the led module configurations
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType led_intitialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
                            .port = led->port_name,
                            .pin = led->pin ,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = led->led_status
                           };
        gpio_pin_initialize(&pin);
    }
    return (ret);
}
/**
 * @brief turn the led on
 * @param led pointer to the led module configurations
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType led_turn_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
                            .port = led->port_name,
                            .pin = led->pin ,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = led->led_status
                           };
        gpio_pin_write_logic(&pin, GPIO_HIGH);
    }
    return (ret);
}
/**
 * @brief turn the led off
 * @param led pointer to the led module configurations
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType led_turn_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
                            .port = led->port_name,
                            .pin = led->pin ,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = led->led_status
                           };
        gpio_pin_write_logic(&pin, GPIO_LOW);
    }
    return (ret);
}
/**
 * @brief toggle the light of the led
 * @param led pointer to the led module configurations
 * @return E_OK if status success otherwise E_NOT_OK
 */
Std_ReturnType led_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin = {
                            .port = led->port_name,
                            .pin = led->pin ,
                            .direction = GPIO_DIRECTION_OUTPUT,
                            .logic = led->led_status
                           };
        gpio_pin_toggle_logic(&pin);
    }
    return (ret);
}