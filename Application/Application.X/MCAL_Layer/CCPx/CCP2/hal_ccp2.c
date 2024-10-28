/* 
 * File:   hal_ccp2.c
 * Author: Mohamed olwi
 *
 * Created on 16 October 2024, 22:03
 */
#include "hal_ccp2.h"
#if CCP2_MODULE_ENABLE == MCAL_ENABLED
/*---------------Static Data types----------------------------------------------*/
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static INTERRUPT_HANDLER ccp2_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
#endif
static pin_config_t ccp2_pin = {.port = PORTC_INDEX, .pin = GPIO_PIN1, .logic = GPIO_LOW};
/*---------------Static Data types End------------------------------------------*/

/*---------------Static Helper functions declerations---------------------------*/
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType ccp2_set_interrupt_handler(INTERRUPT_HANDLER Interrupt_Handler);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void ccp2_set_interrupt_priority(const cpp2_t *ccp2_obj);
#endif
#endif
static inline Std_ReturnType ccp2_select_mode(const cpp2_t *ccp2_obj);
/*---------------Static Helper functions declerations End-----------------------*/
/**
 * @brief: Initialize the CCP2 module
 * @param ccp2_obj the CCP2 module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp2_init(const cpp2_t *ccp2_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == ccp2_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable CCP2 */
        CCP2_SET_MODULE_MODE(CCP2_MODULE_DISABLE);
        /* Enable CCP2 interrupt if interrupt is enable */
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        CCP2_INTERRUPT_ENABLE();
        ret |= ccp2_set_interrupt_handler(ccp2_obj->ccp2_interrupt_handler);
        /* Set the priority of the CCP2 if the priority feature is enable*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ccp2_set_interrupt_priority(ccp2_obj);
#endif  
#endif
        /* Select the mode variant and configure ccp2 pin */
        ret |= ccp2_select_mode(ccp2_obj);
    }
    return (ret);
}
/**
 * @brief: Deinitialize the CCP2 module
 * @param ccp2_obj the CCP2 module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp2_deinit(const cpp2_t *ccp2_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == ccp2_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        CCP2_SET_MODULE_MODE(CCP2_MODULE_DISABLE);
        /* Disable CCP2 interrupt if interrupt is enable */
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        CCP2_INTERRUPT_DISABLE();
#endif 
    }
    return (ret);
}
#if (CCP2_SELECTED_MODE_CFG == CCP2_CAPTURE_MODE_CFG_SELECT)
/**
 * @brief: See the status of the capture mode operation
 * @param _capture_status the address to store the status of the capture mode
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp2_capture_mode_status(uint8 *_capture_status)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == _capture_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (CCP2_CAPTURE_MODE_READY == PIR1bits.CCP1IF)
        {
            *_capture_status = CCP2_CAPTURE_MODE_READY;
            CCP2_INTERRUPT_FLAG_BIT_CLEAR();
        }
        else
        {
            *_capture_status = CCP2_CAPTURE_MODE_NOT_READY;
        }
    }
    return (ret);
}
/**
 * @brief: Read the value of the capture mode operation
 * @param _capture_value the address to store the value read from the capture mode operation
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp2_capture_mode_read_value(uint16 *_capture_value)
{
    Std_ReturnType ret = E_OK;
    CCP2_PERIOD_REG_T ccp2_reg = {.ccpr2_low = 0, .ccpr2_high = 0};
    
    if (NULL == _capture_value)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ccp2_reg.ccpr2_low = CCPR2L;
        ccp2_reg.ccpr2_high = CCPR2H;
        *_capture_value = ccp2_reg.ccpr2_16bit;
    }
    return (ret);
}
#endif

#if (CCP2_SELECTED_MODE_CFG == CCP2_COMPARE_MODE_CFG_SELECT)
/**
 * @brief: See the status of the compare mode operation
 * @param _compare_status the address to store the status of the compare mode
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp2_compare_mode_status(uint8 *_compare_status)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == _compare_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Compare mode is done */
        if (CCP2_COMPARE_MODE_READY == PIR2bits.CCP2IF)
        {
            *_compare_status = CCP2_COMPARE_MODE_READY;
        }
        else
        {
            /* Compare mode is idle */
             *_compare_status = CCP2_COMPARE_MODE_NOT_READY;
        }
    }
    return (ret);
}
/**
 * @brief: Set the value of the compare mode operation
 * @param _compare_value the value to store inside CCPR2 for compare mode operation
 */
void ccp2_compare_mode_set_value(uint16 _compare_value)
{
    CCP2_PERIOD_REG_T ccp2_reg = {.ccpr2_low = 0, .ccpr2_high = 0};
    
    /* Store the parameterized value into the union for easier setting */
    ccp2_reg.ccpr2_16bit = _compare_value;
    /* Set the value of the CCPR2 register with the value inside the union */
    CCPR2H = ccp2_reg.ccpr2_high;
    CCPR2L = ccp2_reg.ccpr2_low;
}
#endif

#if (CCP2_SELECTED_MODE_CFG == CCP2_PWM_MODE_CFG_SELECT)
/**
 * @brief: Set the duty cycle of the PWM mode signal
 * @param _duty the duty cycle to set to the PWM mode signal
 */
void ccp2_pwm_set_duty_cycle(const uint8 _duty)
{
    /* Duty Cycle equation to store the bits inside CCPR2L:CCP2CON<5:4> */
    uint16 duty_cycle_value= (uint16)((PR2 + 1) * (_duty / 100.0) * 4);
    /* Set the CCPR1L with the 8 bits MSbs */
    CCPR2L = (uint8) (duty_cycle_value >> 2);
    /* Set the CCP2CON<5:4> bits with LSbs */
    CCP2CONbits.DC2B0 = (uint8)(READ_BIT(duty_cycle_value, 0));
    CCP2CONbits.DC2B1 = (uint8)(READ_BIT(duty_cycle_value, 1));
}
/**
 * @brief: Start the pwm mode operation
 */
void ccp2_pwm_start(void)
{
    /* Start PWM mode */
    CCP2_SET_MODULE_MODE(CCP2_PWM_MODE);
}
/**
 * @brief: Stop the pwm mode operation
 */
void ccp2_pwm_stop(void)
{
    /* Stop PWM mode */
    CCP2_SET_MODULE_MODE(CCP2_MODULE_DISABLE);
}
#endif

#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief: A helper function to set the interrupt handler of the ccp2 interrupt
 * @param Interrupt_Handler the interrupt handler to call when an interrupt is raised
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType ccp2_set_interrupt_handler(INTERRUPT_HANDLER Interrupt_Handler)
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
        ccp2_interrupt_handler = Interrupt_Handler;
    }
    return (ret);
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief: A helper function to set the priority of the ccp2 interrupt
 * @param ccp2_obj the CCP2 module object
 */
static inline void ccp2_set_interrupt_priority(const cpp2_t *ccp2_obj)
{
    INTERRUPT_PRIORITY_levels_ENABLE();
    INTERRUPT_Global_interrupt_LOW_ENABLE();
    INTERRUPT_Global_interrupt_HIGH_ENABLE();
    if (INTERRUPT_HIGH_PRIORITY == ccp2_obj->ccp2_interrupt_priority)
    {
        CCP2_HIGH_PRIORITY();
    }
    else
    {
        CCP2_LOW_PRIORITY();
    }
}
#endif
/**
 * @brief the interrupt service routine of CCP2 module
 */
void CCP2_ISR(void)
{
    CCP2_INTERRUPT_FLAG_BIT_CLEAR();
    if (NULL != ccp2_interrupt_handler)
    {
        ccp2_interrupt_handler();
    }
}
#endif
/**
 * @brief: Select the mode variant and configure the CCP2 pin in PORTC
 * @param ccp2_obj the CCP2 module object
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType ccp2_select_mode(const cpp2_t *ccp2_obj)
{
    Std_ReturnType ret = E_OK;
    
    /* Select the ccp2 mode variant */
    if (ccp2_obj->ccp2_mode_variant <= 12)
    {
        CCP2_SET_MODULE_MODE(ccp2_obj->ccp2_mode_variant);
    }
    else
    {
        /* value cant be more than 12*/
        ret = E_NOT_OK;
    }
    
    /* Configure the ccp2 pin */
    if (CCP2_CAPTURE_MODE_SELECT == ccp2_obj->ccp2_mode)
    {
        ccp2_pin.direction = GPIO_DIRECTION_INPUT;
    }
    else if (CCP2_COMPARE_MODE_SELECT == ccp2_obj->ccp2_mode)
    {
        ccp2_pin.direction = GPIO_DIRECTION_OUTPUT;
    }
    else
    {
        ccp2_pin.direction = GPIO_DIRECTION_OUTPUT;
#if CCP2_SELECTED_MODE_CFG == CCP2_PWM_MODE_CFG_SELECT
        /* Set the PR2 Register (period of the PWM) */
        /* The timer2 prescaler and postscaler must be added to one as the enums starts from 0 not 1 */
        PR2 = (uint8)((_XTAL_FREQ / 
                (ccp2_obj->ccp2_pwm_frequency * 4 
                * (ccp2_obj->timer2_prescaler_value + 1) * (ccp2_obj->timer2_postscaler_value + 1))) - 1);
#endif
    }
    ret |= gpio_pin_initialize(&ccp2_pin);
    
    return (ret);
}
#endif
