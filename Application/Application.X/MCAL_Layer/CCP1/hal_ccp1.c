/* 
 * File:   hal_ccp1.c
 * Author: Mohamed olwi
 *
 * Created on 16 October 2024, 22:03
 */
#include "hal_ccp1.h"
#if CCP1_MODULE_ENABLE == MCAL_ENABLED
/*---------------Static Data types----------------------------------------------*/
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static INTERRUPT_HANDLER ccp1_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
#endif
static pin_config_t ccp1_pin = {.port = PORTC_INDEX, .pin = GPIO_PIN1, .logic = GPIO_LOW};
/*---------------Static Data types End------------------------------------------*/

/*---------------Static Helper functions declerations---------------------------*/
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType ccp1_set_interrupt_handler(INTERRUPT_HANDLER Interrupt_Handler);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void ccp1_set_interrupt_priority(const cpp1_t *ccp1_obj);
#endif
#endif
static inline Std_ReturnType ccp1_select_mode(const cpp1_t *ccp1_obj);
/*---------------Static Helper functions declerations End-----------------------*/
/**
 * @brief: Initialize the CCP1 module
 * @param ccp1_obj the CCP1 module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_init(const cpp1_t *ccp1_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == ccp1_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable CCP1 */
        CCP1_SET_MODULE_MODE(CCP1_MODULE_DISABLE);
        /* Enable CCP1 interrupt if interrupt is enable */
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        ret |= ccp1_set_interrupt_handler(ccp1_obj->ccp1_interrupt_handler);
        /* Set the priority of the CCP1 if the priority feature is enable*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ccp1_set_interrupt_priority(ccp1_obj);
#endif  
#endif
        /* Select the mode variant and configure ccp1 pin */
        ret |= ccp1_select_mode(ccp1_obj);
    }
    return (ret);
}
/**
 * @brief: Deinitialize the CCP1 module
 * @param ccp1_obj the CCP1 module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_deinit(const cpp1_t *ccp1_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == ccp1_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        CCP1_SET_MODULE_MODE(CCP1_MODULE_DISABLE);
        /* Disable CCP1 interrupt if interrupt is enable */
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_DISABLE();
#endif 
    }
    return (ret);
}
#if (CCP1_SELECTED_MODE_CFG == CCP1_CAPTURE_MODE_CFG_SELECT)
/**
 * @brief: See the status of the capture mode operation
 * @param _capture_status the address to store the status of the capture mode
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_capture_mode_status(uint8 *_capture_status)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == _capture_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return (ret);
}
/**
 * @brief: Read the value of the capture mode operation
 * @param _capture_value the address to store the value read from the capture mode operation
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_capture_mode_read_value(uint16 *_capture_value)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == _capture_value)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return (ret);
}
#endif

#if (CCP1_SELECTED_MODE_CFG == CCP1_COMPARE_MODE_CFG_SELECT)
/**
 * @brief: See the status of the compare mode operation
 * @param _compare_status the address to store the status of the compare mode
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_compare_mode_status(uint8 *_compare_status)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == _compare_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return (ret);
}
/**
 * @brief: Read the value of the compare mode operation
 * @param _compare_value the address to store the value read from the compare mode operation
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_compare_mode_set_value(uint16 _compare_value)
{
    Std_ReturnType ret = E_OK;

    return (ret);
}
#endif

#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
/**
 * @brief: Set the duty cycle of the PWM mode signal
 * @param _duty the duty cycle to set to the PWM mode signal
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_pwm_set_duty_cycle(const uint8 _duty)
{
    Std_ReturnType ret = E_OK;
    
    return (ret);
}
/**
 * @brief: Start the pwm mode operation
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_pwm_start(void)
{
    Std_ReturnType ret = E_OK;
    
    return (ret);
}
/**
 * @brief: Stop the pwm mode operation
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_pwm_stop(void)
{
    Std_ReturnType ret = E_OK;
    
    return (ret);
}
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief: A helper function to set the interrupt handler of the ccp1 interrupt
 * @param Interrupt_Handler the interrupt handler to call when an interrupt is raised
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType ccp1_set_interrupt_handler(INTERRUPT_HANDLER Interrupt_Handler)
{
    Std_ReturnType ret = E_OK;
   
    /* If the interrupt priority is disabled then enable the peripheral interrupt
    and global interrupts*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
        INTERRUPT_Peripheral_interrupt_ENABLE();
        INTERRUPT_Global_interrupt_ENABLE();
#endif
    if (NULL == Interrupt_Handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ccp1_interrupt_handler = Interrupt_Handler;
    }
    return (ret);
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief: A helper function to set the priority of the ccp1 interrupt
 * @param ccp1_obj the CCP1 module object
 */
static inline void ccp1_set_interrupt_priority(const cpp1_t *ccp1_obj)
{
    INTERRUPT_PRIORITY_levels_ENABLE();
    INTERRUPT_Global_interrupt_LOW_ENABLE();
    INTERRUPT_Global_interrupt_HIGH_ENABLE();
    if (INTERRUPT_HIGH_PRIORITY == ccp1_obj->ccp1_interrupt_priority)
    {
        CCP1_HIGH_PRIORITY();
    }
    else
    {
        CCP1_LOW_PRIORITY();
    }
}
#endif
/**
 * @brief the interrupt service routine of CCP1 module
 */
void CCP1_ISR(void)
{
    CCP1_INTERRUPT_FLAG_BIT_CLEAR();
    if (NULL != ccp1_interrupt_handler)
    {
        ccp1_interrupt_handler();
    }
}
#endif
/**
 * @brief: Select the mode variant and configure the CCP1 pin in PORTC
 * @param ccp1_obj the CCP1 module object
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType ccp1_select_mode(const cpp1_t *ccp1_obj)
{
    Std_ReturnType ret = E_OK;
    
    /* Select the ccp1 mode variant */
    if (ccp1_obj->ccp1_mode_variant <= 12)
    {
        CCP1_SET_MODULE_MODE(ccp1_obj->ccp1_mode_variant);
    }
    else
    {
        /* value cant be more than 12*/
        ret = E_NOT_OK;
    }
    
    /* Configure the ccp1 pin */
    if (CCP1_CAPTURE_MODE_SELECT == ccp1_obj->ccp1_mode)
    {
        ccp1_pin.direction = GPIO_DIRECTION_INPUT;
    }
    else if (CCP1_COMPARE_MODE_SELECT == ccp1_obj->ccp1_mode)
    {
        ccp1_pin.direction = GPIO_DIRECTION_OUTPUT;
    }
    else
    {
        ccp1_pin.direction = GPIO_DIRECTION_OUTPUT;
#if CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT
        /* Set the PR2 Register (period of the PWM) */
        PR2 = (uint8)((_XTAL_FREQ / 
                (ccp1_obj->ccp1_pwm_frequency * 4 * ccp1_obj->timer2_prescaler_value * ccp1_obj->timer2_postscaler_value)) - 1);
#endif
    }
    ret |= gpio_pin_initialize(&ccp1_pin);
    
    return (ret);
}
#endif
#endif