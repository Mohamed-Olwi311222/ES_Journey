/* 
 * File:   hal_ccp2_cfg.h
 * Author: Mohamed olwi
 *
 * Created on 22 October 2024, 21:37
 */
#ifndef HAL_CCP2_CFG_H
#define	HAL_CCP2_CFG_H
/*----------------------------Macros Declarations-----------------------------*/
#define CCP2_CAPTURE_MODE_CFG_SELECT           0                                    /* Precompile Config for CCP2 Compare Mode */
#define CCP2_COMPARE_MODE_CFG_SELECT           1                                    /* Precompile Config for CCP2 Capture Mode */
#define CCP2_PWM_MODE_CFG_SELECT               2                                    /* Precompile Config for CCP2 PWM Mode */
#define CCP2_SELECTED_MODE_CFG                 (CCP2_PWM_MODE_CFG_SELECT)           /* Select a Precompile Config for CCP2 Mode */

#endif	/* HAL_CCP2_CFG_H */

