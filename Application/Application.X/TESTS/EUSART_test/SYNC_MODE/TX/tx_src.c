/*
 * File:   tx_src.c
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
    .eusart_rx_config.eusart_sync_cont_reception_mode = _EUSART_SYNC_CONTINUOUS_RECEIVE_DISABLE,
    .eusart_rx_config.eusart_sync_single_reception_mode = _EUSART_SYNC_MASTER_SINGLE_RECEIVE_DISABLE,

    .eusart_tx_config.eusart_9_bit_transmit_enable = _EUSART_9_BIT_TRANSMISSION,
    .eusart_tx_config.eusart_TX_enable = _EUSART_TRANSMIT_ENABLE,
    .eusart_tx_config.eusart_TX_interrupt = NULL,
    .eusart_tx_config.eusart_TX_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    .eusart_tx_config.sync_clk_src = _EUSART_SYNC_MASTER_MODE
};

int tx_src(void)
{  
    Std_ReturnType ret = E_OK;
    
    ret |= eusart_init(&eusart_obj);
    while (1)
    {
        eusart_write_data('1');
        __delay_ms(500);
        eusart_write_data('0');
        __delay_ms(500);
    }
    return (ret);
}
