/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */

#include "app.h"
Std_ReturnType application_initialize(void);
button_t btn_low = {
    .button_connection = BUTTON_ACTIVE_LOW,
    .button_pin.port = PORTD_INDEX,
    .button_pin.pin = GPIO_PIN0,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_HIGH,
    .button_state_t = BUTTON_RELEASED
};

button_t btn_high = {
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_pin.port = PORTC_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_state_t = BUTTON_RELEASED
};
led_t led1 = {
    .port_name = PORTC_INDEX,
    .pin = 0,
    .led_status = LED_OFF,
};
led_t led2 = {
    .port_name = PORTC_INDEX,
    .pin = 1,
    .led_status = LED_OFF,
};
void program_1();
void program_2();
void program_3();
int main(void)
{
    Std_ReturnType ret = application_initialize();
    button_state_t btn_high_status = BUTTON_RELEASED;
    button_state_t btn_low_status = BUTTON_RELEASED;
   button_state_t btn_high_last_valid_status = BUTTON_RELEASED;

    

   uint8 program_selected = 0;

    if (E_NOT_OK == ret)
    {
        exit(E_NOT_OK);
    }
    while (1)
    {
        button_read_state(&btn_high, &btn_high_status);
        button_read_state(&btn_low, &btn_low_status);
        // btn_high_magic_button(&btn_high, &led1, &btn_high_status);
       if (btn_high_status != btn_high_last_valid_status)
       {
           btn_high_last_valid_status = btn_high_status;
           if (BUTTON_PRESSED == btn_high_status)
           {
               program_selected++;
               switch (program_selected)
               {
                    case 1: program_1(); break;
                    case 2: program_2(); break;
                    case 3: program_3(); break;
                    default: program_selected = 0;
               }
           }
       }
    }
    return (0);
}
Std_ReturnType application_initialize(void)
{
    Std_ReturnType ret = E_OK;
    ret = button_initialize(&btn_high);
    ret = button_initialize(&btn_low);
    ret = led_intitialize(&led1);
    ret = led_intitialize(&led2);

    return (ret);
}
void program_1()
{
    led_turn_on(&led1);
    __delay_ms(250);
    led_turn_off(&led1);
    __delay_ms(250);
}
void program_2()
{
    led_turn_on(&led2);
    __delay_ms(250);
    led_turn_off(&led2);
    __delay_ms(250);
}
void program_3()
{
    led_turn_on(&led1);
    led_turn_on(&led2);
    __delay_ms(250);
    led_turn_off(&led1);
    led_turn_off(&led2);
    __delay_ms(250);
}