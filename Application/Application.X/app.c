/*
 * File:   app.c
 * Author: Mohamed olwi
 *
 * Created on April 1, 2024, 4:43 PM
 */
#include "app.h"
#include "MCAL_Layer/ADC/hal_adc.h"

adc_config_t adc = {
  .adc_interrupt_handler = NULL,
  .aquisition_time = ADC_ACQUISITION_TIME_12_TAD,
  .adc_analog_channel = ADC_CHANNEL_AN0,
  .adc_port_config = ADC_AN0__AN3__ANALOG_FUNCTIONALITY,
  .conversion_clock = ADC_CONVERSION_CLOCK_FOSC16,
  .result_format = ADC_RES_RIGHT_JUSTIFY,
  .voltage_ref = ADC_VREF_INTENAL
};
led_t led1 = {
  .led_status = LED_OFF,
  .port_name = PORTC_INDEX,
  .pin = GPIO_PIN0
};
int main(void)
{
    Std_ReturnType ret = application_init();
    adc_conversion_result adc_result1 = ZERO_INIT;
    adc_conversion_result adc_result2 = ZERO_INIT;
    adc_conversion_result adc_result3 = ZERO_INIT;
    adc_conversion_result adc_result4 = ZERO_INIT;

    if (E_NOT_OK == ret)
    {
        return (-1);
    }
    ret |= adc_init(&adc);
    ret |= led_initialize(&led1); 
    while(1)
    {
        ret |= adc_get_conversion(&adc, ADC_CHANNEL_AN0, &adc_result1);
        ret |= adc_get_conversion(&adc, ADC_CHANNEL_AN1, &adc_result2);
        ret |= adc_get_conversion(&adc, ADC_CHANNEL_AN2, &adc_result3);
        ret |= adc_get_conversion(&adc, ADC_CHANNEL_AN3, &adc_result4);

    }
   return (0);
}
Std_ReturnType application_init(void)
{
    Std_ReturnType ret = E_OK;
    ret = ecu_layer_initialize();

    return (ret);
}
