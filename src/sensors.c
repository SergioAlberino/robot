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
unsigned char sensores=0x00;
int8_t  contador=0;
int8_t  pushCont=50;

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

void sensorsUpdate()
{
	valSensorF = !gpioRead( sensorF );
	valSensorR = !gpioRead( sensorR);
	valPushButton = !gpioRead( button );
}

 unsigned char sensorsUpdatex(void)
{
	static uint32_t contador = 0;
	sensores = 0;
	valSensorF = !gpioRead( sensorF );
	valSensorR = !gpioRead( sensorR);
	valPushButton = !gpioRead( button );


	if(valSensorF!= 0)
		{
		sensores=sensores | 0x01;
		}
	    else
		{
	    sensores=sensores  & 0xFE;
		}

	if(valSensorR!= 0)
		{
		sensores=sensores | 0x02;
		}
	    else
		{
	    sensores=sensores  & 0xFD;
		}

	if (valPushButton){
	           contador++;
	           if ( contador >=pushCont){
	           contador=0;
	           sensores=sensores | 0x04;
	           }
	           else
	           		{
	           	    sensores=sensores  & 0xFB;
	           		}
		}


	return sensores;
}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/
