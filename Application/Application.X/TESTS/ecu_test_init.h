/* 
 * File:   ecu_test_init.h
 * Author: Mohamed olwi
 *
 * Created on 10 July 2024, 17:58
 */

#ifndef ECU_TEST_INIT_H
#define	ECU_TEST_INIT_H
/*----------------------------Header Files------------------------------------*/
#include "../ECU_Layer/led/ecu_led.h"
#include "../ECU_Layer/button/ecu_button.h"
#include "../ECU_Layer/Relay/ecu_relay.h"
#include "../ECU_Layer/DC_Motor/ecu_dc_motor.h"
#include "../ECU_Layer/seven_seg/ecu_seven_seg.h"
#include "../ECU_Layer/keypad/ecu_keypad.h"
#include "../ECU_Layer/Char_LCD/ecu_char_lcd.h"
#include "../MCAL_Layer/ADC/hal_adc.h"
#include "../MCAL_Layer/Timers/Timer0/hal_timer0.h"
#include "../MCAL_Layer/Timers/Timer1/hal_timer1.h"
#include "../MCAL_Layer/Timers/Timer2/hal_timer2.h"
#include "../MCAL_Layer/Timers/Timer3/hal_timer3.h"
#include "../MCAL_Layer/CCP1/hal_ccp1.h"
#include "../MCAL_Layer/CCP2/hal_ccp2.h"
/*----------------------------Macros Declarations-----------------------------*/

/*----------------------------Macros Functions Declarations-------------------*/

/*----------------------------DataTypes---------------------------------------*/
extern char_lcd_4bit_t lcd_1;
extern char_lcd_8bit_t lcd_2;
/*----------------------------Function Prototypes-----------------------------*/
Std_ReturnType ecu_char_lcd_initialize(void);

#endif	/* ECU_TEST_INIT_H */

