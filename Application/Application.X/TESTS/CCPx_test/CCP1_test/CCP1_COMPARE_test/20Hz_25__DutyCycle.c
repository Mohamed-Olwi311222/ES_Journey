/*
 * File:  20Hz_25__DutyCycle.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../../../ecu_test_init.h"

volatile uint8 compare_mode_flag = 0;
void CCP1_Interrupt_Handler(void);


cpp1_t ccp1_obj = {
  .ccp1_interrupt_handler = CCP1_Interrupt_Handler,
  .ccp1_interrupt_priority = INTERRUPT_LOW_PRIORITY,
  .ccp1_mode = CCP1_COMPARE_MODE_SELECT,
  .ccp1_mode_variant = CCP1_COMPARE_MODE_FORCE_HIGH,
};
timer3_t timer3_obj = {
  .timer3_interrupt_handler = NULL,
  .timer3_interrupt_priority = INTERRUPT_LOW_PRIORITY,
  .timer3_preloaded_value = 0,
  .rw_mode = _TIMER3_RW_16bit_OP,
  .prescaler_value = TIMER3_PRESCALER_DIV_BY_2,
  .clock_src = _TIMER3_INT_SRC,
  .clk_src_for_ccpx = TIMER3_FOR_CCPx_MODULES,
};
int ccp1_compare_test(void)
{
    Std_ReturnType ret = E_OK;
    /* Set the value of CCPR1 to be 37500(37.5 ms) to make a square wave of 75% off */
    /* Frequency = 20Hz */
    /* Period = 50 ms*/
    ccp1_compare_mode_set_value(37500);
    ret |= ccp1_init(&ccp1_obj);
    ret |= timer3_init(&timer3_obj);
    while (1)
    {

    }
    return (ret);
}
void CCP1_Interrupt_Handler(void)
{
    compare_mode_flag++;
    (void)timer3_write_value(&timer3_obj, 0);
    if (1 == compare_mode_flag)
    {
        /* Load CCPR1 with 12500(12.5 ms) to make 25% on*/
        ccp1_compare_mode_set_value(12500);
        CCP1_SET_MODULE_MODE(CCP1_COMPARE_MODE_FORCE_LOW);
    }
    else if (2 == compare_mode_flag)
    {
        /* Load CCPR1 with 37500(37.5 ms) to make 75% off*/
        ccp1_compare_mode_set_value(37500);
        CCP1_SET_MODULE_MODE(CCP1_COMPARE_MODE_FORCE_HIGH);
        compare_mode_flag = 0;
    }
}
