/*=====[motorDrive]===========================================================
 * Author Sergio Alberino <alberino@gmail.com>
 * All rights reserved.
 * Version: 1.0.0
 * Creation Date: 2020/08/14
 */
 
/*=====[Inclusion of own header]=============================================*/
#include "sapi.h"
#include <motorDrive.h>

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/
#define dir0 GPIO5
#define dir1 GPIO3
/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

bool_t valor = 0;
uint8_t  pwm1 = 180; /* 0 a 255 */
uint8_t  pwm2 = 0; /* 0 a 255 */
uint8_t  pwm3 = 200; /* 0 a 255 para el giro*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

void motorDriveInit( void )
{
	 /* Configurar PWM */
	   valor = pwmConfig( 0, PWM_ENABLE );

	   valor = pwmConfig( PWM5, PWM_ENABLE_OUTPUT );
	   valor = pwmConfig( PWM4, PWM_ENABLE_OUTPUT );
	   gpioInit(dir0, GPIO_OUTPUT);
	   gpioInit(dir1, GPIO_OUTPUT);
}

void motorDriveUpdate(motors_t motorstate)
{

    switch( motorstate ){

    	case motorsFW:
		pwmWrite( PWM5, pwm1);
	    pwmWrite( PWM4, pwm1);
		 /* ambos motores hacia adelante */
    	gpioWrite(dir0, false );
    	gpioWrite(dir1, false );
    		break;

    	case motorsTR:
	    pwmWrite( PWM5, pwm1);
	    pwmWrite( PWM4, pwm3);
		 /* motores en contramarcha */
    	gpioWrite(dir0, false );
    	gpioWrite(dir1, true );

    		break;

    	case motorsTL:
	    pwmWrite( PWM5, pwm3);
	    pwmWrite( PWM4, pwm1);
		 /* motores en contramarcha */
    	gpioWrite(dir0, true );
    	gpioWrite(dir1, false);
    		break;

    	case motorsST:
	    pwmWrite( PWM5, pwm2);
	    pwmWrite( PWM4, pwm2);
    	gpioWrite(dir0, false );
    	gpioWrite(dir1, false);
    		break;

    	default:
    		break;
    	}
}
    /**
     * @brief Comando Tabulado
     * @details Actualiza x Comando Tabulado de motores para Maquina de Estados
     * @param COM: Número de Comando
     * @param Parametro: Modificador del Comando
     */
    void SEL_COM (short COM,short Parametro)
    {

//    		if (Parametro > 255){    // Check if is there an obstacle in front
//    			Parametro = 255;
//                }

    	switch(COM)
    		{
    		case 1:
    			// Setea PWM1 y PWM2 para ir para ADELANTE
    			pwmWrite( PWM5, Parametro);
    			pwmWrite( PWM4, Parametro);
    			/* ambos motores hacia adelante */
    			gpioWrite(dir0, false );
    			gpioWrite(dir1, false );
    				break;
    		case 2:
    			// Setea PWM1 y PWM2 para girar a la Izq
    			pwmWrite( PWM5, Parametro*0.50);
    		    pwmWrite( PWM4, Parametro*0.50);
    			 /* motores en contramarcha */
    	    	gpioWrite(dir0, true );
    	    	gpioWrite(dir1, false);
    				break;
    		case 3:
    				// Setea PWM1 y PWM2 para girar a la Der
    		    pwmWrite( PWM5, Parametro*0.50);
    		    pwmWrite( PWM4, Parametro*0.50);
    			 /* motores en contramarcha */
    	    	gpioWrite(dir0, true );
    	    	gpioWrite(dir1, false);
    				break;
    		case 4:
    				// Setea PWM1 y PWM2 para RETROCEDER
    			pwmWrite( PWM5, Parametro);
    			pwmWrite( PWM4, Parametro);
    			/* ambos motores hacia adelante */
    			gpioWrite(dir0, true);
    			gpioWrite(dir1, true );
    				break;
    		case 5:
    				// Setea PWM1 y PWM2 para detenerse
    			pwmWrite( PWM5, 0);
    			pwmWrite( PWM4, 0);
    			/* ambos motores hacia adelante */
    			gpioWrite(dir0, false );
    			gpioWrite(dir1, false );
    				break;

    		default:
    			// error: comando no soportado
    				break;
    		}
}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/
