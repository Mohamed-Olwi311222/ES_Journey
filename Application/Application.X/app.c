/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "MCAL_Layer/ADC/hal_adc.h"

void adc_interrupt_handler(void);
volatile uint16 adc_flag = 0;
adc_conversion_result adc_result1 = ZERO_INIT;

adc_config_t adc = {
  .adc_interrupt_handler = adc_interrupt_handler,
  .priortiy = INTERRUPT_HIGH_PRIORITY,
  .aquisition_time = ADC_ACQUISITION_TIME_12_TAD,
  .adc_analog_channel = ADC_CHANNEL_AN0,
  .adc_port_config = ADC_AN0__AN3__ANALOG_FUNCTIONALITY,
  .conversion_clock = ADC_CONVERSION_CLOCK_FOSC16,
  .result_format = ADC_RES_RIGHT_JUSTIFY,
  .voltage_ref = ADC_VREF_INTENAL
};

void adc_interrupt_handler(void)
{
    adc_flag++;
    adc_read_result(&adc, &adc_result1);
}
int main(void)
{
    Std_ReturnType ret = application_init();

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret |= adc_init(&adc);
    while(1)
    {
        ret |= adc_get_conversion_interrupt(&adc, ADC_CHANNEL_AN0);
    }
   return (0);
}
Std_ReturnType application_init(void)
{
    Std_ReturnType ret = E_OK;
    ret = ecu_layer_initialize();

    return (ret);
}
