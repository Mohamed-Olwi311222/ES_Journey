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

/*----------------ADCON0 bits----------------*/
/*--------ADON bit--------*/
#define ADC_ENABLE_ON           1 /*ADC enable on*/
#define ADC_ENABLE_OFF          0 /*ADC enable off*/
/*--------GODONE bit--------*/
#define ADC_IDLE                0 /*ADC idle status*/
#define ADC_START_CONV          1 /*ADC conversion start*/
#define ADC_NOT_IDLE            1 /*ADC conversion in progress*/
/*----------------ADCON1 bits----------------*/
/*--------VFG0 and VFG1 bit--------*/
#define ADC_VREF_INTENAL        0 /*ADC vref is internal (VSS and VDD)*/
#define ADC_POS_VREF_VSS        0 /*ADC +ve vref is VSS*/
#define ADC_NEG_VREF_VDD        0 /*ADC -ve vref is VSS*/

#define ADC_VREF_EXTERNAL       1 /*ADC vref is external (AN2 and AN3)*/
#define ADC_POS_VREF_AN3        1 /*ADC +ve vref is AN3*/
#define ADC_NEG_VREF_AN2        1 /*ADC -ve vref is AN2*/

/*----------------ADCON1 bits----------------*/
#define ADC_RES_RIGHT_JUSTIFY   1 /*ADC result is right justified*/
#define ADC_RES_LEFT_JUSTIFY    0 /*ADC result is left justified*/

/*----------------------------Macros Functions Declarations-------------------*/

/*----------------ADCON0 bits----------------*/
/*--------ADON bit--------*/
/**
 * Enable ADC (set ADON bit)
 */
#define ENABLE_ADC_CONVERSION()                     (ADCON0bits.ADON = ADC_ENABLE_ON)  
/*
 * Disable ADC (unset ADON bit)
 */
#define DISABLE_ADC_CONVERSION()                    (ADCON0bits.ADON = ADC_ENABLE_OFF)  

/*--------GODONE bit--------*/
/*
 * Start ADC conversion (set GO bit)
 */
#define START_ADC_CONV()                            (ADCON0bits.GO = ADC_START_CONV)            
/*
 * Get the status of the ADC conversion (GODONE bit)
 */
#define ADC_CONV_STATUS(ADDR)                       (*ADDR = ADCON0bits.DONE)       

/*--------CHS3:CHS0 bits--------*/
/**
 * Set the analog input channel (CHS3:CHS0 bits) with _CONFIG @ref adc_channel_select_t
 */
#define ADC_SET_ANALOG_CHANNEL(_CONFIG)             (ADCON0bits.CHS = _CONFIG)

/*----------------ADCON1 bits----------------*/
/*VFG0 and VFG1 bit*/
/**
 * Set the +vref t0 AN3 pin and -vref to AN2 pin
 */
#define ADC_VREF_INTERNAL()                         do{                                      \
                                                        ADCON1bits.VCFG0 = ADC_NEG_VREF_VDD; \
                                                        ADCON1bits.VCFG1 = ADC_POS_VREF_VSS; \
                                                    }while(0);
/**
 * Set the +vref to VDD pin and -vref to VSS pin
 */
#define ADC_VREF_EXT()                              do{                                      \
                                                        ADCON1bits.VCFG0 = ADC_POS_VREF_AN3; \
                                                        ADCON1bits.VCFG1 = ADC_NEG_VREF_AN2; \
                                                    }while(0);
/**
 * Set A/D Port Configuration Control bits with _CONFIG @ref adc_port_config_select_t
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)         (ADCON1bits.PCFG = _CONFIG)

/*----------------ADCON2 bits----------------*/
/*--------ADFM bit--------*/
/**
 * Set the ADC result to left justified
 **/
#define ADC_SET_RESULT_LEFT_JUSTIFY()                   (ADCON2bits.ADFM = ADC_RES_LEFT_JUSTIFY)      
/**
 * Set the ADC result to right justified
 **/
#define ADC_SET_RESULT_RIGHT_JUSTIFY()                  (ADCON2bits.ADFM = ADC_RES_RIGHT_JUSTIFY)                  

/*--------ADCS2:ADCS0 bits--------*/
/**
 * Set A/D Conversion Clock Select bits with _CONFIG @ref adc_conversion_clock_select_t
 */
#define ADC_SET_CONVERSION_CLOCK(_CONFIG)         (ADCON2bits.ADCS = _CONFIG)

/*--------ADQT2:ADQT0 bits--------*/
/**
 * Set A/D Acquisition Time Select bits with _CONFIG @ref adc_acquisition_time_select_t
 */
#define ADC_SET_ACQUISITION_TIME(_CONFIG)         (ADCON2bits.ACQT = _CONFIG)
/*----------------------------DataTypes---------------------------------------*/

typedef uint8 vref_t;                                    /* A typedef for adc vref select */
typedef uint8 adc_res_justification_t;                   /* A typedef for adc result justification*/
typedef uint16 adc_conversion_result;                     /* A typedef for adc conversion result */
typedef uint8 adc_conversion_status;                     /* A typedef for adc conversion status */

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
} adc_channel_select_t;

/**
 *  An enum for selecting ADC port configuration control bits
 * Note: ANO__ANX means that all Analog pins from AN0 to ANX are analog
 */
typedef enum
{
    ADC_ALL_ANALOG_FUNCTIONALITY        = 0x02,
    ADC_AN0__AN11__ANALOG_FUNCTIONALITY = 0x03,
    ADC_AN0__AN10__ANALOG_FUNCTIONALITY = 0x04,
    ADC_AN0__AN9__ANALOG_FUNCTIONALITY  = 0x05,  
    ADC_AN0__AN8__ANALOG_FUNCTIONALITY  = 0x06, 
    ADC_AN0__AN7__ANALOG_FUNCTIONALITY  = 0x07,  
    ADC_AN0__AN6__ANALOG_FUNCTIONALITY  = 0x08, 
    ADC_AN0__AN5__ANALOG_FUNCTIONALITY  = 0x09,  
    ADC_AN0__AN4__ANALOG_FUNCTIONALITY  = 0x0A, 
    ADC_AN0__AN3__ANALOG_FUNCTIONALITY  = 0x0B,  
    ADC_AN0__AN2__ANALOG_FUNCTIONALITY  = 0x0C,
    ADC_AN0__AN1__ANALOG_FUNCTIONALITY  = 0x0D,
    ADC_AN0_ANALOG_FUNCTIONALITY        = 0x0E,
    ADC_ALL_DIGITAL_FUNCTIONALITY       = 0x0F
} adc_port_config_select_t;

/**
 * An enum for selecting ADC conversion clock
 * Note1: FOSCx means FOSC/x
 * Note2: FRC means clock derived from A/D RC oscillator
 */
typedef enum
{
    ADC_CONVERSION_CLOCK_FOSC2 = 0,
    ADC_CONVERSION_CLOCK_FOSC8,
    ADC_CONVERSION_CLOCK_FOSC32,
    ADC_CONVERSION_CLOCK_FRC,
    ADC_CONVERSION_CLOCK_FOSC4,
    ADC_CONVERSION_CLOCK_FOSC16,    
    ADC_CONVERSION_CLOCK_FOSC64 
} adc_conversion_clock_select_t;
/**
 * An enum for selecting ADC Acquisition time
 * Note: TAD depends on Clock source @ref adc_conversion_clock_select_t
 **/
typedef enum
{
    ADC_ACQUISITION_TIME_0_TAD = 0,
    ADC_ACQUISITION_TIME_2_TAD,    
    ADC_ACQUISITION_TIME_4_TAD,
    ADC_ACQUISITION_TIME_6_TAD,
    ADC_ACQUISITION_TIME_8_TAD,
    ADC_ACQUISITION_TIME_12_TAD,
    ADC_ACQUISITION_TIME_16_TAD,
    ADC_ACQUISITION_TIME_20TAD,
} adc_acquisition_time_select_t;

/**
 * struct adc_config_t - struct for adc config
 * @adc_interrupt_handler: The callback to call when an interrupt is raised
 * @adc_port_config: The adc port configuration for deciding which ANx is analog
 * @adc_analog_channel: The analog channel used for analog input
 * @conversion_clock: the conversion clock used
 * @aquisition_time: the acquisition time needed for the adc
*/
typedef struct
{
    INTERRUPT_HANDLER adc_interrupt_handler;            /* ADC interrupt handler */
    adc_port_config_select_t adc_port_config;           /* @ref adc_conversion_clock_select_t */
    adc_channel_select_t adc_analog_channel;            /* @ref adc_channel_select_t          */
    adc_conversion_clock_select_t conversion_clock;     /* @ref adc_conversion_clock_select_t */
    adc_acquisition_time_select_t aquisition_time;      /* @ref adc_acquisition_time_select_t */
    vref_t voltage_ref : 1;                             /* Vref configuration                 */
    adc_res_justification_t result_format : 1;          /* ADC result format select           */
    uint8 RESERVED : 6;
} adc_config_t;
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief: Initialize the adc peripheral
 * @param adc_obj the adc object to initialize
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_init(const adc_config_t *adc_obj);
/**
 * @brief: Deinitialize the adc peripheral
 * @param adc_obj the adc object to deinitialize
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_deinit(const adc_config_t *adc_obj);
/**
 * @brief: Select the adc input channel
 * @param adc_obj the adc config used
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_select_channel(const adc_config_t *adc_obj);
/**
 * @brief: Start the adc conversion
 * @param adc_obj the adc config used
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_start_conversion(const adc_config_t *adc_obj);
/**
 * @brief: Read the status of the adc conversion
 * @param adc_obj the adc config used
 * @param adc_status the address to store the status of the adc conversion
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_read_conversion_status(const adc_config_t *adc_obj, adc_conversion_status *adc_status);
/**
 * @brief: Read the result of the adc conversion
 * @param adc_obj the adc config used
 * @param adc_result the address to store the result of the adc conversion
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_read_result(const adc_config_t *adc_obj, adc_conversion_result *adc_result);
/**
 * @brief: Get the conversion done by the adc on from a specific input channel and wait until the conversion is done
 *         and read the result to the specified memory address
 * @param adc_obj the adc config used
 * @param channel the input channel to read the input from
 * @param result the adddress to store the result of the adc conversion
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType adc_get_conversion(const adc_config_t *adc_obj, adc_channel_select_t channel, adc_conversion_result * result);
#endif	/* HAL_ADC_H */

