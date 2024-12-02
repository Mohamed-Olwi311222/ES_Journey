/*
 * File:   rx_src.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../../../ecu_test_init.h"
led_t led1 = {
    .port_name = PORTD_INDEX,
    .pin = 0,
    .led_status = LED_OFF,
};
eusart_t eusart_obj = {
    .eusart_baudrate = 9600,
    .eusart_baudrate_config = BAUDRATE_ASYNC_16_BIT_LOW_SPEED,
    
    .eusart_errors_interrupts.eusart_frame_error_interrupt = NULL,
    .eusart_errors_interrupts.eusart_frame_error_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    .eusart_errors_interrupts.eusart_overrun_error_interrupt = NULL,
    .eusart_errors_interrupts.eusart_overrun_error_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    
    .eusart_rx_config.eusart_9_bit_receive_enable = _EUSART_9_BIT_RECEIVE,
    .eusart_rx_config.eusart_RX_enable = _EUSART_ASYNC_RECEIVE_ENABLE,


    .eusart_tx_config.eusart_9_bit_transmit_enable = _EUSART_9_BIT_TRANSMISSION,
    .eusart_tx_config.eusart_TX_enable = _EUSART_TRANSMIT_ENABLE,

};
int rx_src(void)
{  
    Std_ReturnType ret = E_OK;
    uint16 data = 0;
    led_initialize(&led1);
    
    ret = eusart_init(&eusart_obj);
    while (1)
    {
       ret |= eusart_read_byte(&data);
       if (data == '1')
       {
           led_turn_on(&led1);
       }
       else if (data == '0')
       {
           led_turn_off(&led1);
       }
    }
    return (ret);
}
