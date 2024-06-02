#include "../../app.h"
Std_ReturnType keypad_application_initialize(void);
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

uint8 value = 0;
uint8 seg_val = 0;
int keypad_test(void)
{
    Std_ReturnType ret = keypad_application_initialize();
    if (E_NOT_OK == ret)
    {
        return (-1);
    }
   while (1)
   {
       ret = keypad_get_value(&keypad1, &value);
       seg_val = (uint8) value - '0';
       ret = seven_segment_write_number(&seg1, seg_val);
   }
   return (0);
}
Std_ReturnType keypad_application_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = keypad_initialize(&keypad1);
    ret = seven_segment_initialize(&seg1);
    return (ret);
}