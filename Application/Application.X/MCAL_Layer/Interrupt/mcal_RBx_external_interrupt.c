/* 
 * File:   mcal_RBx_external_interrupt.c
 * Author: Mohamed olwi
 *
 * Created on 10 August 2024, 08:00 AM
 */
#include "mcal_external_interrupt.h"

/*----------------------Static Declerations----------------------------------------------------------------*/
/*----------------------RBx interrupt on change static functions declerations----*/
#if EXTERNAL_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE

#if EXTERNAL_INTERRUPT_ONChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

static INTERRUPT_HANDLER RB4_ISRS[RBx_INTERRUPT_HANDLERS_LEN];
static INTERRUPT_HANDLER RB5_ISRS[RBx_INTERRUPT_HANDLERS_LEN];
static INTERRUPT_HANDLER RB6_ISRS[RBx_INTERRUPT_HANDLERS_LEN];
static INTERRUPT_HANDLER RB7_ISRS[RBx_INTERRUPT_HANDLERS_LEN];

static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Set_Interrupt_Handler(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
/*----------------------Functions Implementations----------------------------------------------------------*/

/*-----------------------RBx Interrupt On change-----------------------------------------------------------*/
/*----------------------RBx interrupt on change functions------------------------*/

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
        ret |= E_NOT_OK;
    }
    else
    {      
        /*Disable the RBx Interrupt*/
        EXT_RBx_INTERRUPT_DISABLE();
        /*Clear Interrupt Flag*/
        EXT_RBx_INTERRUPT_FLAG_BIT_CLEAR();
        /*Configure the External Interrupt priority*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret |= Interrupt_RBx_Priority_Init(int_obj);
#endif
        /*Initialize the pin of the RB*/
        ret |= Interrupt_RBx_Pin_Init(int_obj);
        /*Set the handler of the RBx pin*/
        ret |= Interrupt_RBx_Set_Interrupt_Handler(int_obj);
        /*Enable the RBx interrupt*/
        Interrupt_RBx_Enable(int_obj);
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
        EXT_RBx_INTERRUPT_FLAG_BIT_CLEAR();
        EXT_RBx_INTERRUPT_DISABLE();
    }
    return (ret);
}
/*----------------------Helper functions for RBx interrupt on change-------------*/
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
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if (INTERRUPT_LOW_PRIORITY == int_obj->priority)
        {
            /*Enable high priority so the low priority can be enabled*/
            INTERRUPT_Global_interrupt_HIGH_ENABLE();
            INTERRUPT_Global_interrupt_LOW_ENABLE();
            EXT_RBx_INTERRUPT_LOW_PRIORITY();
        }
        else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority)
        {
            INTERRUPT_Global_interrupt_HIGH_ENABLE();
            EXT_RBx_INTERRUPT_HIGH_PRIORITY();
        }
        else
        {
            ret |= E_NOT_OK;
        }
#endif
    }
    return (ret);
}
#endif
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
        switch(int_obj->mcu_pin.pin)
         {
            case GPIO_PIN4 :
                ret = gpio_pin_initialize(&(int_obj->mcu_pin));
                break;
            case GPIO_PIN5 :
                ret = gpio_pin_initialize(&(int_obj->mcu_pin));
                break;
            case GPIO_PIN6 : 
                ret = gpio_pin_initialize(&(int_obj->mcu_pin));
                break;
            case GPIO_PIN7:
                ret = gpio_pin_initialize(&(int_obj->mcu_pin));
                break;
            default : 
                ret = E_NOT_OK;
                break;
         }
    }
    return (ret); 
}
/**
 * @brief A helper function to enable RBx interrupt on change
 * @param int_obj the RBx interrupt on change object
 * @return E_OK if success otherwise E_NOT_OK
 */
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (NULL == int_obj)
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
        EXT_RBx_INTERRUPT_ENABLE();
    }
    return (ret);   
}

/*----------------------Helper functions for RBx Interrupt Handler--------------*/

/**
 * @brief A helper function to set each RBx its each handler depending on the value of its pin
 * @param int_obj the RBx interrupt on change object
 * @return E_OK if success otherwise E_NOT_OK 
 */
static Std_ReturnType Interrupt_RBx_Set_Interrupt_Handler(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;

    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->mcu_pin.pin)
         {
            case GPIO_PIN4 :
                RB4_ISRS[RBx_ISR_HIGH] = int_obj->EXT_interrupt_handler_High;
                RB4_ISRS[RBx_ISR_LOW] = int_obj->EXT_interrupt_handler_Low;
                break;
            case GPIO_PIN5 : 
                RB5_ISRS[RBx_ISR_HIGH] = int_obj->EXT_interrupt_handler_High;
                RB5_ISRS[RBx_ISR_LOW] = int_obj->EXT_interrupt_handler_Low;
                break;
            case GPIO_PIN6 : 
                RB6_ISRS[RBx_ISR_HIGH] = int_obj->EXT_interrupt_handler_High;
                RB6_ISRS[RBx_ISR_LOW] = int_obj->EXT_interrupt_handler_Low;
                break;
            case GPIO_PIN7:
                RB7_ISRS[RBx_ISR_HIGH] = int_obj->EXT_interrupt_handler_High;
                RB7_ISRS[RBx_ISR_LOW] = int_obj->EXT_interrupt_handler_Low;
                break;
            default : 
                ret = E_NOT_OK;
                break;
         }
    }
    return (ret);  
}

/*----------------------ISRs for RBx--------------------------------------------*/

/**
 * @brief The interrupt service routine of RB4, will be called if RB4 on change interrupt has been raised depending on
 * the logic of the pin
 * @param source the source of the calling from the interrupt manager
 */
void RB4_ISR(uint8 source)
{
    /*Clear Flagbit of RB4*/
    EXT_RBx_INTERRUPT_FLAG_BIT_CLEAR();
    /*Code*/

    /*Callback function*/
    if (0 == source)
    {
        if (RB4_ISRS[RBx_ISR_HIGH])
        {
            RB4_ISRS[RBx_ISR_HIGH]();
        }
    }
    else
    {
        if (RB4_ISRS[RBx_ISR_LOW])
        {
            RB4_ISRS[RBx_ISR_LOW]();
        } 
    }
}

/**
 * @brief The interrupt service routine of RB5, will be called if RB4 on change interrupt has been raised depending on
 * the logic of the pin
 * @param source the source of the calling from the interrupt manager
 */
void RB5_ISR(uint8 source)
{
    /*Clear Flag bit of RB4*/
    EXT_RBx_INTERRUPT_FLAG_BIT_CLEAR();
    /*Code*/

    /*Callback function*/
    if (0 == source)
    {
        if (RB5_ISRS[RBx_ISR_HIGH])
        {
            RB5_ISRS[RBx_ISR_HIGH]();
        }
    }
    else
    {
        if (RB5_ISRS[RBx_ISR_LOW])
        {
            RB5_ISRS[RBx_ISR_LOW]();
        } 
    }
}

/**
 * @brief The interrupt service routine of RB6, will be called if RB4 on change interrupt has been raised depending on
 * the logic of the pin
 * @param source the source of the calling from the interrupt manager
 */
void RB6_ISR(uint8 source)
{
    /*Clear Flag bit of RB4*/
    EXT_RBx_INTERRUPT_FLAG_BIT_CLEAR();
    /*Code*/

    /*Callback function*/
    if (0 == source)
    {
        if (RB6_ISRS[RBx_ISR_LOW])
        {
            RB6_ISRS[RBx_ISR_LOW]();
        }
    }
    else
    {
        if (RB6_ISRS[RBx_ISR_HIGH])
        {
            RB6_ISRS[RBx_ISR_HIGH]();
        } 
    }
}

/**
 * @brief The interrupt service routine of RB7, will be called if RB4 on change interrupt has been raised depending on
 * the logic of the pin
 * @param source the source of the calling from the interrupt manager
 */
void RB7_ISR(uint8 source)
{
    /*Clear Flag bit of RB4*/
    EXT_RBx_INTERRUPT_FLAG_BIT_CLEAR();
    /*Code*/

    /*Callback function*/
    if (0 == source)
    {
        if (RB7_ISRS[RBx_ISR_LOW])
        {
            RB7_ISRS[RBx_ISR_LOW]();
        }
    }
    else
    {
        if (RB7_ISRS[RBx_ISR_HIGH])
        {
            RB7_ISRS[RBx_ISR_HIGH]();
        } 
    }
}
#endif

#endif

