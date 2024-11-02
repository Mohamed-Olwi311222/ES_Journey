/* 
 * File:   hal_ccp1.h
 * Author: Mohamed olwi
 *
 * Created on 22 October 2024, 21:36
 */
#ifndef HAL_CCP1_H
#define	HAL_CCP1_H
/*----------------------------Header Files------------------------------------*/
#include "../../mcal_std_types.h"
#include <xc.h>
#include "../../mcal_layer_cfg.h"
#include "../../Interrupt/mcal_internal_interrupt.h"
#include "../../GPIO/hal_gpio.h"
#include "hal_ccp1_cfg.h"
/*----------------------------Macros Declarations-----------------------------*/
#if CCP1_MODULE_ENABLE == MCAL_ENABLED

/*----------------P1x pins------------------*/
#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
#define P1x_MAX_LEN                              (uint8)4              /* Max lenght of P1x array with pwm pins*/

#else
#define P1x_MAX_LEN                              (uint8)1              /* Max lenght of P1x array without pwm pins*/
#endif
#define P1A_PIN                                  (uint8)0              /* P1A pin index for CCP1 pins */
#define P1B_PIN                                  (uint8)1              /* P1B pin index for CCP1 pins */               
#define P1C_PIN                                  (uint8)2              /* P1C pin index for CCP1 pins */  
#define P1D_PIN                                  (uint8)3              /* P1D pin index for CCP1 pins */  
/*----------------CCP2M bits----------------*/
#define CCP1_MODULE_DISABLE                      (uint8)0              /* Capture/Compare/PWM disabled (resets CCPx module) */
/* CCP2 Compare Mode*/
#if (CCP1_SELECTED_MODE_CFG == CCP1_COMPARE_MODE_CFG_SELECT)
#define CCP1_COMPARE_MODE_TOGGLE_ON_MATCH        (uint8)2              /* Compare mode, toggle output on match */
#define CCP1_COMPARE_MODE_FORCE_HIGH             (uint8)8              /* Compare mode, on compare match, force CCPx pin high */
#define CCP1_COMPARE_MODE_FORCE_LOW              (uint8)9              /* Compare mode, on compare match, force CCPx pin low */
#define CCP1_COMPARE_MODE_REFLECTS_IO            (uint8)10             /* Compare mode, generate software interrupt on compare match, CCPx pin reflects I/O state */
#define CCP1_COMPARE_MODE_SPECIAL_EVENT          (uint8)11             /* Compare mode, trigger special event; reset timer; CCPx match starts A/D conversion */
/* CCP1 Compare Mode State */
#define CCP1_COMPARE_MODE_READY                  (uint8)1              /* CCP2 Compare Operation is done */
#define CCP1_COMPARE_MODE_NOT_READY              (uint8)0              /* CCP2 Compare Operation is not done */
#endif

/* CCP1 Capture Mode */
#if (CCP1_SELECTED_MODE_CFG == CCP1_CAPTURE_MODE_CFG_SELECT)
#define CCP1_CAPTURE_MODE_1_FALLING_EDGE         (uint8)4              /* Capture mode, every falling edge */
#define CCP1_CAPTURE_MODE_1_RISING_EDGE          (uint8)5              /* Capture mode, every rising edge */ 
#define CCP1_CAPTURE_MODE_4TH_RISING_EDGE        (uint8)6              /* Capture mode, every 4th rising edge */
#define CCP1_CAPTURE_MODE_16TH_RISING_EDGE       (uint8)7              /* Capture mode, every 16th rising edge */
/* CCP1 Capture Mode State */
#define CCP1_CAPTURE_MODE_READY                  (uint8)1              /* CCP2 Capture Operation is done */
#define CCP1_CAPTURE_MODE_NOT_READY              (uint8)0              /* CCP2 Capture Operation is not done */
#endif

/* CCP1 PWM Mode*/
#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
#define CCP1_PWM_MODE_P1ABCD_ALL_HIGH            (uint8)12             /* PWM mode, P1A, P1C active-high; P1B, P1D active-high */
#define CCP1_PWM_MODE_P1AC_HIGH_P1BD_LOW         (uint8)13             /* PWM mode, P1A, P1C active-high; P1B, P1D active-low */
#define CCP1_PWM_MODE_P1AC_LOW_P1BD_HIGH         (uint8)14             /* PWM mode, P1A, P1C active-low; P1B, P1D active-high */ 
#define CCP1_PWM_MODE_P1ABCD_ALL_LOW             (uint8)15             /* PWM mode, P1A, P1C active-low; P1B, P1D active-low */ 
#endif
/*----------------------------Macros Functions Declarations-------------------*/
/**
 * Set the Mode of CCP2 module mode
 */
#define CCP1_SET_MODULE_MODE(__MODE)             (CCP1CONbits.CCP1M = __MODE)
#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
/**
 * Set the enhanced pwm output configurations bits
 */
#define CCP1_ENHANCED_PWM_CONFIG(__CFG)           (CCP1CONbits.P1M = __CFG)
#endif
/*----------------------------DataTypes---------------------------------------*/
#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
/**
 * @brief: An enum for CCP1 pwm mode variants
 */
typedef enum
{
    SINGLE_OUTPUT_P1A_MODULATED,                                       /* Single output, P1A modulated; P1B, P1C, P1D assigned as port pins */
    FULL_BRIDGE_OUTPUT_FORWARD,                                        /* Full-bridge output forward, P1D modulated; P1A active; P1B, P1C inactive */
    HALF_BRIDGE_OUTPUT,                                                /* Half-bridge output, P1A, P1B modulated with dead-band control; P1C, P1D assigned as port pins */
    FULL_BRIDGE_OUTPUT_REVERSED                                        /* Full-bridge output reverse, P1B modulated; P1C active; P1A, P1D inactive */
} ccp1_pwm_variant_t;
#endif

/**
 * @brief: An enum for CCP1 mode selection
 */
typedef enum
{
    CCP1_CAPTURE_MODE_SELECT,
    CCP1_COMPARE_MODE_SELECT,
    CCP1_PWM_MODE_SELECT
} ccp1_mode_t;

/**
 * @brief: Defines the values needed to store in CCPR1 to convert from 16bit to two 8-bit and vice versa
 * @Description: Used to get two 8 bit values from 16 bit also two 8-bit values are combined into one 16-bit 
 */
typedef union
{
    struct 
    {
        uint8 ccpr1_low;
        uint8 ccpr1_high;
    };
    struct
    {
        uint16 ccpr1_16bit;
    };
} CCP1_PERIOD_REG_T;

typedef uint8 timer2_TMR2_postscaler_select_t;
typedef uint8 timer2_TMR2_prescaler_select_t;
typedef uint8 ccp1_pwm_output_t;
/**
 * struct cpp1_t - a struct for CCP1 peripheral
 * @ccp1_pwm_frequency: The PWM mode frequency
 * @timer2_postscaler_value: The postscaler value of the timer2 @ref timer2_postscaler_select_t in timer2.h
 * @timer2_prescaler_value: The prescaler value of the timer2 @ref timer2_prescaler_select_t in timer2.h
 * @ccp1_pwm_output_config: The Enhanced PWM Output Configuration 
 * @ccp1_interrupt_handler: The interrupt handler of the CCP1 module
 * @ccp1_interrupt_priority: The priority of the interrupt raised
 * @ccp1_mode: The mode of the CCP2 module to activate
 * @ccp1_mode_variant: The variant of the mode selected of the CCP1 module
 */
typedef struct
{
#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
    uint32 ccp1_pwm_frequency;
    timer2_TMR2_postscaler_select_t timer2_postscaler_value;
    timer2_TMR2_prescaler_select_t timer2_prescaler_value;
    ccp1_pwm_output_t ccp1_pwm_output_config; 
#endif
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_HANDLER ccp1_interrupt_handler;
    interrupt_priority_cfg ccp1_interrupt_priority;
#endif
    ccp1_mode_t ccp1_mode;         
    uint8 ccp1_mode_variant : 4;    
    uint8 RESERVED : 4;
} cpp1_t;
/*----------------------------Function Prototypes-----------------------------*/
/**
 * @brief: Initialize the CCP1 module
 * @param ccp2_obj the CCP1 module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_init(const cpp1_t *ccp1_obj);
/**
 * @brief: Deinitialize the CCP1 module
 * @param ccp1_obj the CCP1 module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_deinit(const cpp1_t *ccp1_obj);

#if (CCP1_SELECTED_MODE_CFG == CCP1_CAPTURE_MODE_CFG_SELECT)
/**
 * @brief: See the status of the capture mode operation
 * @param _capture_status the address to store the status of the capture mode
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_capture_mode_status(uint8 *_capture_status);
/**
 * @brief: Read the value of the capture mode operation
 * @param _capture_value the address to store the value read from the capture mode operation
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_capture_mode_read_value(uint16 *_capture_value);
#endif

#if (CCP1_SELECTED_MODE_CFG == CCP1_COMPARE_MODE_CFG_SELECT)
/**
 * @brief: See the status of the compare mode operation
 * @param _compare_status the address to store the status of the compare mode
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_compare_mode_status(uint8 *_compare_status);
/**
 * @brief: Set the value of the compare mode operation
 * @param _compare_value the value to store inside CCPR1 for compare mode operation
 */
void ccp1_compare_mode_set_value(uint16 _compare_value);
#endif

#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
/**
 * @brief: Set the duty cycle of the PWM mode signal
 * @param _duty the duty cycle to set to the PWM mode signal
 */
void ccp1_pwm_set_duty_cycle(const uint8 _duty);
/**
 * @brief: Set the output configurations of the CCP1 Enhanced PWM mode
 * @param pwm_output_mode_config the output mode configuration to use
 * @param ccp1_pwm_output_config the pwm output pins mode to configure
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_set_pwm_output_config(uint8 pwm_output_mode_config, uint8 ccp1_pwm_output_config);
/**
 * @brief: Start the pwm mode operation
 * @param ccp1_pwm_variant the pwm mode variant to use
 */
void ccp1_pwm_start(ccp1_pwm_variant_t ccp1_pwm_variant);
/**
 * @brief: Stop the pwm mode operation
 */
void ccp1_pwm_stop(void);
#endif
#endif
#endif	/* HAL_CCP1_H */

