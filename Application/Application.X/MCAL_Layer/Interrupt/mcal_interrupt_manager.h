/* 
 * File:   mcal_interrupt_manager.h
 * Author: Mohamed olwi
 *
 * Created on 01 August 2024, 06:53
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H
/*----------------------------Header Files------------------------------------*/
#include "mcal_interrupt_config.h"
/*----------------------------Macros Declarations-----------------------------*/

/*----------------------------Macros Functions Declarations-------------------*/

/*----------------------------DataTypes---------------------------------------*/

/*----------------------------Function Prototypes-----------------------------*/

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
#endif	/* MCAL_INTERRUPT_MANAGER_H */

