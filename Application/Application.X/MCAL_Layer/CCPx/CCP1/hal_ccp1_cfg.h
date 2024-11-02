/* 
 * File:   hal_ccp1_cfg.h
 * Author: Mohamed olwi
 *
 * Created on 22 October 2024, 21:37
 */
#ifndef HAL_CCP1_CFG_H
#define	HAL_CCP1_CFG_H
/*----------------------------Macros Declarations-----------------------------*/
#define CCP1_CAPTURE_MODE_CFG_SELECT           0                                    /* Precompile Config for CCP2 Compare Mode */
#define CCP1_COMPARE_MODE_CFG_SELECT           1                                    /* Precompile Config for CCP2 Capture Mode */
#define CCP1_PWM_MODE_CFG_SELECT               2                                    /* Precompile Config for CCP2 PWM Mode */
#define CCP1_SELECTED_MODE_CFG                 (CCP1_CAPTURE_MODE_CFG_SELECT)           /* Select a Precompile Config for CCP1 Mode */

#endif	/* HAL_CCP1_CFG_H */

