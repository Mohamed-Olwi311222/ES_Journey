/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */

#include "app.h"
Std_ReturnType application_initialize(void);
// uint8 hours = 23, minutes = 59, seconds = 45;
// uint8 counter = 0;
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
    .segment_pins[SEGMENT_PIN3].port = PORTC_INDEX
    };
int main(void)
{
    Std_ReturnType ret = application_initialize();
    uint8 num = 0;
    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    while (1)
    {
        if (num > 9)
            num = 0;
        ret = seven_segment_write_number(&seg1, num);
        num++;
        __delay_ms(200);
    }
    
//    while (1)
//    {
//        for (counter = 0; counter < 50; counter++)
//        {
//        ret = gpio_port_write_logic(PORTD_INDEX, 0x01);
//        ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)hours / 10));
//        __delay_us(3333);
//        ret = gpio_port_write_logic(PORTD_INDEX, 0x02);
//        ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)hours % 10));
//        __delay_us(3333);
//        ret = gpio_port_write_logic(PORTD_INDEX, 0x04);
//        ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)minutes / 10));
//        __delay_us(3333);  
//        ret = gpio_port_write_logic(PORTD_INDEX, 0x08);
//        ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)minutes % 10));
//        __delay_us(3333); 
//        ret = gpio_port_write_logic(PORTD_INDEX, 0x10);  
//        ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)seconds / 10));
//        __delay_us(3333);
//        ret = gpio_port_write_logic(PORTD_INDEX, 0x20);  
//        ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)seconds % 10));
//        __delay_us(3333);
//        }
//        seconds++;
//        if (60 == seconds)
//        {
//            minutes++;
//            seconds = 0;
//        }
//        if (60 == minutes)
//        {
//            hours++;
//            minutes = 0;
//        }
//        if (24 == hours)
//        {
//            hours = 0;
//        }
//    }
//    return (0);
}
Std_ReturnType application_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    // ret = gpio_port_direction_initialize(PORTC_INDEX, 0xF0);
    // ret = gpio_port_direction_initialize(PORTD_INDEX, 0xC0);
    // ret = gpio_port_write_logic(PORTC_INDEX, 0);
    // ret = gpio_port_write_logic(PORTD_INDEX, 0x3F);

    ret = seven_segment_initialize(&seg1);
    return (ret);
}
