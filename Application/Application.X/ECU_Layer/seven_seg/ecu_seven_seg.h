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

/**
 * enum segment_type_t - enum for seven segments module to choose which type
 * @SEGMENT_COMMON_ANODE: 7segment common anode
 * @SEGMENT_COMMON_CATHODE: 7segment common cathode
*/
typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

/**
 * struct segment_t - struct for seven segments module
 * @segment_pins: an array to contain the pins of the seven segment
 * @segment_type: which type is connected 
*/
typedef struct
{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;
/*----------------------------Function Prototypes-----------------------------*/

/**
 * @brief initialize the connected seven segments
 * @param seg a pointer to segment_t datatype @ref segment_t
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg);

/**
 * @brief used to write the required number on the seven segments
 * @param seg a pointer to segment_t datatype @ref segment_t
 * @param number the number to write on the seven segments
 * @return E_OK if success otherwise E_NOT_OK 
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number);
#endif	/* ECU_SEVEN_SEG_H */

