/* 
 * File:   hal_ccp1.h
 * Author: Mohamed olwi
 *
 * Created on 16 October 2024, 22:03
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H
/*----------------------------Header Files------------------------------------*/
#include "../mcal_std_types.h"
#include <xc.h>
#include "../../Interrupt/mcal_internal_interrupt.h"
#include "GPIO/hal_gpio.h"
#include "hal_ccp1_cfg.h"
/*----------------------------Macros Declarations-----------------------------*/
#define CCP1_MODULE_DISABLE                      (uint8)0              /* Capture/Compare/PWM disabled (resets CCPx module) */
/* CCP1 Compare Mode*/
#if (CCP1_SELECTED_MODE_CFG == CCP1_COMPARE_MODE_CFG_SELECT)
#define CCP1_COMPARE_MODE_TOGGLE_ON_MATCH        (uint8)2              /* Compare mode, toggle output on match */
#define CCP1_COMPARE_MODE_FORCE_HIGH             (uint8)8              /* Compare mode, on compare match, force CCPx pin high */
#define CCP1_COMPARE_MODE_FORCE_LOW              (uint8)9              /* Compare mode, on compare match, force CCPx pin low */
#define CCP1_COMPARE_MODE_REFLECTS_IO            (uint8)10             /* Compare mode, generate software interrupt on compare match, CCPx pin reflects I/O state */
#define CCP1_COMPARE_MODE_SPECIAL_EVENT          (uint8)11             /* Compare mode, trigger special event; reset timer; CCPx match starts A/D conversion */
/* CCP1 Compare Mode State */
#define CCP1_COMPARE_MODE_READY                  (uint8)1              /* CCP1 Compare Operation is done */
#define CCP1_COMPARE_MODE_NOT_READY              (uint8)0              /* CCP1 Compare Operation is not done */
#endif

/* CCP1 Capture Mode */
#if (CCP1_SELECTED_MODE_CFG == CCP1_CAPTURE_MODE_CFG_SELECT)
#define CCP1_CAPTURE_MODE_1_FALLING_EDGE         (uint8)4              /* Capture mode, every falling edge */
#define CCP1_CAPTURE_MODE_1_RISING_EDGE          (uint8)5              /* Capture mode, every rising edge */ 
#define CCP1_CAPTURE_MODE_4TH_RISING_EDGE        (uint8)6              /* Capture mode, every 4th rising edge */
#define CCP1_CAPTURE_MODE_16TH_RISING_EDGE       (uint8)7              /* Capture mode, every 16th rising edge */
/* CCP1 Capture Mode State */
#define CCP1_CAPTURE_MODE_READY                  (uint8)1              /* CCP1 Capture Operation is done */
#define CCP1_CAPTURE_MODE_NOT_READY              (uint8)0              /* CCP1 Capture Operation is not done */
#endif

/* CCP1 PWM Mode*/
#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
#define CCP1_PWM_MODE                            (uint8)12             /* PWM mode */
#endif
/*----------------------------Macros Functions Declarations-------------------*/
/**
 * Set the Mode of CCP1 module mode
 */
#define CCP1_SET_MODULE_MODE(__MODE)             (CCP1CONbits.CCP1M = __MODE)
/*----------------------------DataTypes---------------------------------------*/
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
 * @brief: Defines the values needed to store in CCPR to convert from 16bit to two 8-bit and vice versa
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

/**
 * struct cpp1_t - a struct for CCP1 peripheral
 * @ccp1_pwm_frequency: The PWM mode frequency
 * @ccp1_interrupt_handler: The interrupt handler of the CCP1 module
 * @ccp1_priority: The priority of the interrupt raised
 * @ccp1_mode: The mode of the CCP1 module to activate
 * @ccp1_mode_variant: The variant of the mode selected of the CCP1 module
 */
typedef struct
{
#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
    uint32 ccp1_pwm_frequency;
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
 * @param ccp1_obj the CCP1 module object
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
 * @brief: Read the value of the compare mode operation
 * @param _compare_value the address to store the value read from the compare mode operation
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_compare_mode_set_value(uint16 _compare_value);  
#endif

#if (CCP1_SELECTED_MODE_CFG == CCP1_PWM_MODE_CFG_SELECT)
/**
 * @brief: Set the duty cycle of the PWM mode signal
 * @param _duty the duty cycle to set to the PWM mode signal
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_pwm_set_duty_cycle(const uint8 _duty);
/**
 * @brief: Start the pwm mode operation
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_pwm_start(void);
/**
 * @brief: Stop the pwm mode operation
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType ccp1_pwm_stop(void);
#endif
#endif	/* HAL_CCP1_H */

