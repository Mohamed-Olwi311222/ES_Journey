/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../app.h"
#include "../MCAL_Layer/EEPROM/mcal_eeprom.h"

Std_ReturnType EEPROM_test_application_init(void);


led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};


volatile uint8 selected_program = 0;

void program1(void)
{
    led_turn_on(&led1);
    __delay_ms(250);
    led_turn_off(&led1);
    __delay_ms(250);
}
void program2(void)
{
    led_turn_on(&led2);
    __delay_ms(250);
    led_turn_off(&led2);
    __delay_ms(250);
}

void INT0_App_ISR(void)
{
    selected_program++;
    if (1 == selected_program)
    {
        led_turn_off(&led2);
    }
    else if (2 == selected_program)
    {
        led_turn_off(&led1);   
    }
    else
    {
        selected_program = 0;
        led_turn_off(&led1);
        led_turn_off(&led2);
    }
    Data_EEPROM_Write_Byte(0x3ff, selected_program);
}

interrupt_INTx_t int0_obj = {
    .EXT_interrupt_handler = INT0_App_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .source = INTERRUPT_EXTERNAL_INT0,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

int EEPROM_test(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret |= led_initialize(&led1);
    ret |= led_initialize(&led2);
    ret |= Interrupt_INTx_Init(&int0_obj);
    ret |= Data_EEPROM_Read_Byte(0x3ff, &selected_program);
    while(1)
    {
        if (1 == selected_program)
        {
            program1();
        }
        else if (2 == selected_program)
        {
            program2();
        }
        else
        {
            led_turn_off(&led1);
            led_turn_off(&led2);
        }
    }
   return (0);
}
Std_ReturnType EEPROM_test_application_init(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = ecu_layer_initialize();

    return (ret);
}
