/* 
 * File:   hal_eusart.h
 * Author: Mohamed olwi
 *
 * Created on 08 November 2024, 11:34
 */
#include "hal_eusart.h"
/*---------------Static Data types----------------------------------------------*/
#if EUSART_TRANSMIT_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static INTERRUPT_HANDLER eusart_tx_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
#endif
#if EUSART_RECEIVE_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static INTERRUPT_HANDLER eusart_rx_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
#endif
/*---------------Static Data types End------------------------------------------*/

/*---------------Static Helper functions declerations---------------------------*/
static void eusart_baudrate_select(const eusart_t *const eusart_obj);
static Std_ReturnType eusart_async_tx_init(const eusart_t *const eusart_obj);
static inline Std_ReturnType eusart_async_tx_interrupt_config(const eusart_t *const eusart_obj);
static Std_ReturnType eusart_async_rx_init(const eusart_t *const eusart_obj);
static inline Std_ReturnType eusart_async_rx_interrupt_config(const eusart_t *const eusart_obj);
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
        /* Select Baudrate */
        eusart_baudrate_select(eusart_obj);
        /* Configure RC6 and RC7 to be input */
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        /* Initialize the Transmit mode */
        ret |= eusart_async_tx_init(eusart_obj);
        /* Initialize the Receive mode */
        ret |= eusart_async_rx_init(eusart_obj);
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
        case BAUDRATE_ASYNC_8_BIT_LOW_SPEED:
            /* ASYNC Mode, Low speed and 8 bit resolution */
            EUSART_SELECT_MODE_CONFIG(_EUSART_ASYNC_MODE);
            EUSART_ASYNC_SELECT_SPEED_CONFIG(_EUSART_ASYNC_LOW_SPEED);
            EUSART_SELECT_8_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 64) - 1);
            break;
        case BAUDRATE_ASYNC_8_BIT_HIGH_SPEED:
            /* ASYNC Mode, High speed and 8 bit resolution */
            EUSART_SELECT_MODE_CONFIG(_EUSART_ASYNC_MODE);
            EUSART_ASYNC_SELECT_SPEED_CONFIG(_EUSART_ASYNC_HIGH_SPEED);
            EUSART_SELECT_8_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 16) - 1);
            break;
        case BAUDRATE_ASYNC_16_BIT_LOW_SPEED:
            /* ASYNC Mode, Low speed and 16 bit resolution */
            EUSART_SELECT_MODE_CONFIG(_EUSART_ASYNC_MODE);
            EUSART_ASYNC_SELECT_SPEED_CONFIG(_EUSART_ASYNC_LOW_SPEED);
            EUSART_SELECT_16_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 16) - 1);
            break;
        case BAUDRATE_ASYNC_16_BIT_HIGH_SPEED:
            /* ASYNC Mode, High speed and 16 bit resolution */
            EUSART_SELECT_MODE_CONFIG(_EUSART_ASYNC_MODE);
            EUSART_ASYNC_SELECT_SPEED_CONFIG(_EUSART_ASYNC_HIGH_SPEED);
            EUSART_SELECT_16_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 4) - 1;
            break;
#if EUSART_SYNC_MODE == EUSART_ACTIVE_MODE
        case BAUDRATE_SYNC_16_BIT:
            /* SYNC Mode, High speed and 16 bit resolution */
            EUSART_SELECT_MODE_CONFIG(_EUSART_);
            EUSART_SELECT_16_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 4) - 1);
            break;
        case BAUDRATE_SYNC_8_BIT:
            /* SYNC Mode, High speed and 8 bit resolution */
            EUSART_SELECT_MODE_CONFIG(_EUSART_SYNC_MODE);
            EUSART_SELECT_8_BIT_BRG_CONFIG();
            baudrate_val_temp = (uint16)(((_XTAL_FREQ / eusart_obj->eusart_baudrate) / 4) - 1);
            break;
#endif
    }
    /* Select the Speed of the Baudrate */
    EUSART_ASYNC_SELECT_SPEED_CONFIG(eusart_obj->eusart_baudrate_config);
    /* Store the Baudrate in the SPBRGH:SPBRG registers */
    SPBRG = (uint8)((baudrate_val_temp));
    SPBRGH = (uint8)(baudrate_val_temp >> 8);
}
/**
 * @brief: A helper function to configure the eusart transmit mode
 * @param eusart_obj The eusart module object used 
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType eusart_async_tx_init(const eusart_t *const eusart_obj)
{
    Std_ReturnType ret = E_OK;
    
    /* Enable transmit mode */
    EUSART_TRANSMIT_ENABLE_CONFIG();
    /* Configure the interrupt and its priority if enabled */
#if EUSART_TRANSMIT_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    ret = eusart_async_tx_interrupt_config(eusart_obj);
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
static inline Std_ReturnType eusart_async_tx_interrupt_config(const eusart_t *const eusart_obj)
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
static Std_ReturnType eusart_async_rx_init(const eusart_t *const eusart_obj)
{
    Std_ReturnType ret = E_OK;
    
    /* Enable the receive mode */
    EUSART_ASYNC_CONTINUES_RECEIVE_ENABLE_CONFIG();
    /* Configure the interrupt and its priority if enabled */
#if EUSART_RECEIVE_INTERRUPT_FEATURE == INTERRUPT_ENABLE
    ret = eusart_async_rx_interrupt_config(eusart_obj);
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
 * @param eusart_obj the eusart module object
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType eusart_async_rx_interrupt_config(const eusart_t *const eusart_obj)
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
    if (eusart_obj->eusart_rx_config.eusart_RX_interrupt)
    {
        eusart_rx_interrupt_handler = eusart_obj->eusart_rx_config.eusart_RX_interrupt;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return (ret);
}
/**
 * @brief the interrupt service routine of EUSART Receive mode
 */
void EUSART_RX_ISR(void)
{
    EUSART_RECEIVE_INTERRUPT_FLAG_BIT_CLEAR();
    if (NULL != eusart_rx_interrupt_handler)
    {
        eusart_rx_interrupt_handler();
    }
}
#endif  

/**
 * @brief: Write data to transmit it using eusart
 * @note: Will block CPU instruction until TXREG is empty
 * @param data the 8-bit data or 9-bit data to transmit
 */
void inline eusart_write_byte(uint16 data)
{
    /* Block CPU instructions until TXREG is empty */
    while (_EUSART_TSR_FULL == TXSTAbits.TRMT);
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

