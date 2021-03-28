/*=====[sensors]===========================================================
 * Author Sergio Alberino <alberino@gmail.com>
 * All rights reserved.
 * Version: 1.0.0
 * Creation Date: 2020/08/14
 */
 
/*=====[Inclusion of own header]=============================================*/

#include <sensors.h>

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/


#define sensorF GPIO0
#define sensorR GPIO1
#define button TEC1

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

void sensorsInit( void )
{
    gpioInit(sensorF, GPIO_INPUT);
    gpioInit(sensorR, GPIO_INPUT);
    gpioInit(button, GPIO_INPUT);
}

void sensorsUpdate( void)
{
	valSensorF = !gpioRead( sensorF );
	valSensorR = !gpioRead( sensorR);
	valPushButton = !gpioRead( button );
}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/
