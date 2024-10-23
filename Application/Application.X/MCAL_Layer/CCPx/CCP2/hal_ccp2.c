/* 
 * File:   hal_ccp2.c
 * Author: Mohamed olwi
 *
 * Created on 22 October 2024, 21:36
 */
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

  }
  return (ret);
}
/**
 * @brief: Set the value of the compare mode operation
 * @param _compare_value the value to store inside CCPR2 for compare mode operation
 */
void ccp2_compare_mode_set_value(uint16 _compare_value)
{

}
#endif

#if (CCP2_SELECTED_MODE_CFG == CCP2_PWM_MODE_CFG_SELECT)
/**
 * @brief: Set the duty cycle of the PWM mode signal
 * @param _duty the duty cycle to set to the PWM mode signal
 */
void ccp2_pwm_set_duty_cycle(const uint8 _duty)
{
  
}
/**
 * @brief: Start the pwm mode operation
 */
void ccp2_pwm_start(void)
{

}
/**
 * @brief: Stop the pwm mode operation
 */
void ccp2_pwm_stop(void)
{

}
#endif

