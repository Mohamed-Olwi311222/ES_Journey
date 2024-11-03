/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "device_config.h"
#include "MCAL_Layer/CCPx/CCP1/hal_ccp1.h"
#include "MCAL_Layer/Timers/Timer3/hal_timer3.h"
#include "MCAL_Layer/Timers/Timer2/hal_timer2.h"

cpp1_t ccp1_obj = {
  .ccp1_interrupt_handler = NULL,
  .ccp1_interrupt_priority = INTERRUPT_LOW_PRIORITY,
  .ccp1_mode = CCP1_PWM_MODE_SELECT,
  .ccp1_mode_variant = CCP1_PWM_MODE_P1AC_LOW_P1BD_HIGH,
  .ccp1_pwm_output_config = FULL_BRIDGE_OUTPUT_FORWARD,
  .ccp1_pwm_frequency = 20000,
  .timer2_postscaler_value = 1,
  .timer2_prescaler_value = 1
};
timer2_t timer2_obj = {
  .PR2_preloaded_value = 99,
  .TMR2_preloaded_value = 0,
  .postscaler_value = 1,
  .prescaler_value = 1
};
int main(void)
{
    Std_ReturnType ret = E_OK;
    ret |= ccp1_init(&ccp1_obj);
    ret |= timer2_init(&timer2_obj);
    ccp1_pwm_set_duty_cycle(50);
    while (1)
    {

    }
    return (ret);
}
