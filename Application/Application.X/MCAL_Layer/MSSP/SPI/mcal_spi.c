/* 
 * File:   mcal_spi.c
 * Author: Mohamed olwi
 *
 * Created on 12 December 2024, 00:36
 */
#include "mcal_spi.h"

/*---------------Static Data types----------------------------------------------*/
/* SCK (Serial Clock) pin, the direction will be changed depending on the SPI mode selected */
static  pin_config_t SCK_pin = {.port = PORTC_INDEX, .pin = GPIO_PIN3};
/* SS (Slave Select) pin */
static const pin_config_t SS_pin = {.direction = GPIO_DIRECTION_INPUT, .port = PORTA_INDEX, .pin = GPIO_PIN5};
/* SDO (Serial Data Out) pin */
static const pin_config_t SDO_pin = {.direction = GPIO_DIRECTION_OUTPUT, .port = PORTC_INDEX, .pin = GPIO_PIN5};
/*---------------Static Data types End------------------------------------------*/

/*---------------Static Helper functions declerations---------------------------*/
static inline void spi_slave_mode_init(const spi_t *const spi_obj);
static inline void spi_master_mode_init(const spi_t *const spi_obj);
/*---------------Static Helper functions declerations End-----------------------*/

/**
 * @brief: Initialize the SPI module
 * @param spi_obj the SPI module object
 * @return E_OK if success otherwise E_NOT_OK
 */
Std_ReturnType spi_init(const spi_t *const spi_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == spi_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable SPI */
        SPI_SERIAL_PORT_DISABLE_CONFIG();
        /* Configure the SPI Mode */
        SPI_SET_OPERATION_MODE(spi_obj->spi_mode);
        /* Configure CLK Edge */
        if ( _SPI_TRANSITION_ACTIVE_IDLE == spi_obj->clk_edg)
        {
            SPI_TRANSITION_ACTIVE_IDLE_CONFIG();
        }
        else
        {
            SPI_TRANSITION_IDLE_ACTIVE_CONFIG();
        }
        /* Configure CLK Polarity */
        if (_SPI_IDLE_STATE_HIGH == spi_obj->clk_polarity)
        {
            SPI_IDLE_STATE_HIGH_CONFIG();
        }
        else
        {
            SPI_IDLE_STATE_LOW_CONFIG();
        }
        /* Configure Master/Slave mode SCK pin data direction and Sample time*/
        if (SPI_SLAVE_MODE_SS_ENABLED == spi_obj->spi_mode || 
                SPI_SLAVE_MODE_SS_DISABLED == spi_obj->spi_mode)
        {
            spi_slave_mode_init(spi_obj);
        }
        else
        {
            spi_master_mode_init(spi_obj);
        }
        /* Configure SDO, SS and SCK pins */
        if (gpio_pin_direction_initialize(&SDO_pin) != E_OK) ret = E_NOT_OK;
        if (gpio_pin_direction_initialize(&SS_pin) != E_OK) ret = E_NOT_OK;
        if (gpio_pin_direction_initialize(&SCK_pin) != E_OK) ret = E_NOT_OK;
        /* Enable SPI */
        SPI_SERIAL_PORT_ENABLE_CONFIG();
    }
    return (ret);
}
/**
 * @brief: Initialize the SPI Slave mode sample time and SCK pin 
 * @param spi_obj the SPI module object
 */
static inline void spi_slave_mode_init(const spi_t *const spi_obj)
{
    /* Configure Slave mode Sample time */
    /* SMP must be cleared when SPI is used in Slave mode(sample at middle) */
    SPI_SAMPLE_INPUT_MIDDLE_CONFIG();
    /* Configure SCK pin if SS is enabled*/
    if (SPI_SLAVE_MODE_SS_ENABLED == spi_obj->spi_mode)
    {
        /* SCK (Slave mode) must have TRISC<3> bit set (input) */
        SCK_pin.direction = GPIO_DIRECTION_INPUT;
    }
}
/**
 * @brief: Initialize the SPI Master mode sample time and SCK pin
 * @param spi_obj the SPI module object
 */
static inline void spi_master_mode_init(const spi_t *const spi_obj)
{
    /* Configure Master mode Sample time */
    if (_SPI_SAMPLE_INPUT_MIDDLE == spi_obj->data_input_sampe_phase)
    {
        /* Input data sampled at middle of data output time */
        SPI_SAMPLE_INPUT_MIDDLE_CONFIG();
    }
    else
    {
        /* Input data sampled at end of data output time */
        SPI_SAMPLE_INPUT_END_CONFIG();
    }
    /* Configure SCK pin */
    /* SCK (Master mode) must have TRISC<3> bit cleared */
    SCK_pin.direction = GPIO_DIRECTION_OUTPUT;
}