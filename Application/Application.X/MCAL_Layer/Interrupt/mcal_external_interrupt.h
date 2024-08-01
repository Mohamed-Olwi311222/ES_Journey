/* 
 * File:   mcal_external_interrupt.h
 * Author: Mohamed olwi
 *
 * Created on 01 August 2024, 06:52
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H
/*----------------------------Header Files------------------------------------*/
#include "mcal_interrupt_config.h"

/*----------------------------Macros Declarations-----------------------------*/

/*----------------------------Macros Functions Declarations-------------------*/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/******INT0******/

/**
 * ENABLE INT0 interrupt
 */
#define EXT_INT0_INTERRUPT_ENABLE()                     (INTCONbits.INT0IE = 1)
/**
 * DISABLE INT0 interrupt
 */
#define EXT_INT0_INTERRUPT_DISABLE()                    (INTCONbits.INT0IE = 0)
/**
 * CLEAR INT0 flag bit
 */
#define EXT_INT0_INTERRUPT_FLAG_BIT_CLEAR()            -(INTCONbits.INT0IF = 0)
/**
 * INT0 interrupt on rising edge
 */
#define EXT_INT0_ON_RISING_EDGE()                       (INTCON2bits.INTEDG0 = 1)
/**
 * INT0 interrupt on falling edge
 */
#define EXT_INT0_ON_FALLING_EDGE()                      (INTCON2bits.INTEDG0 = 0)

/******INT1******/
/**
 * ENABLE INT1 interrupt
 */
#define EXT_INT1_INTERRUPT_ENABLE()                     (INTCON3bits.INT1IE = 1)
/**
 * DISABLE INT1 interrupt
 */
#define EXT_INT1_INTERRUPT_DISABLE()                    (INTCON3bits.INT1IE = 0)
/**
 * CLEAR INT1 flag bit
 */
#define EXT_INT1_INTERRUPT_FLAG_BIT_CLEAR()             (INTCON3bits.INT1IF = 0)
/**
 * INT1 interrupt on rising edge
 */
#define EXT_INT1_ON_RISING_EDGE()                       (INTCON2bits.INTEDG1 = 1)
/**
 * INT1 interrupt on falling edge
 */
#define EXT_INT1_ON_FALLING_EDGE()                      (INTCON2bits.INTEDG1 = 0)

/******INT2******/
/**
 * ENABLE INT2 interrupt
 */
#define EXT_INT2_INTERRUPT_ENABLE()                     (INTCON3bits.INT2IE = 1)
/**
 * DISABLE INT2 interrupt
 */
#define EXT_INT2_INTERRUPT_DISABLE()                    (INTCON3bits.INT2IE = 0)
/**
 * CLEAR INT2 flag bit
 */
#define EXT_INT2_INTERRUPT_FLAG_BIT_CLEAR()             (INTCON3bits.INT2IF = 0)
/**
 * INT2 interrupt on rising edge
 */
#define EXT_INT2_ON_RISING_EDGE()                       (INTCON2bits.INTEDG1 = 1)
/**
 * INT2 interrupt on falling edge
 */
#define EXT_INT2_ON_FALLING_EDGE()                      (INTCON2bits.INTEDG1 = 0)

/**PRIORITY FOR EXTERNAL INTERRUPTS**/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * INT1 HIGH priority
 */
#define EXT_INT1_HIGH_PRIORITY()                        (INTCON3bits.INT1P = 1)
/**
 * INT1 LOW priority
 */
#define EXT_INT1_LOW_PRIORITY()                         (INTCON3bits.INT1P = 0)
/**
 * INT2 HIGH priority
 */
#define EXT_INT2_HIGH_PRIORITY()                        (INTCON3bits.INT2P = 1)
/**
 * INT2 LOW priority
 */
#define EXT_INT2_LOW_PRIORITY()                         (INTCON3bits.INT2P = 0)

#endif
#endif
#if EXTERNAL_INTERRUPT_ONChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * ENABLE PORTB On change interrupt
 */
#define EXT_ON_CHANGE_INTERRUPT_ENABLE                  (INTCONbits.RBIE = 1)
/**
 * DISABLE PORTB On change interrupt
 */
#define EXT_ON_CHANGE_INTERRUPT_DISABLE                 (INTCONbits.RBIE = 0)
/**
 * Clear PORTB on change interrupt flag bit
 */
#define EXT_ON_CHANGE_INTERRUPT_FLAG_BIT_CLEAR          (INTCONbits.RBIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * On change interrupt HIGH priority
 */

#endif
#endif

/*----------------------------DataTypes---------------------------------------*/

/*----------------------------Function Prototypes-----------------------------*/
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

