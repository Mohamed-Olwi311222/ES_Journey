/* 
 * File:   mcal_external_interrupt.c
 * Author: Mohamed olwi
 *
 * Created on 01 August 2024, 06:51
 */
#include "mcal_external_interrupt.h"

static void (*INT0_INTERRUPT_HANDLER) (void) = NULL;    /*Pointer to the callback function of INT0*/
static void (*INT1_INTERRUPT_HANDLER) (void) = NULL;    /*Pointer to the callback function of INT1*/
static void (*INT2_INTERRUPT_HANDLER) (void) = NULL;    /*Pointer to the callback function of INT2*/

static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t * int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);


static Std_ReturnType INT0_Set_Interrupt_Handler(void (*Interrupt_Handler) (void));
static Std_ReturnType INT1_Set_Interrupt_Handler(void (*Interrupt_Handler) (void));
static Std_ReturnType INT2_Set_Interrupt_Handler(void (*Interrupt_Handler) (void));
static Std_ReturnType Interrupt_INTx_Set_Interrupt_Handler(const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t * int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
/**
 * @brief: A software interface to initialize the given external INTx interrupt
 * @param int_obj the external INTx interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Disable the External Interrupt*/
        ret |= Interrupt_INTx_Disable(int_obj);
        /*Clear Interrupt Flag*/
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        /*Configure the External Interrupt edge*/
        ret |= Interrupt_INTx_Edge_Init(int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /*Configure the External Interrupt priority*/
        ret |= Interrupt_INTx_Priority_Init(int_obj);
#endif
        /*Configure the External Interrupt I/O pin*/
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        /*Configure the Default Interrupt Callback*/
        ret |= Interrupt_INTx_Set_Interrupt_Handler(int_obj);
        /*Enable the External Interrupt*/
        ret |= Interrupt_INTx_Enable(int_obj);
    }
    return (ret);
}

/**
 * @brief: A software interface to deinitialize the given external INTx interrupt
 * @param int_obj the external INTx interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Interrupt_INTx_Deinit(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return (ret);
}

/**
 * @brief: A software interface to initialize the PORTB on change interrupt
 * @param int_obj the PORTB on change interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {

    }
    return (ret);
}

/**
 * @brief: A software interface to deinitialize the PORTB on change interrupt
 * @param int_obj the PORTB on change interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType Interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {

    }
    return (ret);
}
/*----------------------Helper functions for INTx interrupt------------------------------------------------*/
/**
 * @brief: A helper function to enable the INTx interrupt
 * @param int_obj the INTx interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if (int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
/*If interrupt priority levels is disabled, the mcu will run in compatibility mode*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_DISABLE
        INTERRUPT_Peripheral_interrupt_ENABLE();
        INTERRUPT_Global_interrupt_ENABLE();
#else
        INTERRUPT_PRIORITY_levels_ENABLE(); /*Enable priority feature*/
#endif
        switch(int_obj->source)
        {
            /*---------INT0------------*/
            case INTERRUPT_EXTERNAL_INT0 :
                /*Its always high priority*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Global_interrupt_HIGH_ENABLE();
                EXT_INT0_INTERRUPT_ENABLE();
#else
                EXT_INT0_INTERRUPT_ENABLE();
#endif
                break;
            /*---------INT1------------*/
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority)
                {
                    INTERRUPT_Global_interrupt_HIGH_ENABLE();
                    INTERRUPT_Global_interrupt_LOW_ENABLE();
                    EXT_INT1_INTERRUPT_ENABLE();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                    INTERRUPT_Global_interrupt_HIGH_ENABLE();
                    EXT_INT1_INTERRUPT_ENABLE();
                }
                else
                {
                    ret = E_NOT_OK;
                }
#else
                EXT_INT1_INTERRUPT_ENABLE();
#endif
                break;
            /*---------INT2------------*/
            case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority)
                {
                    INTERRUPT_Global_interrupt_HIGH_ENABLE();
                    INTERRUPT_Global_interrupt_LOW_ENABLE();
                    EXT_INT2_INTERRUPT_ENABLE();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                    INTERRUPT_Global_interrupt_HIGH_ENABLE();
                    EXT_INT2_INTERRUPT_ENABLE();
                }
                else
                {
                    ret = E_NOT_OK;
                }
#else
                EXT_INT2_INTERRUPT_ENABLE();
#endif
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return (ret);
}
/**
 * @brief: A helper function to disable the INTx interrupt
 * @param int_obj the INTx interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_INTERRUPT_DISABLE();
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_INTERRUPT_DISABLE();
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_INTERRUPT_DISABLE(); 
                break;
            default : 
                ret = E_NOT_OK;
                break;
        }
    }
    return (ret);
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief: A helper function to initialize the interrupt priority of the INTx interrupt
 * @param int_obj the INTx interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            /*Its always high priority*/
            case INTERRUPT_EXTERNAL_INT0:
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority)
                {
                    EXT_INT1_LOW_PRIORITY();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {
                    EXT_INT1_HIGH_PRIORITY();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority)
                {

                    EXT_INT2_LOW_PRIORITY();
                }
                else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority)
                {

                    EXT_INT2_HIGH_PRIORITY();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            default : 
                ret = E_NOT_OK;
                break;
        }
    }
    return (ret);
}
#endif
/**
 * @brief: A helper function to initalize the edge of the INTx interrupt
 * @param int_obj the INTx interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
        {
            case INTERRUPT_EXTERNAL_INT0 :
                if (INTERRUPT_RISING_EDGE == int_obj->edge)
                {
                    EXT_INT0_ON_RISING_EDGE();
                }
                else if(INTERRUPT_FALLING_EDGE == int_obj->edge)
                {
                    EXT_INT0_ON_FALLING_EDGE();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if (INTERRUPT_RISING_EDGE == int_obj->edge)
                {
                    EXT_INT1_ON_RISING_EDGE();
                }
                else if(INTERRUPT_FALLING_EDGE == int_obj->edge)
                {
                    EXT_INT1_ON_FALLING_EDGE();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if (INTERRUPT_RISING_EDGE == int_obj->edge)
                {
                    EXT_INT2_ON_RISING_EDGE();
                }
                else if(INTERRUPT_FALLING_EDGE == int_obj->edge)
                {
                    EXT_INT2_ON_FALLING_EDGE();
                }
                else
                {
                    ret = E_NOT_OK;
                }
                break;
            default : 
                ret = E_NOT_OK;
                break;
        }
    }
    return (ret);
}
/**
 * @brief: A helper function to Initialize the pin of the INTx interrupt
 * @param int_obj the INTx interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_initialize(&(int_obj->mcu_pin));
    }
    return (ret);
}
/**
 * @brief: A helper function to clear the flag of the given interrupt
 * @param int_obj the INTx interrupt object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
         switch(int_obj->source)
         {
            case INTERRUPT_EXTERNAL_INT0 :
                EXT_INT0_INTERRUPT_FLAG_BIT_CLEAR();
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_INTERRUPT_FLAG_BIT_CLEAR();
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_INTERRUPT_FLAG_BIT_CLEAR();
                break;
            default : 
                ret = E_NOT_OK;
                break;
         }
    }
    return (ret); 
}
/*----------------------Helper functions for RBx interrupt on change---------------------------------------*/

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief A helper function to initialize the interrupt priority of RBx on change interrupt
 * @param int_obj the RBx interrupt on change object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return (ret);
}
#endif
/**
 * @brief A helper function to enable RBx interrupt on change
 * @param int_obj the RBx interrupt on change object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t * int_obj)
{
    Std_ReturnType ret = E_OK;

    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return (ret);   
}
/**
 * @brief A helper function to disable RBx interrupt on change
 * @param int_obj the RBx interrupt on change object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return (ret);   
}
/**
 * @brief A helper function to initialize the pin of RBx interrupt on change
 * @param int_obj the RBx interrupt on change object
 * @return E_OK if success otherwise E_NOT_OK 
 */
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return (ret); 
}
/*----------------------Helper functions for Interrupt Handler---------------------------------------------*/

/**
 * @brief A helper function to set the interrupt handler of INT0 external interrupt
 * @param Interrupt_Handler the interrupt handler to set the INT0 handler
 * @return E_OK if success otherwise E_NOT_OK 
 */
static Std_ReturnType INT0_Set_Interrupt_Handler(void (*Interrupt_Handler) (void))
{
    Std_ReturnType ret = E_OK;

    if (NULL ==Interrupt_Handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_INTERRUPT_HANDLER = Interrupt_Handler;
    }
    return (ret);
}
/**
 * @brief A helper function to set the interrupt handler of INT1 external interrupt
 * @param Interrupt_Handler the interrupt handler to set the INT1 handler
 * @return E_OK if success otherwise E_NOT_OK 
 */
static Std_ReturnType INT1_Set_Interrupt_Handler(void (*Interrupt_Handler) (void))
{
    Std_ReturnType ret = E_OK;

    if (NULL ==Interrupt_Handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_INTERRUPT_HANDLER = Interrupt_Handler; 
    }
    return (ret);
}
/**
 * @brief A helper function to set the interrupt handler of INT2 external interrupt
 * @param Interrupt_Handler the interrupt handler to set the INT2 handler
 * @return E_OK if success otherwise E_NOT_OK 
 */
static Std_ReturnType INT2_Set_Interrupt_Handler(void (*Interrupt_Handler) (void))
{
    Std_ReturnType ret = E_OK;

    if (NULL ==Interrupt_Handler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_INTERRUPT_HANDLER = Interrupt_Handler; 
    }
    return (ret);
}
/**
 * @brief A helper function to set each INTx its each handler depending on the value of the initialization
 * @param int_obj the external interrupt object
 * @return E_OK if success otherwise E_NOT_OK 
 */
static Std_ReturnType Interrupt_INTx_Set_Interrupt_Handler(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source)
         {
            case INTERRUPT_EXTERNAL_INT0 :
                ret = INT0_Set_Interrupt_Handler(int_obj->EXT_interrupt_handler);
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                ret = INT1_Set_Interrupt_Handler(int_obj->EXT_interrupt_handler);
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                ret = INT2_Set_Interrupt_Handler(int_obj->EXT_interrupt_handler);
                break;
            default : 
                ret = E_NOT_OK;
                break;
         }
    }
    return (ret);  
}

/*----------------------ISRs for INTx----------------------------------------------------------------------*/

/**
 * @brief: The interrupt service routine of INT0, will be called if INT0 interrupt has been raised
 */
void INT0_ISR(void)
{
    /*Clear Flagbit of INT0*/
    EXT_INT0_INTERRUPT_FLAG_BIT_CLEAR();
    /*Code*/

    /*Callback function*/
    if (INT0_INTERRUPT_HANDLER)
    {
        INT0_INTERRUPT_HANDLER();
    }
}

/**
 * @brief: The interrupt service routine of INT0, will be called if INT0 interrupt has been raised
 */
void INT1_ISR(void)
{
    /*Clear Flagbit of INT0*/
    EXT_INT1_INTERRUPT_FLAG_BIT_CLEAR();
    /*Code*/

    /*Callback function*/
    if (INT1_INTERRUPT_HANDLER)
    {
        INT1_INTERRUPT_HANDLER();
    }
}

/**
 * @brief: The interrupt service routine of INT0, will be called if INT0 interrupt has been raised
 */
void INT2_ISR(void)
{
    /*Clear Flagbit of INT0*/
    EXT_INT2_INTERRUPT_FLAG_BIT_CLEAR();
    /*Code*/

    /*Callback function*/
    if (INT2_INTERRUPT_HANDLER)
    {
        INT2_INTERRUPT_HANDLER();
    }
}