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
/*----------------------------Macros Declarations-----------------------------*/
/*==================TXSTA REG==================*/
/*----------CSRC Bit----------*/
/*===SYNC===*/
#define _EUSART_SYNC_MASTER_MODE                             1 /* Synchronous Master Mode */
#define _EUSART_SYNC_SLAVE_MODE                              0 /* Synchronous Slave Mode */
/*----------TX9 Bit------------*/
#define _EUSART_9_BIT_TRANSMISSION                           1 /* Selects 9-bit Transmission */ 
#define _EUSART_8_BIT_TRANSMISSION                           0 /* Selects 8-bit Transmission */ 
/*----------TXEN Bit-----------*/
#define _EUSART_TRANSMIT_ENABLE                              1 /* EUSART Transmit Enable*/
#define _EUSART_TRANSMIT_DISABLE                             0 /* EUSART Transmit Disable*/
/*----------SYNC Bit-----------*/
/*===SYNC===*/
#define _EUSART_SYNC_MODE                                    1 /* EUSART Sync Mode */
/*===ASYNC===*/
#define _EUSART_ASYNC_MODE                                   0 /* EUSART ASync Mode */
/*----------BRGH Bit-----------*/
/*===ASYNC===*/
#define _EUSART_ASYNC_HIGH_SPEED                             1 /* EUSART Async mode high speed*/
#define _EUSART_ASYNC_LOW_SPEED                              0 /* EUSART Async mode low speed*/
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
/*----------SREN Bit-----------*/
/*===SYNC===*/
#define _EUSART_SYNC_MASTER_SINGLE_RECEIVE_ENABLE            1 /* EUSART Sync mode single receive enable */
#define _EUSART_SYNC_MASTER_SINGLE_RECEIVE_DISABLE           0 /* EUSART Sync mode single receive disable */
/*----------CREN Bit-----------*/
/*===SYNC===*/
#define _EUSART_SYNC_CONTINUES_RECEIVE_ENABLE                1 /* EUSART Sync Enables continuous receive until enable bit */
#define _EUSART_SYNC_CONTINUES_RECEIVE_DISABLE               0 /* EUSART Sync Disables continuous receive */
/*===ASYNC===*/
#define _EUSART_ASYNC_RECEIVE_ENABLE                         1 /* EUSART ASync Enables receiver */
#define _EUSART_ASYNC_RECEIVE_DISABLE                        0 /* EUSART ASync Disables receiver */
/*----------ADEN Bit-----------*/
/*===ASYNC===*/
#define _EUSART_ASYNC_ADDRESS_DETECTION_ENABLE               1 /* Enables address detection, enables interrupt and loads the receive buffer when RSR<8> is set */
#define _EUSART_ASYNC_ADDRESS_DETECTION_DISABLE              0 /* Disables address detection, all bytes are received and ninth bit can be used as parity bit */
/*----------FERR Bit-----------*/
#define _EUSART_FRAMING_ERROR_EXIST                          1 /* Framing error (can be cleared by reading RCREG register and receiving next valid byte) */
#define _EUSART_FRAMING_ERROR_DOESNT_EXIST                   0 /* No framing error */
/*----------OERR Bit-----------*/
#define _EUSART_OVERRUN_ERROR_EXIST                          1 /* Overrun error (can be cleared by clearing bit, CREN) */
#define _EUSART_OVERRUN_ERROR_DOESNT_EXIST                   0 /* No overrun error */
/*==================BAUDCON REG================*/
/*----------ADOVF Bit----------*/

/*----------------------------Macros Functions Declarations-------------------*/
/*==================TXSTA REG==================*/
/*----------CSRC Bit-----------*/
/*===SYNC===*/
/**
 * A macro function for configuring EUSART Sync mode clock source
 */
#define EUSART_SYNC_CLK_SRC_CONFIG(__SRC)                    (TXSTAbits.CSRC = __SRC)
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
/*----------BRGH Bit-----------*/
/*===ASYNC===*/
/**
 * A macro function for selecting the speed of the EUSART ASYNC MODE
 */
#define EUSART_ASYNC_SELECT_SPEED_CONFIG(__SPEED)            (TXSTAbits.BRGH = __SPEED)
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
/*----------SREN Bit-----------*/
/*===SYNC===*/
/**
 * A macro function for enabling Master Sync mode single receive 
 */
#define EUSART_SYNC_MASTER_SINGLE_RECEIVE_ENABLE_CONFIG()    (RCSTAbits.SREN = _EUSART_SYNC_MASTER_SINGLE_RECEIVE_ENABLE)
/**
 * A macro function for disabling Master Sync mode single receive 
 */
#define EUSART_SYNC_MASTER_SINGLE_RECEIVE_DISABLE_CONFIG()   (RCSTAbits.SREN = _EUSART_SYNC_MASTER_SINGLE_RECEIVE_DISABLE)
/*----------CREN Bit-----------*/
/*===ASYNC===*/
/**
 * A macro function for enabling continues receive in Async mode
 */
#define EUSART_ASYNC_CONTINUES_RECEIVE_ENABLE_CONFIG()       (RCSTA1bits.CREN = _EUSART_ASYNC_RECEIVE_ENABLE)
/**
 * A macro function for disabling continues receive in Async mode
 */
#define EUSART_ASYNC_CONTINUES_RECEIVE_ENABLE_CONFIG()       (RCSTA1bits.CREN = _EUSART_ASYNC_RECEIVE_DISABLE)
/*===SYNC===*/
/**
 * A macro function for enabling continues receive in Sync mode
 */
#define EUSART_SYNC_CONTINUES_RECEIVE_ENABLE_CONFIG()        (RCSTA1bits.CREN = _EUSART_SYNC_RECEIVE_ENABLE)
/**
 * A macro function for disabling continues receive in Sync mode
 */
#define EUSART_SYNC_CONTINUES_RECEIVE_ENABLE_CONFIG()        (RCSTA1bits.CREN = _EUSART_SYNC_RECEIVE_DISABLE)
/*----------ADDEN Bit----------*/
/*===ASYNC===*/
/**
 * A macro function for enabling address detection in Async mode
 */
#define EUSART_ASYNC_ADDRESS_DETECTION_ENABLE_CONFIG()       (RCSTA1bits.ADEN = _EUSART_ASYNC_ADDRESS_DETECTION_ENABLE)
/**
 * A macro function for disabling address detection in Async mode
 */
#define EUSART_ASYNC_ADDRESS_DETECTION_DISABLE_CONFIG()      (RCSTA1bits.ADEN = _EUSART_ASYNC_ADDRESS_DETECTION_DISABLE)
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
/*----------ADOVF Bit----------*/
/*----------------------------Function Prototypes-----------------------------*/

#endif	/* HAL_EUSART_H */

