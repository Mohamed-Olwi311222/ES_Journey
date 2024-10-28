/*
 * File:  20Hz_25__DutyCycle.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../../../ecu_test_init.h"

volatile uint8 compare_mode_flag = 0;
void CCP2_Interrupt_Handler(void);


cpp2_t ccp2_obj = {
  .ccp2_interrupt_handler = CCP2_Interrupt_Handler,
  .ccp2_interrupt_priority = INTERRUPT_LOW_PRIORITY,
  .ccp2_mode = CCP2_COMPARE_MODE_SELECT,
  .ccp2_mode_variant = CCP2_COMPARE_MODE_FORCE_HIGH,
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
int ccp2_compare_test(void)
{
    Std_ReturnType ret = E_OK;
    /* Set the value of CCPR2 to be 37500(37.5 ms) to make a square wave of 75% off */
    /* Frequency = 20Hz */
    /* Period = 50 ms*/
    ccp2_compare_mode_set_value(37500);
    ret |= ccp2_init(&ccp2_obj);
    ret |= timer3_init(&timer3_obj);
    while (1)
    {

    }
    return (ret);
}
void CCP2_Interrupt_Handler(void)
{
    compare_mode_flag++;
    (void)timer3_write_value(&timer3_obj, 0);
    if (1 == compare_mode_flag)
    {
        /* Load CCPR2 with 12500(12.5 ms) to make 25% on*/
        ccp2_compare_mode_set_value(12500);
        CCP2_SET_MODULE_MODE(CCP2_COMPARE_MODE_FORCE_LOW);
    }
    else if (2 == compare_mode_flag)
    {
        /* Load CCPR2 with 37500(37.5 ms) to make 75% off*/
        ccp2_compare_mode_set_value(37500);
        CCP2_SET_MODULE_MODE(CCP2_COMPARE_MODE_FORCE_HIGH);
        compare_mode_flag = 0;
    }
}
