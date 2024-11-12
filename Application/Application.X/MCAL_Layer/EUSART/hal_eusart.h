/* 
 * File:   hal_eusart.h
 * Author: Mohamed olwi
 *
 * Created on 08 November 2024, 11:34
 */
#ifndef HAL_EUSART_H
#define	HAL_EUSART_H
/*----------------------------Header Files------------------------------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include <xc.h>
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_layer_cfg.h"
#include "hal_eusart_cfg.h"
/*----------------------------Macros Declarations-----------------------------*/
#if EUSART_ACTIVE_MODE == EUSART_SYNC_MODE                   /* EUSART SYNC MODE ONLY */
/*==================TXSTA REG==================*/
/*----------CSRC Bit----------*/
#define _EUSART_SYNC_MASTER_MODE                             1 /* Synchronous Master Mode */
#define _EUSART_SYNC_SLAVE_MODE                              0 /* Synchronous Slave Mode */
/*----------SYNC Bit-----------*/
#define _EUSART_SYNC_MODE                                    1 /* EUSART Sync Mode */   
/*==================RCSTA REG==================*/
/*----------SREN Bit-----------*/
#define _EUSART_SYNC_MASTER_SINGLE_RECEIVE_ENABLE            1 /* EUSART Sync mode single receive enable */
#define _EUSART_SYNC_MASTER_SINGLE_RECEIVE_DISABLE           0 /* EUSART Sync mode single receive disable */
/*----------CREN Bit-----------*/
#define _EUSART_SYNC_CONTINUES_RECEIVE_ENABLE                1 /* EUSART Sync Enables continuous receive until enable bit */
#define _EUSART_SYNC_CONTINUES_RECEIVE_DISABLE               0 /* EUSART Sync Disables continuous receive */
/*==================BAUDCON REG================*/
#define _EUSART_SYNC_CLK_IDLE_STATE_LOW_LEVEL                1 /* Idle state for clock (CK) is a high level */
#define _EUSART_SYNC_CLK_IDLE_STATE_HIGH_LEVEL               0 /* Idle state for clock (CK) is a low level */
#endif
#if EUSART_ACTIVE_MODE == EUSART_ASYNC_MODE                /* EUSART ASYNC MODE ONLY */
/*==================TXSTA REG==================*/
/*----------SYNC Bit-----------*/
#define _EUSART_ASYNC_MODE                                   0 /* EUSART ASync Mode */
/*----------BRGH Bit-----------*/
#define _EUSART_ASYNC_HIGH_SPEED                             1 /* EUSART Async mode high speed*/
#define _EUSART_ASYNC_LOW_SPEED                              0 /* EUSART Async mode low speed*/
/*==================RCSTA REG==================*/
/*----------RX9 Bit------------*/
#define _EUSART_ASYNC_RECEIVE_ENABLE                         1 /* EUSART ASync Enables receiver */
#define _EUSART_ASYNC_RECEIVE_DISABLE                        0 /* EUSART ASync Disables receiver */
/*----------ADEN Bit-----------*/
#define _EUSART_ASYNC_ADDRESS_DETECTION_ENABLE               1 /* Enables address detection, enables interrupt and loads the receive buffer when RSR<8> is set */
#define _EUSART_ASYNC_ADDRESS_DETECTION_DISABLE              0 /* Disables address detection, all bytes are received and ninth bit can be used as parity bit */
/*==================BAUDCON REG================*/
/*----------WUE Bit-----------*/
#define _EUSART_ASYNC_WAKE_UP_ENABLE                         1 /* EUSART will continue to sample the RX pin – interrupt generated on falling edge; bit cleared in hardware on following rising edge */
#define _EUSART_ASYNC_WAKE_UP_DISABLE                        0 /* RX pin not monitored or rising edge detected */
/*----------ABDEN Bit---------*/
#define _EUSART_ASYNC_AUTO_BAUD_MEASUREMENT_ENABLE           1 /* Enable baud rate measurement on the next character. Requires reception of a Sync field (55h); cleared in hardware upon completion */
#define _EUSART_ASYNC_AUTO_BAUD_MEASUREMENT_DISABLE          0 /* Baud rate measurement disabled or completed */
#endif
/*==================TXSTA REG==================*/
/*----------TX9 Bit------------*/
#define _EUSART_9_BIT_TRANSMISSION                           1 /* Selects 9-bit Transmission */ 
#define _EUSART_8_BIT_TRANSMISSION                           0 /* Selects 8-bit Transmission */ 
/*----------TXEN Bit-----------*/
#define _EUSART_TRANSMIT_ENABLE                              1 /* EUSART Transmit Enable*/
#define _EUSART_TRANSMIT_DISABLE                             0 /* EUSART Transmit Disable*/
/*----------TRMT Bit-----------*/
#define _EUSART_TSR_EMPTY                                    1 /* EUSART Transmit Shift Register Empty */
#define _EUSART_TSR_FULL                                     0 /* EUSART Transmit Shift Register Full */
/*==================RCSTA REG==================*/
/*----------SPEN Bit-----------*/
#define _EUSART_SERIAL_PORT_ENABLE                           1 /* EUSART Serial port enable */
#define _EUSART_SERIAL_PORT_DISABLE                          0 /* EUSART Serial port disable */
/*----------RX9 Bit------------*/
#define _EUSART_9_BIT_RECEIVE                                1 /* EUSART Receive 9-bit */
#define _EUSART_8_BIT_RECEIVE                                0 /* EUSART Receive 8-bit */
/*----------FERR Bit-----------*/
#define _EUSART_FRAMING_ERROR_EXIST                          1 /* Framing error (can be cleared by reading RCREG register and receiving next valid byte) */
#define _EUSART_FRAMING_ERROR_DOESNT_EXIST                   0 /* No framing error */
/*----------OERR Bit-----------*/
#define _EUSART_OVERRUN_ERROR_EXIST                          1 /* Overrun error (can be cleared by clearing bit, CREN) */
#define _EUSART_OVERRUN_ERROR_DOESNT_EXIST                   0 /* No overrun error */
/*==================BAUDCON REG================*/
/*----------ABDOVF Bit---------*/
#define _EUSART_BRG_ROLLOVER_OCCUR                           1 /* A BRG rollover has occurred during Auto-Baud Rate Detect mode (must be cleared in software) */
#define _EUSART_BRG_ROLLOVER_DIDNT_OCCUR                     0 /* No BRG rollover has occurred */
/*----------RCIDL Bit----------*/
#define _EUSART_RECEIVE_OPERATION_IDLE                       1 /* Receive operation is Idle */
#define _EUSART_RECEIVE_OPERATION_NOT_IDLE                   0 /* Receive operation is active */
/*----------BRG16 Bit----------*/
#define _EUSART_16_BIT_BAUD_RATE_GENERATOR                   1 /* 16-bit Baud Rate Generator – SPBRGH and SPBRG */
#define _EUSART_8_BIT_BAUD_RATE_GENERATOR                    0 /* 8-bit Baud Rate Generator – SPBRG only (Compatible mode), SPBRGH value ignored */
/*----------------------------Macros Functions Declarations-------------------*/
#if EUSART_ACTIVE_MODE == EUSART_SYNC_MODE                   /* EUSART SYNC MODE ONLY */
/*==================TXSTA REG==================*/
/*----------CSRC Bit-----------*/
/**
 * A macro function for configuring EUSART Sync mode clock source
 */
#define EUSART_SYNC_CLK_SRC_CONFIG(__SRC)                    (TXSTAbits.CSRC = __SRC)
/*==================RCSTA REG==================*/
/*----------SREN Bit-----------*/
/**
 * A macro function for enabling Master Sync mode single receive 
 */
#define EUSART_SYNC_MASTER_SINGLE_RECEIVE_ENABLE_CONFIG()    (RCSTAbits.SREN = _EUSART_SYNC_MASTER_SINGLE_RECEIVE_ENABLE)
/**
 * A macro function for disabling Master Sync mode single receive 
 */
#define EUSART_SYNC_MASTER_SINGLE_RECEIVE_DISABLE_CONFIG()   (RCSTAbits.SREN = _EUSART_SYNC_MASTER_SINGLE_RECEIVE_DISABLE)
/*----------CREN Bit-----------*/
/**
 * A macro function for enabling continues receive in Sync mode
 */
#define EUSART_SYNC_CONTINUES_RECEIVE_ENABLE_CONFIG()        (RCSTA1bits.CREN = _EUSART_SYNC_RECEIVE_ENABLE)
/**
 * A macro function for disabling continues receive in Sync mode
 */
#define EUSART_SYNC_CONTINUES_RECEIVE_DISABLE_CONFIG()       (RCSTA1bits.CREN = _EUSART_SYNC_RECEIVE_DISABLE)
/*==================BAUDCON REG================*/
/*----------RCIDL Bit----------*/
/**
 * A macro function for selecting clock and data polarity idle state for CLK is high level
 */
#define EUSART_SYNC_CLK_IDLE_STATE_HIGH_LEVEL_CONFIG()       (BAUDCONbits.TXCKP = _EUSART_SYNC_CLK_IDLE_STATE_HIGH_LEVEL)
/**
 * A macro function for selecting clock and data polarity idle state for CLK is low level
 */
#define EUSART_SYNC_CLK_IDLE_STATE_LOW_LEVEL_CONFIG()        (BAUDCONbits.TXCKP = _EUSART_SYNC_CLK_IDLE_STATE_LOW_LEVEL)
#endif
#if EUSART_ACTIVE_MODE == EUSART_ASYNC_MODE                /* EUSART ASYNC MODE ONLY */
/*==================TXSTA REG==================*/
/*----------BRGH Bit-----------*/
/**
 * A macro function for selecting the speed of the EUSART ASYNC MODE
 */
#define EUSART_ASYNC_SELECT_SPEED_CONFIG(__SPEED)            (TXSTAbits.BRGH = __SPEED)
/*==================RCSTA REG==================*/
/*----------CREN Bit-----------*/
/**
 * A macro function for enabling continues receive in Async mode
 */
#define EUSART_ASYNC_CONTINUES_RECEIVE_ENABLE_CONFIG()       (RCSTA1bits.CREN = _EUSART_ASYNC_RECEIVE_ENABLE)
/**
 * A macro function for disabling continues receive in Async mode
 */
#define EUSART_ASYNC_CONTINUES_RECEIVE_DISABLE_CONFIG()      (RCSTA1bits.CREN = _EUSART_ASYNC_RECEIVE_DISABLE)
/*----------ADDEN Bit----------*/
/**
 * A macro function for enabling address detection in Async mode
 */
#define EUSART_ASYNC_ADDRESS_DETECTION_ENABLE_CONFIG()       (RCSTA1bits.ADEN = _EUSART_ASYNC_ADDRESS_DETECTION_ENABLE)
/**
 * A macro function for disabling address detection in Async mode
 */
#define EUSART_ASYNC_ADDRESS_DETECTION_DISABLE_CONFIG()      (RCSTA1bits.ADEN = _EUSART_ASYNC_ADDRESS_DETECTION_DISABLE)
/*==================BAUDCON REG================*/
/*----------RXDTP Bit----------*/
/**
 * A macro function for selecting Async mode data polarity to be inverted 
 */
#define EUSART_ASYNC_RECEIVED_DATA_INVERTED_CONFIG()         (BAUDCONbits.RXDTP = _EUSART_ASYNC_DATA_INVERTED)
/**
 * A macro function for selecting Async mode data polarity to be not inverted 
 */
#define EUSART_ASYNC_RECEIVED_DATA_NOT_INVERTED_CONFIG()     (BAUDCONbits.RXDTP = _EUSART_ASYNC_DATA_NOT_INVERTED)
/*----------ABDEN Bit----------*/
/**
 * A macro function for Async mode for enabling baud rate measurement on next character
 */
#define EUSART_ASYNC_ENABLE_BAUD_RATE_MEASUREMENT_CONFIG()   (BAUDCONbits.ABDEN = _EUSART_ASYNC_AUTO_BAUD_MEASUREMENT_ENABLE)
/**
 * A macro function for Async mode for disabling baud rate measurement on next character
 */
#define EUSART_ASYNC_DISABLE_BAUD_RATE_MEASUREMENT_CONFIG()  (BAUDCONbits.ABDEN = _EUSART_ASYNC_AUTO_BAUD_MEASUREMENT_DISABLE)
#endif
/*==================TXSTA REG==================*/
/*----------TX9 Bit------------*/
/**
 * A macro function for configuring the size of EUSART transmission
 */
#define EUSART_TRANSMISSION_SIZE_CONFIG(__SIZE)              (TXSTAbits.TX9 = __SIZE)
/*----------TXEN Bit-----------*/
/**
 * A macro function for enabling EUSART
 */
#define EUSART_ENABLE_CONFIG()                               (TXSTAbits.TXEN = EUSART_TRANSMIT_ENABLE)
/**
 * A macro function for disabling EUSART
 */
#define EUSART_DISABLE_CONFIG()                              (TXSTAbits.TXEN = EUSART_TRANSMIT_DISABLE)
/*----------SYNC Bit-----------*/
/**
 * A macro function for Selecting EUSART mode
 */
#define EUSART_SELECT_MODE_CONFIG(__MODE)                    (TXSTAbits.SYNC = __MODE)
/*----------TRMT Bit-----------*/
/**
 * A macro function for reading the status of the TSR register
 */
#define EUSART_TSR_GET_STATUS_CONFIG(__VAR)                  (__VAR = TXSTAbits.TRMT)
/*----------TX9 Bit------------*/
/**
 * A macro function for Setting the TX9 bit (Can be address/data bit or a parity bit)
 */
#define EUSART_SET_TX9_BIT_CONFIG()                          (TXSTAbits.TX9 = 1)
/**
 * A macro function for Clearing the TX9 bit (Can be address/data bit or a parity bit)
 */
#define EUSART_CLEAR_TX9_BIT_CONFIG()                        (TXSTAbits.TX9 = 0)
/*==================RCSTA REG==================*/
/*----------SPEN Bit-----------*/
/**
 * A macro function for enabling serial port
 */
#define EUSART_SERIAL_PORT_ENABLE_CONFIG()                   (RCSTAbits.SPEN = _EUSART_SERIAL_PORT_ENABLE)
/**
 * A macro function for disabling serial port
 */
#define EUSART_SERIAL_PORT_DISABLE_CONFIG()                  (RCSTAbits.SPEN = _EUSART_SERIAL_PORT_DISABLE)
/*----------RX9 Bit------------*/
/**
 * A macro function for selecting 9 bits for the received data
 */
#define EUSART_RECEIVED_SIZE_9_BIT_CONFIG()                  (RCSTAbits.RX9 = _EUSART_9_BIT_RECEIVE)
/**
 * A macro function for selecting 8 bits for the received data
 */
#define EUSART_RECEIVED_SIZE_8_BIT_CONFIG()                  (RCSTAbits.RX9 = _EUSART_8_BIT_RECEIVE)
/*----------FERR Bit-----------*/
/**
 * A macro function for reading the status of Framing error bit
 */
#define EUSART_READ_FRAMING_ERROR_STATUS_CONFIG(__VAR)       (__VAR = RCSTAbits.FERR)
/*----------OERR Bit-----------*/
/**
 * A macro function for reading the status of Overrun error bit
 */
#define EUSART_READ_OVERRUN_ERROR_STATUS_CONFIG(__VAR)       (__VAR = RCSTAbits.OERR)
/*----------RX9D Bit-----------*/
/**
 * A macro function for Setting the RX9D bit (This can be address/data bit or a parity bit and must be calculated by user firmware.)
 */
#define EUSART_SET_RX9D_BIT_CONFIG()                         (RCSTAbits.RX9D = 1)
/**
 * A macro function for Clearing the RX9D bit (This can be address/data bit or a parity bit and must be calculated by user firmware.)
 */
#define EUSART_CLEAR_RX9D_BIT_CONFIG()                       (RCSTAbits.RX9D = 0)
/*==================BAUDCON REG================*/
/*----------ABDOVF Bit---------*/
/**
 * A macro function for reading Auto-Baud Acquisition Rollover Status bit
 */
#define EUSART_READ_BRG_ROLLOVER_STATUS_CONFIG(__VAR)        (__VAR = BAUDCONbits.ABDOVF)
/**
 * A macro function for clearing Auto-Baud Acquisition Rollover Status bit
 */
#define EUSART_CLEAR_BRG_ROLLOVER_STATUS_CONFIG()           (BAUDCONbits.ABDOVF = _EUSART_BRG_ROLLOVER_DIDNT_OCCUR)
/*----------RCIDL Bit----------*/
/**
 * A macro function for reading Receive Operation Idle Status bit
 */
#define EUSART_READ_RECEIVE_OPERATION_STATUS_CONFIG(__VAR)   (__VAR = BAUDCONbits.RCIDL)
/*----------BRG16 Bit----------*/
/**
 * A macro function for selecting 16 bit baud rate generator
 */
#define EUSART_SELECT_16_BIT_BRG_CONFIG()                    (BAUDCONbits.BRG = _EUSART_16_BIT_BAUD_RATE_GENERATOR)
/**
 * A macro function for selecting 8 bit baud rate generator
 */
#define EUSART_SELECT_8_BIT_BRG_CONFIG()                     (BAUDCONbits.BRG = _EUSART_8_BIT_BAUD_RATE_GENERATOR)
/*----------WUE Bit------------*/
/**
 * A macro function for Async mode for continue sampling RX pin
 */
#define EUSART_ASYNC_CONTINUE_SAMPLE_RX_CONFIG()             (BAUDCONbits.WUE = _EUSART_ASYNC_WAKE_UP_ENABLE)
/**
 * A macro function for Async mode for discontinue sampling RX pin
 */
#define EUSART_ASYNC_DISCONTINUE_SAMPLE_RX_CONFIG()          (BAUDCONbits.WUE = _EUSART_ASYNC_WAKE_UP_DISABLE)
/*----------------------------DataTypes---------------------------------------*/
typedef struct
{
    
} eusart_t;
/*----------------------------Function Prototypes-----------------------------*/

#endif	/* HAL_EUSART_H */

