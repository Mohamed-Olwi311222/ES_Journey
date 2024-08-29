/* 
 * File:   hal_adc.h
 * Author: Mohamed olwi
 *
 * Created on 29 August 2024, 23:42
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
/*----------------------------Header Files------------------------------------*/
#include "hal_adc_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"
#include "xc.h"
/*----------------------------Macros Declarations-----------------------------*/

/*----------------------------Macros Functions Declarations-------------------*/

/*----------------------------DataTypes---------------------------------------*/
/**
 * An enum for ADCON0 bits CHS3:CHS0 for selecting analog channels 
 */
typedef enum
{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}adc_channel_select_t;
/*----------------------------Function Prototypes-----------------------------*/
#endif	/* HAL_ADC_H */

