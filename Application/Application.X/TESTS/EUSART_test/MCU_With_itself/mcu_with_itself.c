/*
 * File:   mcu_with_itself.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../../ecu_test_init.h"

int tx = 10;
int rx = 20;
uint16 data = 0;

led_t led1 = {.pin = GPIO_PIN0, .port_name = PORTD_INDEX, .led_status = GPIO_LOW};
led_t led2= {.pin = GPIO_PIN1, .port_name = PORTD_INDEX, .led_status = GPIO_LOW};

void tx_handler(void)
{
    tx++;
}
void rx_handler(void)
{
    rx++;
    (void)eusart_read_byte(&data);
    if ('1' == data)
    {
        (void)led_turn_on(&led1); 
        (void)led_turn_on(&led2); 
    }
    else if ('0' == data)
    {
        (void)led_turn_off(&led1); 
        (void)led_turn_off(&led2); 
    }
}
eusart_t eusart_obj = {
    .eusart_baudrate = 9600,
    .eusart_baudrate_config = BAUDRATE_ASYNC_16_BIT_LOW_SPEED,
    
    .eusart_errors_interrupts.eusart_frame_error_interrupt = NULL,
    .eusart_errors_interrupts.eusart_frame_error_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    .eusart_errors_interrupts.eusart_overrun_error_interrupt = NULL,
    .eusart_errors_interrupts.eusart_overrun_error_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    
    .eusart_rx_config.eusart_9_bit_receive_enable = _EUSART_9_BIT_RECEIVE,
    .eusart_rx_config.eusart_RX_enable = _EUSART_ASYNC_RECEIVE_ENABLE,
    .eusart_rx_config.eusart_RX_interrupt = tx_handler,
    .eusart_rx_config.eusart_RX_interrupt_priority = INTERRUPT_LOW_PRIORITY,

    .eusart_tx_config.eusart_9_bit_transmit_enable = _EUSART_9_BIT_TRANSMISSION,
    .eusart_tx_config.eusart_TX_enable = _EUSART_TRANSMIT_ENABLE,
    .eusart_tx_config.eusart_TX_interrupt = rx_handler,
    .eusart_tx_config.eusart_TX_interrupt_priority = INTERRUPT_LOW_PRIORITY

};
int mcu_with_itself(void)
{  
    Std_ReturnType ret = E_OK;
    
    ret = eusart_init(&eusart_obj);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);

    while (1)
    {
        eusart_write_byte('1');
        __delay_ms(500);
        eusart_write_byte('0');
        __delay_ms(500);
    }
    return (ret);
}
