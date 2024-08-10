/* 
 * File:   mcal_interrupt_manager.h
 * Author: Mohamed olwi
 *
 * Created on 01 August 2024, 06:53
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H
/*----------------------------Header Files-----------------------------------------------------------------*/
#include "mcal_interrupt_config.h"
/*----------------------------Function Prototypes----------------------------------------------------------*/

/*--------------------------------INTx ISRS------------------------------------*/
/**
 * @brief: The interrupt service routine of INT0, will be called if INT0 interrupt has been raised
 */
void INT0_ISR(void);
/**
 * @brief: The interrupt service routine of INT1, will be called if INT0 interrupt has been raised
 */
void INT1_ISR(void);
/**
 * @brief: The interrupt service routine of INT2, will be called if INT0 interrupt has been raised
 */
void INT2_ISR(void);
/*--------------------------------RBx ISRS-------------------------------------*/

/**
 * @brief The interrupt service routine of RB4, will be called if RB4 on change interrupt has been raised depending on
 * the source of the calling
 * @param source the source of the calling from the interrupt manager
 */
void RB4_ISR(uint8 source);

/**
 * @brief The interrupt service routine of RB5, will be called if RB4 on change interrupt has been raised depending on
 * the source of the calling
 * @param source the source of the calling from the interrupt manager
 */
void RB5_ISR(uint8 source);

/**
 * @brief The interrupt service routine of RB6, will be called if RB4 on change interrupt has been raised depending on
 * the source of the calling
 * @param source the source of the calling from the interrupt manager
 */
void RB6_ISR(uint8 source);

/**
 * @brief The interrupt service routine of RB7, will be called if RB4 on change interrupt has been raised depending on
 * the source of the calling
 * @param source the source of the calling from the interrupt manager
 */
void RB7_ISR(uint8 source);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

