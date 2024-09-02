/* 
 * File:   hal_adc.
 * Author: Mohamed olwi
 *
 * Created on 29 August 2024, 23:42
 */
#include "hal_adc.h"
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static INTERRUPT_HANDLER adc_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
#endif
/*---------------Static Helper functions declerations---------------------------*/
static inline Std_ReturnType adc_analog_input_channel_config(const adc_channel_select_t channel);
static inline Std_ReturnType adc_configure_result_format(const adc_config_t *adc_obj);
static inline Std_ReturnType adc_configure_vref(const adc_config_t *adc_obj);
static inline Std_ReturnType adc_port_control_config(const adc_config_t *adc_obj);
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType adc_set_interrupt_handler(INTERRUPT_HANDLER Interrupt_Handler);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType adc_set_interrupt_priority(const adc_config_t *adc_obj);
#endif
#endif
/*---------------Static Helper functions declerations End-----------------------*/


/**
 * @brief: Initialize the adc peripheral
 * @param adc_obj the adc object to initialize
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_init(const adc_config_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == adc_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable the ADC conversion  */
        DISABLE_ADC_CONVERSION();
        /* Configure the Conversion Clock */
        ADC_SET_CONVERSION_CLOCK(adc_obj->conversion_clock);
        /* Configure the Acquisition time */
        ADC_SET_ACQUISITION_TIME(adc_obj->aquisition_time);
        /* Configure the default channel */
        ret |= adc_select_channel(adc_obj, adc_obj->adc_analog_channel);
        /* Configure the A/D port configuration */
        ret |= adc_port_control_config(adc_obj);
        /* Configure the interrupt */
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_FLAG_BIT_CLEAR();
        ret |= adc_set_interrupt_handler(adc_obj->adc_interrupt_handler);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret |= adc_set_interrupt_priority(adc_obj);
#endif
#endif
        /* Configure the result format */
        ret |= adc_configure_result_format(adc_obj);
        /* Configure the voltage reference */
        ret |= adc_configure_vref(adc_obj);
        /* Enable the adc */
        ENABLE_ADC_CONVERSION();
    }
    return (ret);
}
/**
 * @brief: Deinitialize the adc peripheral
 * @param adc_obj the adc object to deinitialize
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_deinit(const adc_config_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == adc_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable interrupt */
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
#endif
        /* Disable ADC */
        DISABLE_ADC_CONVERSION();
    }
    return (ret);
}
/**
 * @brief: Select the adc input channel
 * @param adc_obj the adc config used
 * @param channel the channel selected
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_select_channel(const adc_config_t *adc_obj, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == adc_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Configure the default channel */
        ret |= adc_analog_input_channel_config(channel);
        ADC_SET_ANALOG_CHANNEL(channel);
    }
    return (ret);
}
/**
 * @brief: Start the adc conversion
 * @param adc_obj the adc config used
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_start_conversion(const adc_config_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == adc_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        START_ADC_CONV();
    }
    return (ret);
}
/**
 * @brief: Read the status of the adc conversion
 * @param adc_obj the adc config used
 * @param adc_status the address to store the status of the adc conversion
 *                   1 - Conversion is in progress
 *                   0 - ADC is in idle state
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_read_conversion_status(const adc_config_t *adc_obj, adc_conversion_status *adc_status)
{
    Std_ReturnType ret = E_OK;
    
    if ((NULL == adc_obj) || (NULL == adc_status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_GET_CONV_STATUS(adc_status);
    }
    return (ret);
}
/**
 * @brief: Read the result of the adc conversion
 * @param adc_obj the adc config used
 * @param adc_result the address to store the result of the adc conversion
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_read_result(const adc_config_t *adc_obj, adc_conversion_result *adc_result)
{
    Std_ReturnType ret = E_OK;
    
    if ((NULL == adc_obj) || (NULL == adc_result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (ADC_RES_LEFT_JUSTIFY == adc_obj->result_format)
        {
            *adc_result = (adc_conversion_result)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else if (ADC_RES_RIGHT_JUSTIFY == adc_obj->result_format)
        {
            *adc_result = (adc_conversion_result)((ADRESH << 8) + ADRESL);
        }
        else
        {
            ret = E_NOT_OK;
        }
    }
    return (ret);
}
/**
 * @brief: Get the conversion done by the adc on from a specific input channel and wait until the conversion is done
 *         and read the result to the specified memory address
 * @param adc_obj the adc config used
 * @param channel the input channel to read the input from
 * @param result the adddress to store the result of the adc conversion
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_get_conversion(const adc_config_t *adc_obj, adc_channel_select_t channel, adc_conversion_result * result)
{
    Std_ReturnType ret = E_OK;
    adc_conversion_status l_result = ADC_IDLE;

    if ((NULL == adc_obj) || (NULL == result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Select the input channel */
        ret |= adc_select_channel(adc_obj, channel);
        /* Start the adc conversion */
        ret |= adc_start_conversion(adc_obj);
        /* Read the conversion status */
        ret |= adc_read_conversion_status(adc_obj, &l_result);
        /* Wait untill the conversion is done */
        while (ADC_CONV_STATUS() == ADC_NOT_IDLE);
        /* Read the result of the adc conversion*/
        ret |= adc_read_result(adc_obj, result);
    }
    return (ret);
}
/*---------------Static Helper functions Definition-----------------------------*/

/**
 * @brief configure the analog input channel pin to be an input
 * @param channel the channel to configure
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType adc_analog_input_channel_config(const adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    switch (channel)
    {
        case ADC_CHANNEL_AN0:
            SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1:
            SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2:
            SET_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3:
            SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4:
            SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5:
            SET_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6:
            SET_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7:
            SET_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8:
            SET_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9:
            SET_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10:
            SET_BIT(TRISB, _TRISB_RB1_POSN);
            break;   
        case ADC_CHANNEL_AN11:
            SET_BIT(TRISB, _TRISB_RB4_POSN);
            break;        
        case ADC_CHANNEL_AN12:
            SET_BIT(TRISB, _TRISB_RB0_POSN);
            break;   
        default:
            ret = E_NOT_OK;
            break;
    }
    return (ret);
}
/**
 * @brief configure the result format to be right justified or left justified
 * @param adc_obj the adc config used
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType adc_configure_result_format(const adc_config_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (ADC_RES_LEFT_JUSTIFY == adc_obj->result_format)
    {
        ADC_SET_RESULT_LEFT_JUSTIFY();
    }
    else if (ADC_RES_RIGHT_JUSTIFY == adc_obj->result_format)
    {
        ADC_SET_RESULT_RIGHT_JUSTIFY();
    }
    else
    {
        ret = E_NOT_OK;
    }
    return (ret);
}
/**
 * @brief configure the vref to be internal or external
 * @param adc_obj the adc config used
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType adc_configure_vref(const adc_config_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (ADC_VREF_INTENAL == adc_obj->voltage_ref)
    {
        ADC_SET_VREF_INTERNAL();
    }
    else if (ADC_VREF_EXTERNAL == adc_obj->voltage_ref)
    {
        ADC_SET_VREF_EXTERNAL();
    }
    else
    {
        ret = E_NOT_OK;
    }
    return (ret);
}
/**
 * @brief: A helper function to configure the adc port control bits
 * @param adc_obj the adc config used
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType adc_port_control_config(const adc_config_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    
    switch(adc_obj->adc_port_config)
    {
        case ADC_ALL_DIGITAL_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_ALL_DIGITAL_FUNCTIONALITY);
            break;
        case ADC_AN0_ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0_ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN1__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN1__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN2__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN2__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN3__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN3__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN4__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN4__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN5__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN5__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN6__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN6__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN7__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN7__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN8__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN8__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN9__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN9__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN10__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN10__ANALOG_FUNCTIONALITY);
            break;
        case ADC_AN0__AN11__ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN0__AN11__ANALOG_FUNCTIONALITY);
            break;
        case ADC_ALL_ANALOG_FUNCTIONALITY:
            ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_ALL_ANALOG_FUNCTIONALITY);
            break;
        default:
            ret = E_NOT_OK;
            break;
    }
    
    return (ret);
}
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief: A helper function to set the interrupt handler of the adc module conversion interrupt
 * @param Interrupt_Handler the interrupt handler to call when an interrupt is raised
 * @return E_OK if success otherwise E_NOT_OK 
 */
static Std_ReturnType adc_set_interrupt_handler(INTERRUPT_HANDLER Interrupt_Handler)
{
    Std_ReturnType ret = E_OK;

    if (NULL == Interrupt_Handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        adc_interrupt_handler = Interrupt_Handler;
    }
    return (ret);
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief: A helper function to set the priority of the adc module conversion interrupt
 * @param adc_obj the adc config used
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType adc_set_interrupt_priority(const adc_config_t *adc_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (INTERRUPT_HIGH_PRIORITY == adc_obj->priortiy)
    {
        ADC_HIGH_PRIORITY();
    }
    else if (INTERRUPT_LOW_PRIORITY == adc_obj->priortiy)
    {
        ADC_LOW_PRIORITY();
    }
    else
    {
        ret = E_NOT_OK;
    }
    return (ret);
}
#endif
#endif
