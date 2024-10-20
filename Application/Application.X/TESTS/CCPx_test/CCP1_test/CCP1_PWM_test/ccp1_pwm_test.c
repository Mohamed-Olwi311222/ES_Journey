/*
 * File:   ccp1_pwm_test.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../../../ecu_test_init.h""
int ccp1_pwm_test(void)
{
    Std_ReturnType ret = E_OK;
    uint8 pwm_duty_cycle = ZERO_INIT;
    
    cpp1_t ccp1_obj = {
      .ccp1_interrupt_handler = NULL,
      .ccp1_interrupt_priority = INTERRUPT_LOW_PRIORITY,
      .ccp1_mode = CCP1_PWM_MODE,
      .ccp1_mode_variant = CCP1_PWM_MODE,
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

    ret |= timer2_init(&timer2_obj);
    ret |= ccp1_init(&ccp1_obj);
    ccp1_pwm_start();

    while (1)
    {
        __delay_ms(5);
        ccp1_pwm_set_duty_cycle(pwm_duty_cycle++);
        if (pwm_duty_cycle > 100)
            pwm_duty_cycle = 0;
    }
    return (ret);
}

