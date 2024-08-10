/* 
 * File:   mcal_RBx_external_interrupt.h
 * Author: Mohamed olwi
 *
 * Created on 10 August 2024, 08:00 AM
 */

#ifndef MCAL_RBX_EXTERNAL_INTERRUPT_H
#define	MCAL_RBX_EXTERNAL_INTERRUPT_H
/*----------------------------Header Files------------------------------------*/
#include "mcal_interrupt_config.h"

/*----------------------------Macros Declarations-----------------------------*/
#if EXTERNAL_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE

#if EXTERNAL_INTERRUPT_ONChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define RBx_INTERRUPT_HANDLERS_LEN                      2 /*The length of the function pointer array*/
#define RBx_ISR_HIGH                                    0 /*The index of the function pointer to ISR_HIGH*/
#define RBx_ISR_LOW                                     1 /*The index of the function pointer to ISR_LOW*/
/*----------------------------Macros Functions Declarations-------------------*/
/**
 * ENABLE PORTB On change interrupt
 */
#define EXT_RBx_INTERRUPT_ENABLE()                      (INTCONbits.RBIE = 1)
/**
 * DISABLE PORTB On change interrupt
 */
#define EXT_RBx_INTERRUPT_DISABLE()                     (INTCONbits.RBIE = 0)
/**
 * Clear PORTB on change interrupt flag bit
 */
#define EXT_RBx_INTERRUPT_FLAG_BIT_CLEAR()              (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * On change interrupt HIGH priority
 */
#define EXT_RBx_INTERRUPT_HIGH_PRIORITY()               (INTCON2bits.RBIP = 1)
/**
 * On change interrupt LOW priority
 */
#define EXT_RBx_INTERRUPT_LOW_PRIORITY()                (INTCON2bits.RBIP = 0)
#endif


/*----------------------------DataTypes---------------------------------------*/
/**
 * struct interrupt_RBYx_t - a struct for PORTB on change interrupt
 * @EXT_interrupt_handler_High: A pointer to the interrupt handler of RBx if logic is high
 * @EXT_interrupt_handler_Low: A pointer to the interrupt handler of RBx if logic is low
 * @mcu_pin: the mcu pin that caused the interrupt
 * @priortiy: the priority of the RB on change interrupt
 */
typedef struct
{
    INTERRUPT_HANDLER EXT_interrupt_handler_High;
    INTERRUPT_HANDLER EXT_interrupt_handler_Low;
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;
/*----------------------------Function Prototypes-----------------------------*/

/**
 * @brief: A software interface to initialize the PORTB on change interrupt
 * @param int_obj the PORTB on change interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
/**
 * @brief: A software interface to deinitialize the PORTB on change interrupt
 * @param int_obj the PORTB on change interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj);
#endif

#endif
#endif	/* MCAL_RBX_EXTERNAL_INTERRUPT_H */

