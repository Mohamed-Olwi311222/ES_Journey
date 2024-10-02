/*
 * File:   timer3_counter_mode.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "../../../ecu_test_init.h"

timer3_t timer3_obj = {
    .timer3_preloaded_value = 0,
    .timer3_interrupt_handler = NULL,
    .timer3_interrupt_priority = INTERRUPT_LOW_PRIORITY,
    .clock_src = _TIMER3_EXT_SRC,
    .ext_clk_sync = _TIMER3_ASYNC,
    .prescaler_value = TIMER3_PRESCALER_DIV_BY_1,
    .rw_mode = _TIMER3_RW_16bit_OP
};

timer3_preload_value_t value = ZERO_INIT;
int timer3_counter_mode(void)
{
    Std_ReturnType ret = E_OK; 

    ret |= timer3_init(&timer3_obj);
    while(1)
    {
        ret |= timer3_read_value(&timer3_obj, &value);
    }
    return (0);
}

