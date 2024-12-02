/*
 * File:   rx_src.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../../../ecu_test_init.h"

eusart_t eusart_obj = {
    .eusart_baudrate = 9600,
    .eusart_baudrate_config = BAUDRATE_SYNC_16_BIT,
    
    .eusart_errors_interrupts.eusart_frame_error_interrupt = NULL,
    .eusart_errors_interrupts.eusart_frame_error_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    .eusart_errors_interrupts.eusart_overrun_error_interrupt = NULL,
    .eusart_errors_interrupts.eusart_overrun_error_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    
    .eusart_rx_config.eusart_9_bit_receive_enable = _EUSART_9_BIT_RECEIVE,
    .eusart_rx_config.eusart_RX_interrupt = NULL,
    .eusart_rx_config.eusart_RX_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    .eusart_rx_config.eusart_sync_cont_reception_mode = _EUSART_SYNC_CONTINUOUS_RECEIVE_ENABLE,
    .eusart_rx_config.eusart_sync_single_reception_mode = _EUSART_SYNC_MASTER_SINGLE_RECEIVE_DISABLE,

    .eusart_tx_config.eusart_9_bit_transmit_enable = _EUSART_9_BIT_TRANSMISSION,
    .eusart_tx_config.eusart_TX_enable = _EUSART_TRANSMIT_DISABLE,
    .eusart_tx_config.eusart_TX_interrupt = NULL,
    .eusart_tx_config.eusart_TX_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    .eusart_tx_config.sync_clk_src = _EUSART_SYNC_SLAVE_MODE
};
led_t led1 = {
    .port_name = PORTD_INDEX,
    .pin = 0,
    .led_status = LED_OFF,
};
int rx_src(void)
{  
    Std_ReturnType ret = E_OK;
    uint16 data = 0;
    
    ret |= eusart_init(&eusart_obj);
    ret |= led_initialize(&led1);
    
    while (1)
    {
        ret |= eusart_read_data(&data);
        
        if ('1' == data)
            ret |= led_turn_on(&led1);
        else
            ret |= led_turn_off(&led1);
    }
    return (ret);
}
