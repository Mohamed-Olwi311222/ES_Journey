/* 
 * File:   hal_eusart_cfg.h
 * Author: Mohamed olwi
 *
 * Created on 12 November 2024, 21:47
 */

#ifndef HAL_EUSART_CFG_H
#define	HAL_EUSART_CFG_H
/*----------------------------Macros Declarations-----------------------------*/
#define EUSART_SYNC_MODE                    1                           /* EUSART SYNC MODE */
#define EUSART_ASYNC_MODE                   0                           /* EUSART ASYNC MODE */
#define EUSART_ACTIVE_MODE                  (EUSART_ASYNC_MODE)         /* Which EUSART mode is active */
#if EUSART_ACTIVE_MODE == EUSART_SYNC_MODE
#define EUSART_SYNC_MASTER_MODE             1                           /* EUSART SYNC MODE MASTER */
#define EUSART_SYNC_SLAVE_MODE              0                           /* EUSART SYNC MODE SLAVE */
#define EUSART_SYNC_MODE                    (EUSART_SYNC_MASTER_MODE)   /* Which sync mode is active */
#endif
#endif	/* HAL_EUSART_CFG_H */

