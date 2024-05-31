/*
 * File:   ecu_seven_seg.c
 * Author: Mohamed olwi
 *
 * Created on 31 May 2024, 10:47
 */
#include "ecu_seven_seg.h"
Std_ReturnType seven_segment_initialize(const segment_t *seg)
{
    Std_ReturnType ret = E_OK;
    if (NULL == seg)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 pin_num = 0;
        for (; pin_num < PINS_MAX_SIZE; pin_num++)
        {
            ret = gpio_pin_initialize(&(seg->segment_pins[pin_num]));
            if (E_NOT_OK == ret)
            {
                break;
            }
        }
    }
    return (ret);
}
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number)
{
    Std_ReturnType ret = E_OK;
    if (NULL == seg || number > 9)
    {
        ret = E_NOT_OK;
    }
    else
    {
        uint8 curr_bit = 0;
        uint8 pin_num = 0;
        for (; curr_bit < MAX_BCD_BITS; curr_bit++, pin_num++)
        {
            ret = gpio_pin_write_logic(&(seg->segment_pins[pin_num]), READ_BIT(number, curr_bit));
            if (E_NOT_OK == ret)
            {
                break;
            }
        }
    }
    return (ret);
}