/* 
 * File:   hal_ccp1.c
 * Author: Mohamed olwi
 *
 * Created on 16 October 2024, 22:03
 */
#include "hal_ccp1.h"

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
#endif