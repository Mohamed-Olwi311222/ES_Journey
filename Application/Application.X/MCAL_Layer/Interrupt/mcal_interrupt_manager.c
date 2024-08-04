/* 
 * File:   mcal_interrupt_manager.c
 * Author: Mohamed olwi
 *
 * Created on 01 August 2024, 06:51
 */
#include "mcal_interrupt_manager.h"
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief the interrupt manager for high priority interrupts
 */
void __interrupt() Interrupt_Manager_High(void)
{

}
/**
 * @brief the interrupt manager for low priority interrupts
 */
void  __interrupt(low_priority) Interrupt_Manager_Low(void)
{

}
 #else
void __interrupt() Interrupt_Manager(void)
{
    if ((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR(); // Call the ISR function
    }
}
#endif
