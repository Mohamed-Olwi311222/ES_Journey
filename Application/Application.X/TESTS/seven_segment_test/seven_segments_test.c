/*
 * File:   seven_segments_test.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */

#include "../../app.h"
Std_ReturnType seven_segment_application_initialize(void);

pin_config_t seg1_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT
};

pin_config_t seg2_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN1,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT
};

pin_config_t seg3_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN2,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT
};

pin_config_t seg4_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN3,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT
};

pin_config_t seg5_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN4,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT
};

pin_config_t seg6_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN5,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT
};

segment_t seg1 = {
    .segment_pins[SEGMENT_PIN0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN0].logic = GPIO_LOW,
    .segment_pins[SEGMENT_PIN0].pin = GPIO_PIN0,
    .segment_pins[SEGMENT_PIN0].port = PORTC_INDEX,

    .segment_pins[SEGMENT_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN1].logic = GPIO_LOW,
    .segment_pins[SEGMENT_PIN1].pin = GPIO_PIN1,
    .segment_pins[SEGMENT_PIN1].port = PORTC_INDEX,

    .segment_pins[SEGMENT_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN2].logic = GPIO_LOW,
    .segment_pins[SEGMENT_PIN2].pin = GPIO_PIN2,
    .segment_pins[SEGMENT_PIN2].port = PORTC_INDEX,

    .segment_pins[SEGMENT_PIN3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[SEGMENT_PIN3].logic = GPIO_LOW,
    .segment_pins[SEGMENT_PIN3].pin = GPIO_PIN3,
    .segment_pins[SEGMENT_PIN3].port = PORTC_INDEX,

    .segment_type = SEGMENT_COMMON_CATHODE
    };

uint8 hours = 23, minutes = 59, seconds = 45;
uint8 counter = 0;
int seven_segment_test(void)
{
    Std_ReturnType ret = seven_segment_application_initialize();
    if (E_NOT_OK == ret)
    {
        return (-1);
    }
   while (1)
   {
       for (counter = 0; counter < 50; counter++)
       {
           //hours
           ret = seven_segment_write_number(&seg1, (uint8)(hours / 10));
           ret = gpio_pin_write_logic(&seg1_enable, GPIO_HIGH);
           __delay_us(3333);
           ret = gpio_pin_write_logic(&seg1_enable, GPIO_LOW);

           ret = seven_segment_write_number(&seg1, (uint8)(hours % 10));
           ret = gpio_pin_write_logic(&seg2_enable, GPIO_HIGH);
           __delay_us(3333);
           ret = gpio_pin_write_logic(&seg2_enable, GPIO_LOW);
           
           //minutes
           ret = seven_segment_write_number(&seg1, (uint8)(minutes / 10));
           ret = gpio_pin_write_logic(&seg3_enable, GPIO_HIGH);
           __delay_us(3333);
           ret = gpio_pin_write_logic(&seg3_enable, GPIO_LOW);

           ret = seven_segment_write_number(&seg1, (uint8)(minutes % 10));
           ret = gpio_pin_write_logic(&seg4_enable, GPIO_HIGH);
           __delay_us(3333);
           ret = gpio_pin_write_logic(&seg4_enable, GPIO_LOW);
           
           //seconds
           ret = seven_segment_write_number(&seg1, (uint8)(seconds / 10));
           ret = gpio_pin_write_logic(&seg5_enable, GPIO_HIGH);
           __delay_us(3333);
           ret = gpio_pin_write_logic(&seg5_enable, GPIO_LOW);

           ret = seven_segment_write_number(&seg1, (uint8)(seconds % 10));
           ret = gpio_pin_write_logic(&seg6_enable, GPIO_HIGH);
           __delay_us(3333);
           ret = gpio_pin_write_logic(&seg6_enable, GPIO_LOW);
       }
       seconds++;
       if (60 == seconds)
       {
           minutes++;
           seconds = 0;
       }
       if (60 == minutes)
       {
           hours++;
           minutes = 0;
       }
       if (24 == hours)
       {
           hours = 0;
       }
   }
   return (0);
}
Std_ReturnType seven_segment_application_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = seven_segment_initialize(&seg1);
    ret = gpio_pin_direction_initialize(&seg1_enable);
    ret = gpio_pin_direction_initialize(&seg2_enable);
    ret = gpio_pin_direction_initialize(&seg3_enable);
    ret = gpio_pin_direction_initialize(&seg4_enable);
    ret = gpio_pin_direction_initialize(&seg5_enable);
    ret = gpio_pin_direction_initialize(&seg6_enable);

    return (ret);
}

