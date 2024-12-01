/* 
 * File:   hal_eusart.h
 * Author: Mohamed olwi
 *
 * Created on 08 November 2024, 11:34
 */
#include "hal_eusart.h"
/*---------------Static Data types----------------------------------------------*/
/*---TX Interrupt Handler---*/
#if EUSART_TRANSMIT_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static INTERRUPT_HANDLER eusart_tx_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
#endif
#if EUSART_RECEIVE_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
/*---RX Interrupt Handler---*/
static INTERRUPT_HANDLER eusart_rx_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
/*---OERR Interrupt Handler-*/
#if EUSART_OERR_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static INTERRUPT_HANDLER eusart_oerr_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
#endif
/*---FERR Interrupt Handler-*/
#if EUSART_FERR_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static INTERRUPT_HANDLER eusart_ferr_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
#endif
#endif
/*---------------Static Data types End------------------------------------------*/

/*---------------Static Helper functions declerations---------------------------*/
/*---Baudrate Helper function---*/
static void eusart_baudrate_select(const eusart_t *const eusart_obj);
/*---Transmit Helper functions--*/
static Std_ReturnType eusart_tx_init(const eusart_t *const eusart_obj);
static inline Std_ReturnType eusart_tx_interrupt_config(const eusart_t *const eusart_obj);
/*---Receive Helper functions---*/
static Std_ReturnType eusart_rx_init(const eusart_t *const eusart_obj);
static inline Std_ReturnType eusart_rx_interrupt_config(const eusart_t *const eusart_obj);
Std_ReturnType inline set_rx_interrupt_handlers(const eusart_t *const eusart_obj);
/*---------------Static Helper functions declerations End-----------------------*/

/**
 * @brief: Initialize the EUSART module
 * @param eusart_obj the eusart module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType eusart_init(const eusart_t *const eusart_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (eusart_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* EUSART disable Module */
        EUSART_SERIAL_PORT_DISABLE_CONFIG();
#if EUSART_SYNC_MODE == EUSART_ACTIVE_MODE
        /* Enable Sync Mode */
        EUSART_SELECT_MODE_CONFIG(_EUSART_SYNC_MODE);
#endif
#if EUSART_ASYNC_MODE == EUSART_ACTIVE_MODE
        /* Enable Async Mode */
        EUSART_SELECT_MODE_CONFIG(_EUSART_ASYNC_MODE);
#endif
        /* Select Baudrate */
        eusart_baudrate_select(eusart_obj);
        /* Configure RC6 and RC7 to be input */
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        /* Initialize the Transmit mode */
        ret |= eusart_tx_init(eusart_obj);
        /* Initialize the Receive mode */
        /* EUSART enable Module */
        EUSART_SERIAL_PORT_ENABLE_CONFIG();
    }
    return (ret);
}
/**
 * @brief: A helper function to configure the eusart baudrate speed and baudrate resolution
 * @param eusart_obj The eusart module object used 
 */
static void eusart_baudrate_select(const eusart_t *const eusart_obj)
{
    uint16 baudrate_val_temp = 0;
    /* Configure Baudrate speed */
    switch (eusart_obj->eusart_baudrate_config)
    {
#if EUSART_ASYNC_MODE == EUSART_ACTIVE_MODE

        case BAUDRATE_ASYNC_8_BIT_LOW_SPEED:
            /* ASYNC Mode, Low speed and 8 bit resolution */
            EUSART_ASYNC_SELECT_SPEED_CONFIG(_EUSART_ASYNC_LOW_SPEED);
            EUSART_SELECT_8_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 64) - 1);
            break;
        case BAUDRATE_ASYNC_8_BIT_HIGH_SPEED:
            /* ASYNC Mode, High speed and 8 bit resolution */
            EUSART_ASYNC_SELECT_SPEED_CONFIG(_EUSART_ASYNC_HIGH_SPEED);
            EUSART_SELECT_8_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 16) - 1);
            break;
        case BAUDRATE_ASYNC_16_BIT_LOW_SPEED:
            /* ASYNC Mode, Low speed and 16 bit resolution */
            EUSART_ASYNC_SELECT_SPEED_CONFIG(_EUSART_ASYNC_LOW_SPEED);
            EUSART_SELECT_16_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 16) - 1);
            break;
        case BAUDRATE_ASYNC_16_BIT_HIGH_SPEED:
            /* ASYNC Mode, High speed and 16 bit resolution */
            EUSART_ASYNC_SELECT_SPEED_CONFIG(_EUSART_ASYNC_HIGH_SPEED);
            EUSART_SELECT_16_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 4) - 1;
            break;
#endif
#if EUSART_SYNC_MODE == EUSART_ACTIVE_MODE
        case BAUDRATE_SYNC_16_BIT:
            /* SYNC Mode, High speed and 16 bit resolution */
            EUSART_SELECT_16_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 4) - 1);
            break;
        case BAUDRATE_SYNC_8_BIT:
            /* SYNC Mode, High speed and 8 bit resolution */
            EUSART_SELECT_8_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 4) - 1);
            break;
#endif
    }
#if EUSART_ASYNC_MODE == EUSART_ACTIVE_MODE
    /* Select the Speed of the Baudrate in async */
    EUSART_ASYNC_SELECT_SPEED_CONFIG(eusart_obj->eusart_baudrate_config);
#endif
    /* Store the Baudrate in the SPBRGH:SPBRG registers */
    SPBRG = (uint8)((baudrate_val_temp));
    SPBRGH = (uint8)(baudrate_val_temp >> 8);
}
/**
 * @brief: A helper function to configure the eusart transmit mode
 * @param eusart_obj The eusart module object used 
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType eusart_tx_init(const eusart_t *const eusart_obj)
{
    Std_ReturnType ret = E_OK;
    
    /* Enable transmit mode */
    EUSART_TRANSMIT_ENABLE_CONFIG();
#if EUSART_SYNC_MODE == EUSART_ACTIVE_MODE
    /* Configure the sync mode clock source (master or slave mode) */
    EUSART_SYNC_CLK_SRC_CONFIG(eusart_obj->eusart_tx_config.sync_clk_src);
#endif
    /* Configure the interrupt and its priority if enabled */
#if EUSART_TRANSMIT_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    ret = eusart_tx_interrupt_config(eusart_obj);
#endif
    /* Configure the TX9 bit for enabling/disabling ninth bit*/
    if (_EUSART_9_BIT_TRANSMISSION == eusart_obj->eusart_tx_config.eusart_9_bit_transmit_enable)
    {
        EUSART_TRANSMISSION_9_BIT_CONFIG();
    }
    else
    {
        EUSART_TRANSMISSION_8_BIT_CONFIG();
    }
    return (ret);
}
#if EUSART_TRANSMIT_INTERRUPT_FEATURE == INTERRUPT_ENABLE
/**
 * @brief A helper function to configure the interrupt for transmit mode
 * @param eusart_obj the eusart module object
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType eusart_tx_interrupt_config(const eusart_t *const eusart_obj)
{
    Std_ReturnType ret = E_OK;
    
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* Enable priority levels */
    INTERRUPT_PRIORITY_levels_ENABLE();
    INTERRUPT_Global_interrupt_LOW_ENABLE();
    INTERRUPT_Global_interrupt_HIGH_ENABLE();
    /* Set the interrupt priority */
    switch (eusart_obj->eusart_tx_config.eusart_TX_interrupt_priority)
    {
        case INTERRUPT_HIGH_PRIORITY:
            /* Transmit mode high priority */
            EUSART_TRANSMIT_HIGH_PRIORITY();
            break;
        case INTERRUPT_LOW_PRIORITY:
            /* Transmit mode low priority */
            EUSART_TRANSMIT_LOW_PRIORITY();
            break; 
        default:
            ret = E_NOT_OK;
            break;
    }
#else
    /* If the interrupt priority is disabled then enable the peripheral interrupt
    and global interrupts */
        INTERRUPT_Peripheral_interrupt_ENABLE();
        INTERRUPT_Global_interrupt_ENABLE();
#endif
    /* Enable the transmit mode interrupt */
    EUSART_TRANSMIT_INTERRUPT_ENABLE();
    /* Set the interrupt handler of the EUSART Transmit mode */
    if (eusart_obj->eusart_tx_config.eusart_TX_interrupt)
    {
        eusart_tx_interrupt_handler = eusart_obj->eusart_tx_config.eusart_TX_interrupt;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return (ret);
}
/**
 * @brief the interrupt service routine of EUSART Transmit mode
 */
void EUSART_TX_ISR(void)
{
    /* The TXIF flag cant be cleared by software*/
    EUSART_TRANSMIT_INTERRUPT_DISABLE();
    if (NULL != eusart_tx_interrupt_handler)
    {
        eusart_tx_interrupt_handler();
    }
}
#endif
/**
 * @brief: A helper function to configure the eusart receive mode
 * @param eusart_obj The eusart module object used 
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType eusart_rx_init(const eusart_t *const eusart_obj)
{
    Std_ReturnType ret = E_OK;
    
#if EUSART_SYNC_MODE == EUSART_ACTIVE_MODE
    /* EUSART Sync mode Single reception config (only if master mode is on) */
    if (_EUSART_SYNC_MASTER_MODE == eusart_obj->eusart_tx_config.sync_clk_src 
            && _EUSART_SYNC_MASTER_SINGLE_RECEIVE_ENABLE == eusart_obj->eusart_rx_config.sync_single_reception_mode)
    {
        EUSART_SYNC_MASTER_SINGLE_RECEIVE_ENABLE_CONFIG();
    }
    else
    {
        EUSART_SYNC_MASTER_SINGLE_RECEIVE_DISABLE_CONFIG();
    }
    /* EUSART Sync mode continuous reception config (will override single reception config) */
    if (_EUSART_SYNC_CONTINUOUS_RECEIVE_ENABLE == eusart_obj->eusart_rx_config.sync_cont_reception_mode)
    {
        EUSART_SYNC_CONTINUOUS_RECEIVE_ENABLE_CONFIG();
    }
    else
    {
        EUSART_SYNC_CONTINUOUS_RECEIVE_DISABLE_CONFIG();
    }
#else
        /* Enable the receive mode in async mode*/
    EUSART_ASYNC_CONTINUOUS_RECEIVE_ENABLE_CONFIG();
#endif
    /* Configure the interrupt and its priority if enabled */
#if EUSART_RECEIVE_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    ret = eusart_rx_interrupt_config(eusart_obj);
#endif  
    /* Configure the RX9 bit for enabling/disabling ninth bit*/
    if (_EUSART_9_BIT_RECEIVE == eusart_obj->eusart_rx_config.eusart_9_bit_receive_enable)
    {
        EUSART_RECEIVED_SIZE_9_BIT_CONFIG();
    }
    else
    {
        EUSART_RECEIVED_SIZE_8_BIT_CONFIG();
    }
    return (ret);
}
#if EUSART_RECEIVE_INTERRUPT_FEATURE == INTERRUPT_ENABLE
/**
 * @brief A helper function to configure the interrupt for receive mode
 * @param eusart_obj The eusart module object used 
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType eusart_rx_interrupt_config(const eusart_t *const eusart_obj)
{
    Std_ReturnType ret = E_OK;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* Enable priority levels */
    INTERRUPT_PRIORITY_levels_ENABLE();
    INTERRUPT_Global_interrupt_LOW_ENABLE();
    INTERRUPT_Global_interrupt_HIGH_ENABLE();
    /* Set the interrupt priority */
    switch (eusart_obj->eusart_rx_config.eusart_RX_interrupt_priority)
    {
        case INTERRUPT_HIGH_PRIORITY:
            /* Receive mode high priority */
            EUSART_RECEIVE_HIGH_PRIORITY();
            break;
        case INTERRUPT_LOW_PRIORITY:
            /* Receive mode low priority */
            EUSART_RECEIVE_LOW_PRIORITY();
            break; 
        default:
            ret = E_NOT_OK;
    }
#else
    /* If the interrupt priority is disabled then enable the peripheral interrupt
    and global interrupts */
        INTERRUPT_Peripheral_interrupt_ENABLE();
        INTERRUPT_Global_interrupt_ENABLE();
#endif
    /* Enable the receive mode interrupt */
    EUSART_RECEIVE_INTERRUPT_ENABLE();
    /* Set the interrupt handler of the EUSART Receive mode */
    ret = set_rx_interrupt_handlers(eusart_obj);
    return (ret);
}
/**
 * @brief Set the interrupt handlers of the RX mode
 * @param eusart_obj the eusart module object used
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline set_rx_interrupt_handlers(const eusart_t *const eusart_obj)
{
    Std_ReturnType ret = E_OK;
    
    /* RX interrupt handler */
    if (eusart_obj->eusart_rx_config.eusart_RX_interrupt)
    {
        eusart_rx_interrupt_handler = eusart_obj->eusart_rx_config.eusart_RX_interrupt;
    }
    else
    {
        ret = E_NOT_OK;
    }  
    /* Framing error interrupt handler */
    if (eusart_obj->eusart_errors_interrupts.eusart_frame_error_interrupt)
    {
      eusart_ferr_interrupt_handler = eusart_obj->eusart_errors_interrupts.eusart_frame_error_interrupt;
    }
    /* Overrun error interrupt handler */
    if (eusart_obj->eusart_errors_interrupts.eusart_overrun_error_interrupt)
    {
      eusart_oerr_interrupt_handler = eusart_obj->eusart_errors_interrupts.eusart_overrun_error_interrupt;
    }
    return (ret);
}
/**
 * @brief the interrupt service routine of EUSART Receive mode
 */
void EUSART_RX_ISR(void)
{
    /* RCIF is Cleared when RCREG register is read from */
    if (eusart_rx_interrupt_handler)
    {
        eusart_rx_interrupt_handler();
    }
    /* Framing error interrupt */
    if (eusart_ferr_interrupt_handler)
    {
        /* The interrupt handler must read RCREG to clear FERR flag */
        eusart_ferr_interrupt_handler();
    }
    /* Overrun error interrupt */
    if (eusart_oerr_interrupt_handler)
    {
        /* Reset the receive logic to clear the flag */
#if EUSART_SYNC_MODE == EUSART_ACTIVE_MODE
        EUSART_SYNC_CONTINUOUS_RECEIVE_DISABLE_CONFIG();
        EUSART_SYNC_CONTINUOUS_RECEIVE_ENABLE_CONFIG();
#else
        EUSART_ASYNC_CONTINUOUS_RECEIVE_DISABLE_CONFIG();
        EUSART_ASYNC_CONTINUOUS_RECEIVE_ENABLE_CONFIG();
#endif
        eusart_oerr_interrupt_handler();
    }
}
#endif  

/**
 * @brief: Write data to transmit it using eusart
 * @note: Will block CPU instruction until TSR is empty
 * @param data the 8-bit data or 9-bit data to transmit
 */
void inline eusart_write_byte(const uint16 data)
{
    /* Block CPU instructions until TSR is empty */
    while (_EUSART_TSR_FULL == TXSTAbits.TRMT);
    /* Enable TX interrupt if interrupt feature is enabled */
#if EUSART_TRANSMIT_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    EUSART_TRANSMIT_INTERRUPT_ENABLE();
#endif
    /* Store the value to write */
    TXREG = (uint8)(data);
    /* Store the 9th bit if enabled */
    if (_EUSART_9_BIT_TRANSMISSION == TXSTAbits.TX9)
    {
        if (1 == READ_BIT(data, 9))
            EUSART_SET_TX9D_BIT_CONFIG();
        else
            EUSART_CLEAR_TX9D_BIT_CONFIG();
    }
}

#if EUSART_RECEIVE_INTERRUPT_FEATURE == INTERRUPT_FEATURE_DISABLE
/**
 * @brief: Read data from eusart
 * @param The address to store the read 8-bit data or 9-bit data
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline eusart_read_byte(uint16 *const data)
{
    Std_ReturnType ret = E_OK;
    if (NULL != data)
    {
        /* Check of data is received */
        if (1 == PIR1bits.RC1IF)
        {
            /* Data is received */
            /* READ the 9th bit before reading RCREG to avoid overwriting */
             if (_EUSART_9_BIT_RECEIVE == RCSTAbits.RX9)
             {
                 *data = (uint16)(RCSTAbits.RX9D << 8);
             }
            /* Set the data to RCREG */
            *data= RCREG;
        }
        else
        {
            /* No data is received */
            ret = E_NOT_OK;
        }
    }

    return (ret);
}   
/**
 * @brief: Read data from eusart
 * @note: Will block CPU instruction until TXREG is empty
 * @param The address to store the read 8-bit data or 9-bit data
 */
void inline eusart_read_byte_blocking(uint16 *const data)
{
    /* Wait till data is received */
    while(!PIR1bits.RC1IF)
        ;
    /* Data is received */
    /* READ the 9th bit before reading RCREG to avoid overwriting */
     if (_EUSART_9_BIT_RECEIVE == RCSTAbits.RX9)
     {
         *data = (uint16)(RCSTAbits.RX9D << 8);
     }
    /* Set the data to RCREG */
    *data= RCREG;
}
#else
/**
 * @brief: Read data from eusart
 * @param The address to store the read 8-bit data or 9-bit data
 * @note If ferr happened or a receive interrupt(RCIF), must use this SW interface to clear the flags
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType inline eusart_read_byte(uint16 *const data)
{
    Std_ReturnType ret = E_OK;
    if (NULL != data)
    {
        /* Check of data is received */
        if (1 == PIR1bits.RC1IF)
        {
            /* Data is received */
            /* READ the 9th bit before reading RCREG to avoid overwriting */
             if (_EUSART_9_BIT_RECEIVE == RCSTAbits.RX9)
             {
                 *data = (uint16)(RCSTAbits.RX9D << 8);
             }
            /* Set the data to RCREG */
            *data= RCREG;
        }
        else
        {
            /* No data is received */
            ret = E_NOT_OK;
        }
    }
    return (ret);
}  
#endif

