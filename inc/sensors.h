/*=====[sensors]===========================================================
 * Author Sergio Alberino <alberino@gmail.com>
 * All rights reserved.
 * Version: 1.0.0
 * Creation Date: 2020/08/14
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _SENSORS_H_
#define _SENSORS_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include <sapi.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

bool_t valSensorF;
bool_t valSensorR;
bool_t valPushButton;
int8_t status;
/*=====[Prototypes (declarations) of public functions]=======================*/

void sensorsInit( void );
void sensorsUpdate(void);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* _SENSORS_H_ */

