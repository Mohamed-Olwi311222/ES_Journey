/* 
 * File:   ecu_layer_init.c
 * Author: Mohamed olwi
 *
 * Created on 02 June 2024, 17:44
 */
#include "ecu_layer_init.h"

keypad_t keypad1 =   {
    /*rows*/
    .keypad_rows_pins[0].port = PORTC_INDEX,
    .keypad_rows_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[0].logic = GPIO_HIGH,
    .keypad_rows_pins[0].pin = GPIO_PIN0,
    .keypad_rows_pins[1].port = PORTC_INDEX,
    .keypad_rows_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[1].logic = GPIO_HIGH,
    .keypad_rows_pins[1].pin = GPIO_PIN1,
    .keypad_rows_pins[2].port = PORTC_INDEX,
    .keypad_rows_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[2].logic = GPIO_HIGH,
    .keypad_rows_pins[2].pin = GPIO_PIN2,
    .keypad_rows_pins[3].port = PORTC_INDEX,
    .keypad_rows_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[3].logic = GPIO_HIGH,
    .keypad_rows_pins[3].pin = GPIO_PIN3,
    /*Cols*/
    .keypad_cols_pins[0].port = PORTC_INDEX,
    .keypad_cols_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_cols_pins[0].logic = GPIO_LOW,
    .keypad_cols_pins[0].pin = GPIO_PIN4,
    .keypad_cols_pins[1].port = PORTC_INDEX,
    .keypad_cols_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_cols_pins[1].logic = GPIO_LOW,
    .keypad_cols_pins[1].pin = GPIO_PIN5,
    .keypad_cols_pins[2].port = PORTC_INDEX,
    .keypad_cols_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_cols_pins[2].logic = GPIO_LOW,
    .keypad_cols_pins[2].pin = GPIO_PIN6,
    .keypad_cols_pins[3].port = PORTC_INDEX,
    .keypad_cols_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_cols_pins[3].logic = GPIO_LOW,
    .keypad_cols_pins[3].pin = GPIO_PIN7,
};
segment_t seg1 = {
    .segment_pins[SEGMENT_PIN0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN0].logic = GPIO_LOW,
    .segment_pins[SEGMENT_PIN0].pin = GPIO_PIN0,
    .segment_pins[SEGMENT_PIN0].port = PORTD_INDEX,

    .segment_pins[SEGMENT_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN1].logic = GPIO_LOW,
    .segment_pins[SEGMENT_PIN1].pin = GPIO_PIN1,
    .segment_pins[SEGMENT_PIN1].port = PORTD_INDEX,

    .segment_pins[SEGMENT_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN2].logic = GPIO_LOW,
    .segment_pins[SEGMENT_PIN2].pin = GPIO_PIN2,
    .segment_pins[SEGMENT_PIN2].port = PORTD_INDEX,

    .segment_pins[SEGMENT_PIN3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN3].logic = GPIO_LOW,
    .segment_pins[SEGMENT_PIN3].pin = GPIO_PIN3,
    .segment_pins[SEGMENT_PIN3].port = PORTD_INDEX,

    .segment_type = SEGMENT_COMMON_ANODE
    };
Std_ReturnType ecu_layer_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = keypad_initialize(&keypad1);
    ret = seven_segment_initialize(&seg1);
    return (ret);
}