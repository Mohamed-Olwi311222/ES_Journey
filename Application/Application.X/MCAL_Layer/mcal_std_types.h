/* 
 * File:   mcal_std_types.h
 * Author: Mohamed olwi
 *
 * Created on April 2, 2024, 6:57 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/*----------------------------Header Files------------------------------------*/
#include "../std_types.h"
#include "../compiler.h"

/*----------------------------DataTypes---------------------------------------*/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef char sint8;
typedef short sint16;
typedef int sint32;

typedef uint8 Std_ReturnType;

/*----------------------------Macros Declarations-----------------------------*/
#define STD_HIGH        0x01    /* Physical state 5V or 3.3V */
#define STD_LOW         0x00    /* Physical state 0V */


#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01    /* Logical state active */
#define STD_IDLE        0x01    /* Logical state idle */

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK            (Std_ReturnType)0x00u
#define E_NOT_OK        (Std_ReturnType)0x01u
#endif
/*----------------------------Macros Functions Declarations-------------------*/




/*----------------------------Function Prototypes-----------------------------*/



#endif	/* MCAL_STD_TYPES_H */

