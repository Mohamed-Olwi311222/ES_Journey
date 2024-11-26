/* 
 * File:   hal_ccp2.c
 * Author: Mohamed olwi
 *
 * Created on 22 October 2024, 21:36
 */
#if CCP2_MODULE_ENABLE == MCAL_ENABLED
#include "hal_ccp1.h"
#if CCP1_MODULE_ENABLE == MCAL_ENABLED
/*---------------Static Data types----------------------------------------------*/
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static INTERRUPT_HANDLER ccp1_interrupt_handler = NULL; /* A pointer to the callback function when an interrupt is raised */
#endif
// Declaration of the array at the global level
static pin_config_t P1x_pins[P1x_MAX_LEN];
/*---------------Static Data types End------------------------------------------*/

/*---------------Static Helper functions declerations---------------------------*/
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType ccp1_set_interrupt_handler(INTERRUPT_HANDLER Interrupt_Handler);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static inline void ccp1_set_interrupt_priority(const cpp1_t *ccp1_obj);
#endif
#endif
static inline Std_ReturnType ccp1_select_mode(const cpp1_t *ccp1_obj);
static inline Std_ReturnType ccp1_set_enhanced_pwm_output(uint8 pwm_output_config);
static inline void initialize_P1x_pins(void);

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
        /* Initialize the P1x pins with the correct pin, port and direction */
        initialize_P1x_pins();
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
        if (CCP1_CAPTURE_MODE_READY == PIR1bits.CCP1IF)
        {
            *_capture_status = CCP1_CAPTURE_MODE_READY;
            CCP1_INTERRUPT_FLAG_BIT_CLEAR();
        }
        else
        {
            *_capture_status = CCP1_CAPTURE_MODE_NOT_READY;
        }
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
    CCP1_PERIOD_REG_T ccp1_reg = {.ccpr1_low = 0, .ccpr1_high = 0};
    
    if (NULL == _capture_value)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ccp1_reg.ccpr1_low = CCPR1L;
        ccp1_reg.ccpr1_high = CCPR1H;
        *_capture_value = ccp1_reg.ccpr1_16bit;
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
        /* Compare mode is done */
        if (CCP1_COMPARE_MODE_READY == PIR1bits.CCP1IF)
        {
            *_compare_status = CCP1_COMPARE_MODE_READY;
        }
        else
        {
            /* Compare mode is idle */
             *_compare_status = CCP1_COMPARE_MODE_NOT_READY;
        }
    }
    return (ret);
}
/**
 * @brief: Set the value of the compare mode operation
 * @param _compare_value the value to store inside CCPR1 for compare mode operation
 */
void ccp1_compare_mode_set_value(uint16 _compare_value)
{
    CCP1_PERIOD_REG_T ccp1_reg = {.ccpr1_low = 0, .ccpr1_high = 0};
    
    /* Store the parameterized value into the union for easier setting */
    ccp1_reg.ccpr1_16bit = _compare_value;
    /* Set the value of the CCPR1 register with the value inside the union */
    CCPR1H = ccp1_reg.ccpr1_high;
    CCPR1L = ccp1_reg.ccpr1_low;
}
#endif

#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
/**
 * @brief: Set the duty cycle of the PWM mode signal
 * @param _duty the duty cycle to set to the PWM mode signal
 */
void ccp1_pwm_set_duty_cycle(const uint8 _duty)
{
    /* Duty Cycle equation to store the bits inside CCPR1L:CCP1CON<5:4> */
    uint16 duty_cycle_value= (uint16)((PR2 + 1) * (_duty / 100.0) * 4);
    /* Set the CCPR1L with the 8 bits MSbs */
    CCPR1L = (uint8) (duty_cycle_value >> 2);
    /* Set the CCP1CON<5:4> bits with LSbs */
    CCP1CONbits.DC1B0 = (uint8)(READ_BIT(duty_cycle_value, 0));
    CCP1CONbits.DC1B1 = (uint8)(READ_BIT(duty_cycle_value, 1));
}
/**
 * @brief: Set the output configurations of the CCP1 Enhanced PWM mode
 * @param pwm_output_mode_config the output mode configuration to use
 * @param ccp1_pwm_output_config the pwm output pins mode to configure
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_set_pwm_output_config(uint8 pwm_output_mode_config, uint8 ccp1_pwm_output_config)
{
    Std_ReturnType ret = E_OK;
    ret = ccp1_set_enhanced_pwm_output(pwm_output_mode_config);
    if (E_OK == ret)
    {    /* Set the output of the enhanced pwm mode */
        CCP1_ENHANCED_PWM_CONFIG(ccp1_pwm_output_config);
    }
    else
    {
        ret = E_NOT_OK;
    }
    return (ret);
}

/**
 * @breif: Configure the CCP1 PWM output config
 * @param pwm_output_config the needed pwm output config
 * @return E_OK if success otherwise E_NOT_OK
 */
static inline Std_ReturnType ccp1_set_enhanced_pwm_output(uint8 pwm_output_pins_config)
{
    Std_ReturnType ret = E_OK;
    
    switch (pwm_output_pins_config)
    {
        case CCP1_PWM_MODE_P1ABCD_ALL_HIGH:
            /* P1A, P1B, P1C and P1D are all active high */
            CCP1CONbits.CCP1M = CCP1_PWM_MODE_P1ABCD_ALL_HIGH;
            P1x_pins[P1A_PIN].logic = GPIO_HIGH;
            P1x_pins[P1C_PIN].logic = GPIO_HIGH;
            P1x_pins[P1B_PIN].logic = GPIO_HIGH;
            P1x_pins[P1D_PIN].logic = GPIO_HIGH;
            break;
        case CCP1_PWM_MODE_P1AC_HIGH_P1BD_LOW:
            /* P1A and P1C are acive high, P1B and P1D are active low */
            CCP1CONbits.CCP1M = CCP1_PWM_MODE_P1AC_HIGH_P1BD_LOW;
            P1x_pins[P1A_PIN].logic = GPIO_HIGH;
            P1x_pins[P1C_PIN].logic = GPIO_HIGH;
            P1x_pins[P1B_PIN].logic = GPIO_LOW;
            P1x_pins[P1D_PIN].logic = GPIO_LOW;
            break;
        case CCP1_PWM_MODE_P1AC_LOW_P1BD_HIGH:
            /* P1A and P1C are acive low, P1B and P1D are active high */
            CCP1CONbits.CCP1M = CCP1_PWM_MODE_P1AC_LOW_P1BD_HIGH;
            P1x_pins[P1A_PIN].logic = GPIO_LOW;
            P1x_pins[P1C_PIN].logic = GPIO_LOW;
            P1x_pins[P1B_PIN].logic = GPIO_HIGH;
            P1x_pins[P1D_PIN].logic = GPIO_HIGH;
            break;
        case CCP1_PWM_MODE_P1ABCD_ALL_LOW:
            /* P1A, P1B, P1C and P1D are all active low */
            CCP1CONbits.CCP1M = CCP1_PWM_MODE_P1ABCD_ALL_LOW;
            P1x_pins[P1A_PIN].logic = GPIO_LOW;
            P1x_pins[P1C_PIN].logic = GPIO_LOW;
            P1x_pins[P1B_PIN].logic = GPIO_LOW;
            P1x_pins[P1D_PIN].logic = GPIO_LOW;
            break;
        default:
            ret = E_NOT_OK;
    }
    if (E_OK == ret)
    {
        ret |= gpio_pin_direction_initialize(&P1x_pins[P1A_PIN]);
        ret |= gpio_pin_direction_initialize(&P1x_pins[P1C_PIN]);
        ret |= gpio_pin_direction_initialize(&P1x_pins[P1B_PIN]);
        ret |= gpio_pin_direction_initialize(&P1x_pins[P1D_PIN]);
    }
    return (ret);
}
/**
 * @brief: Start the pwm mode operation
 * @param ccp1_pwm_variant the pwm mode variant to use
 */
void ccp1_pwm_start(ccp1_pwm_variant_t ccp1_pwm_variant)
{
    /* Start Enhanced PWM mode */
    CCP1_SET_MODULE_MODE(ccp1_pwm_variant);
}
/**
 * @brief: Stop the pwm mode operation
 */
void ccp1_pwm_stop(void)
{
    /* Stop PWM mode */
    CCP1_SET_MODULE_MODE(CCP1_MODULE_DISABLE);
}
#endif

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
 * @param ccp1_obj the CCP2 module object
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
    if (ccp1_obj->ccp1_mode_variant <= 15)
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
        P1x_pins[P1A_PIN].direction = 1;
        ret |= gpio_pin_direction_initialize(&P1x_pins[P1A_PIN]);
    }
    else if (CCP1_COMPARE_MODE_SELECT == ccp1_obj->ccp1_mode)
    {
        P1x_pins[P1A_PIN].direction = GPIO_DIRECTION_OUTPUT;
        ret |= gpio_pin_direction_initialize(&P1x_pins[P1A_PIN]);
    }
    else
    {
        P1x_pins[P1A_PIN].direction = GPIO_DIRECTION_OUTPUT;
#if CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT
        /* Set the PR2 Register (period of the PWM) */
        /* The timer2 prescaler and postscaler must be added to one as the enums starts from 0 not 1 */
        PR2 = (uint8)((_XTAL_FREQ / 
                (ccp1_obj->ccp1_pwm_frequency * 4 
                * (ccp1_obj->timer2_prescaler_value + 1) * (ccp1_obj->timer2_postscaler_value + 1))) - 1);
        ret |= ccp1_set_pwm_output_config(ccp1_obj->ccp1_mode_variant, ccp1_obj->ccp1_pwm_output_config);

#endif
    }
    return (ret);
}
/**
 * @brief initialize the P1x pins
 */
static inline void initialize_P1x_pins(void)
{
    /* P1A pin */
    P1x_pins[P1A_PIN].port = PORTC_INDEX;
    P1x_pins[P1A_PIN].pin = GPIO_PIN2;
    /* PWM pins*/
    #if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
    /* P1B pin */
    P1x_pins[P1B_PIN].port = PORTD_INDEX;
    P1x_pins[P1B_PIN].pin = GPIO_PIN5;
    P1x_pins[P1B_PIN].direction = GPIO_DIRECTION_OUTPUT;
    /* P1C pin */
    P1x_pins[P1C_PIN].port = PORTD_INDEX;
    P1x_pins[P1C_PIN].pin = GPIO_PIN6;
    P1x_pins[P1C_PIN].direction = GPIO_DIRECTION_OUTPUT;
    /* P1D pin */
    P1x_pins[P1D_PIN].port = PORTD_INDEX;
    P1x_pins[P1D_PIN].pin = GPIO_PIN7;
    P1x_pins[P1D_PIN].direction = GPIO_DIRECTION_OUTPUT;
    #endif
}
#endif
#endif