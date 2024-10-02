/* 
 * File:   mcal_interrupt_manager.c
 * Author: Mohamed olwi
 *
 * Created on 01 August 2024, 06:51
 */
#include "mcal_interrupt_manager.h"
#if EXTERNAL_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
#if EXTERNAL_INTERRUPT_ONChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static volatile uint8 RB4_Flag = RBx_FLAG_TRUE;          /*A flag to indicates that the ISR_RB4 has been called*/
static volatile uint8 RB5_Flag = RBx_FLAG_TRUE;          /*A flag to indicates that the ISR_RB5 has been called*/
static volatile uint8 RB6_Flag = RBx_FLAG_TRUE;          /*A flag to indicates that the ISR_RB6 has been called*/
static volatile uint8 RB7_Flag = RBx_FLAG_TRUE;          /*A flag to indicates that the ISR_RB7 has been called*/
#endif
#endif
     
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief the interrupt manager for high priority interrupts
 */
void __interrupt() Interrupt_Manager_High(void)
{
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
#endif
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == INTCONbits.T0IE) && (INTERRUPT_OCCUR == INTCONbits.T0IF))
    {
        TIMER0_ISR();
    }
#endif
#if EXTERNAL_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR(); // Call the ISR function
    }
    if ((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR(); // Call the ISR function
    }
#endif
#endif
}
/**
 * @brief the interrupt manager for low priority interrupts
 */
void  __interrupt(low_priority) Interrupt_Manager_Low(void)
{
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TIMER3_ISR();
    }
#endif
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TIMER2_ISR();
    }
#endif
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TIMER1_ISR();
    }
#endif
    #if EXTERNAL_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
    #if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR(); // Call the ISR function
    }  
    #endif
    #if EXTERNAL_INTERRUPT_ONChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*------------------------PORTB on change interrupt------------------------*/
    /*---------------RB4--------------------------*/
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_HIGH == PORTBbits.RB4) && (RBx_FLAG_TRUE == RB4_Flag))
    {
        RB4_Flag = RBx_FLAG_FALSE;
        RB4_ISR(0); // Call the ISR function
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&&
            (GPIO_LOW == PORTBbits.RB4) && (RBx_FLAG_FALSE == RB4_Flag))
    {
        RB4_Flag = RBx_FLAG_TRUE;
        RB4_ISR(1); // Call the ISR function
    }
    
    /*---------------RB5--------------------------*/
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_HIGH == PORTBbits.RB5) && (RBx_FLAG_TRUE == RB5_Flag))
    {
        RB5_Flag = RBx_FLAG_FALSE;
        RB5_ISR(0); // Call the ISR function
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_LOW == PORTBbits.RB5 ) && (RBx_FLAG_FALSE == RB5_Flag))
    {
        RB5_Flag = RBx_FLAG_TRUE;
        RB5_ISR(1); // Call the ISR function
    }
    /*---------------RB6--------------------------*/
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_HIGH == PORTBbits.RB6) && (RBx_FLAG_TRUE == RB6_Flag))
    {
        RB6_Flag = RBx_FLAG_FALSE;
        RB6_ISR(0); // Call the ISR function
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_LOW == PORTBbits.RB6 ) && (RBx_FLAG_FALSE == RB6_Flag))
    {
        RB6_Flag = RBx_FLAG_TRUE;
        RB6_ISR(1); // Call the ISR function
    }
    /*---------------RB7--------------------------*/
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_HIGH == PORTBbits.RB7) && (RBx_FLAG_TRUE == RB7_Flag))
    {
        RB7_Flag = RBx_FLAG_FALSE;
        RB7_ISR(0); // Call the ISR function
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_LOW == PORTBbits.RB7 ) && (RBx_FLAG_FALSE == RB7_Flag))
    {
        RB7_Flag = RBx_FLAG_TRUE;
        RB7_ISR(1); // Call the ISR function
    }
    #endif
    #endif

}
#else
void __interrupt() Interrupt_Manager(void)
{
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
#endif
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if ((INTERRUPT_ENABLE == INTCONbits.T0IE) && (INTERRUPT_OCCUR == INTCONbits.T0IF))
    {
        TIMER0_ISR();
    }
#endif
    #if EXTERNAL_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
    #if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*------------------------INTx External Interrupts------------------------*/
    /*---------------INT0-------------------------*/
    if ((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR(); // Call the ISR function
    }
    /*---------------INT1-------------------------*/
    if ((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR(); // Call the ISR function
    }
    /*---------------INT2-------------------------*/
    if ((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR(); // Call the ISR function
    }
    #endif
    #if EXTERNAL_INTERRUPT_ONChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /*------------------------PORTB on change interrupt------------------------*/
    /*---------------RB4--------------------------*/
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_HIGH == PORTBbits.RB4) && (RBx_FLAG_TRUE == RB4_Flag))
    {
        RB4_Flag = RBx_FLAG_FALSE;
        RB4_ISR(0); // Call the ISR function
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF)&&
            (GPIO_LOW == PORTBbits.RB4) && (RBx_FLAG_FALSE == RB4_Flag))
    {
        RB4_Flag = RBx_FLAG_TRUE;
        RB4_ISR(1); // Call the ISR function
    }
    
    /*---------------RB5--------------------------*/
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_HIGH == PORTBbits.RB5) && (RBx_FLAG_TRUE == RB5_Flag))
    {
        RB5_Flag = RBx_FLAG_FALSE;
        RB5_ISR(0); // Call the ISR function
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_LOW == PORTBbits.RB5 ) && (RBx_FLAG_FALSE == RB5_Flag))
    {
        RB5_Flag = RBx_FLAG_TRUE;
        RB5_ISR(1); // Call the ISR function
    }
    /*---------------RB6--------------------------*/
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_HIGH == PORTBbits.RB6) && (RBx_FLAG_TRUE == RB6_Flag))
    {
        RB6_Flag = RBx_FLAG_FALSE;
        RB6_ISR(0); // Call the ISR function
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_LOW == PORTBbits.RB6 ) && (RBx_FLAG_FALSE == RB6_Flag))
    {
        RB6_Flag = RBx_FLAG_TRUE;
        RB6_ISR(1); // Call the ISR function
    }
    /*---------------RB7--------------------------*/
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_HIGH == PORTBbits.RB7) && (RBx_FLAG_TRUE == RB7_Flag))
    {
        RB7_Flag = RBx_FLAG_FALSE;
        RB7_ISR(0); // Call the ISR function
    }
    if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
            (GPIO_LOW == PORTBbits.RB7 ) && (RBx_FLAG_FALSE == RB7_Flag))
    {
        RB7_Flag = RBx_FLAG_TRUE;
        RB7_ISR(1); // Call the ISR function
    }
    #endif
    #endif

}
#endif
