/* 
 * File:   ecu_seven_seg.h
 * Author: Mohamed olwi
 *
 * Created on 31 May 2024, 10:46
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H
/*----------------------------Header Files------------------------------------*/
#include "ecu_seven_seg_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*----------------------------Macros Declarations-----------------------------*/
#define SEGMENT_PIN0    0
#define SEGMENT_PIN1    1
#define SEGMENT_PIN2    2
#define SEGMENT_PIN3    3
#define PINS_MAX_SIZE   4

#define MAX_BCD_BITS    4
/*----------------------------Macros Functions Declarations-------------------*/

/*----------------------------DataTypes---------------------------------------*/
typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct
{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;
/*----------------------------Function Prototypes-----------------------------*/
Std_ReturnType seven_segment_initialize(const segment_t *seg);
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number);
#endif	/* ECU_SEVEN_SEG_H */

