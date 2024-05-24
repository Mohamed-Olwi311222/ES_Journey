/*
 * File:   dc_motor_test.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */

#include "../../app.h"

Std_ReturnType application_initialize(void);
dc_motor_t  dc_motor_1 = {
    .dc_motor_pins[DC_MOTOR_PIN1].port = PORTC_INDEX,
    .dc_motor_pins[DC_MOTOR_PIN1].pin = GPIO_PIN0,
    .dc_motor_pins[DC_MOTOR_PIN1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pins[DC_MOTOR_PIN1].direction = GPIO_DIRECTION_OUTPUT,

    .dc_motor_pins[DC_MOTOR_PIN2].port = PORTC_INDEX,
    .dc_motor_pins[DC_MOTOR_PIN2].pin = GPIO_PIN1,
    .dc_motor_pins[DC_MOTOR_PIN2].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pins[DC_MOTOR_PIN2].direction = GPIO_DIRECTION_OUTPUT
};

dc_motor_t  dc_motor_2 = {
    .dc_motor_pins[DC_MOTOR_PIN1].port = PORTC_INDEX,
    .dc_motor_pins[DC_MOTOR_PIN1].pin = GPIO_PIN2,
    .dc_motor_pins[DC_MOTOR_PIN1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pins[DC_MOTOR_PIN1].direction = GPIO_DIRECTION_OUTPUT,

    .dc_motor_pins[DC_MOTOR_PIN2].port = PORTC_INDEX,
    .dc_motor_pins[DC_MOTOR_PIN2].pin = GPIO_PIN3,
    .dc_motor_pins[DC_MOTOR_PIN2].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor_pins[DC_MOTOR_PIN2].direction = GPIO_DIRECTION_OUTPUT

};
int dc_motor_test(void)
{
    Std_ReturnType ret = application_initialize();
    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    while (1)
    {
        ret = dc_motor_move_forward(&dc_motor_1);
        ret = dc_motor_move_forward(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_backward(&dc_motor_1);
        ret = dc_motor_move_backward(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_stop(&dc_motor_1);
        ret = dc_motor_stop(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_forward(&dc_motor_1);
        ret = dc_motor_move_backward(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_stop(&dc_motor_1);
        ret = dc_motor_stop(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_backward(&dc_motor_1);
        ret = dc_motor_move_forward(&dc_motor_2);
        __delay_ms(3000);
    }
    return (0);
}
Std_ReturnType dc_motorapplication_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = dc_motor_initialize(&dc_motor_1);
    ret = dc_motor_initialize(&dc_motor_2);


    return (ret);
}

