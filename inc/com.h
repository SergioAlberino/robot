/*=====[sensors]===========================================================
 * Author Sergio Alberino <alberino@gmail.com>
 * All rights reserved.
 * Version: 1.0.0
 * Creation Date: 2020/08/14
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _COM_H_
#define _COM_H_

//*==================[inlcusiones]============================================*/

#include <sapi.h>    // <= Biblioteca sAPI
#include <string.h>

/*==================[definiciones y macros]==================================*/

#define UART_PC        UART_USB
#define UART_BLUETOOTH UART_232

/*==================[definiciones de datos internos]=========================*/

DEBUG_PRINT_ENABLE
CONSOLE_PRINT_ENABLE

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

bool_t hm10bleTest( int32_t uart );


/*=====[Prototypes (declarations) of public functions]=======================*/

void com_init(void);
unsigned char com(void);
//void hm10blePrintATCommands( int32_t uart );

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* _SENSORS_H_ */

