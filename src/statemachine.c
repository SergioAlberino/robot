/*=====[Statemachine]===========================================================
 * Author Sergio Alberino <alberino@gmail.com>
 * All rights reserved.
 * Version: 1.0.0
 * Creation Date: 2020/08/14
 */
 
/*=====[Inclusion of own header]=============================================*/

#include <sapi.h>
#include <sensors.h>
#include <statemachine.h>
#include <motorDrive.h>

/*=====[Definition macros of private constants]==============================*/
#define rele LCD1
#define buzzer LCD2

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

// States
typedef enum{ 
    FORWARD,
    TURN_R,
    TURN_L,
	STOPPED,
} state_t;

typedef enum{
    goForward = LED2,
    turnLeft = LED1,
    turnRight = LEDG,
	stop = LEDB,
} leds_t;

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

int8_t  contador=0;
int8_t  pushCont=50;

/*=====[Definitions of private global variables]=============================*/

static state_t actualState;

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

void statemachineInit(void)
{
    boardInit();
    gpioInit(goForward, GPIO_OUTPUT); // se inicializan LEDs para visualizar estados
    gpioInit(turnLeft, GPIO_OUTPUT);
    gpioInit(turnRight, GPIO_OUTPUT);
    gpioInit(stop, GPIO_OUTPUT);
    gpioInit(rele, GPIO_OUTPUT);
    gpioInit(buzzer, GPIO_OUTPUT);

    sensorsInit();
    motorDriveInit();
    actualState = STOPPED;
}



static void statemachineError(void)
{
	statemachineInit();
}

void statemachineUpdate(void)
{
    static uint32_t contador = 0;

    // Update state of sensors
    sensorsUpdate();

    switch( actualState ){
        case FORWARD:
        	clean_leds();
        	gpioWrite(goForward, true );

        	gpioWrite(rele, true );
        	gpioWrite(buzzer,false);

        	// update motors
        	motorDriveUpdate(motorsFW);

        	// Check if is there an obstacle at front and not at right
            if ( valSensorF && !(valSensorR)){    // Check if is there an obstacle in front
                actualState = TURN_R;
                }
        	// Check if is there an obstacle at front and at right
            if ( valSensorF && valSensorR){    // Check if is there an obstacle in front
                actualState = TURN_L;
                }
            // if PushButton pressed go STOPPED
            if ( valPushButton){
            	contador++;
            	if ( contador >=pushCont){
            		contador=0;
            		actualState = STOPPED;
            		one_piip();
            		}
                }
        break;
        
        case TURN_R:	//Turning right
        	clean_leds();
        	gpioWrite(turnRight, true );
        	gpioWrite(rele, false );

        	// update motors
        	motorDriveUpdate(motorsTR);
         	// Check if is there an obstacle at front and at right
            if ( valSensorF && valSensorR){    // Check if is there an obstacle in front
            	actualState = TURN_L;
                }

            // If no obstacle at front, go FORWARD
            if ( !valSensorF ){
                actualState = FORWARD;
            	}


            // if PushButton pressed go STOPPED
            if ( valPushButton){
            	contador++;
            	if ( contador >=pushCont){
            		contador=0;
            		actualState = STOPPED;
            		}
                }
        break;
        
        case TURN_L:
        	clean_leds();
        	gpioWrite(turnLeft, true );
        	gpioWrite(rele, false );

        	// update motors
        	motorDriveUpdate(motorsTL);

            // If no obstacle at front, go FORWARD
            if ( !valSensorF ){
                actualState = FORWARD;
            	}
//            if ( valSensorF && !(valSensorR)){    // Check if is there an obstacle in front
//                actualState = TURN_R;
//                }

            // if PushButton pressed go STOPPED
            if ( valPushButton){
            	contador++;
            	if ( contador >=pushCont){
            		contador=0;
            		actualState = STOPPED;
            		}
                }
        break;
        
        case STOPPED:
        	clean_leds();
        	gpioWrite(stop, true );
        	gpioWrite(rele, false );

        	// update motors
        	motorDriveUpdate(motorsST);

            // if PushButton pressed go FORWARD
            if ( valPushButton){
            	contador++;
            	// only change if it is pressed some time
            	if ( contador >=pushCont){
            		contador=0;
            		double_piip();
            		actualState = FORWARD;
            		}
            	}
        break;

        default:
        	statemachineError();
        break;
    }



}

void double_piip(void)
{
	gpioWrite(buzzer, true );
	delay(200);
	gpioWrite(buzzer, false );
	delay(100);
	gpioWrite(buzzer, true );
	delay(200);
	gpioWrite(buzzer, false );
}

void one_piip(void)
{
	gpioWrite(buzzer, true );
	delay(200);
	gpioWrite(buzzer, false );

}

void clean_leds(void)
{
	gpioWrite(goForward, false );
	gpioWrite(turnLeft, false );
	gpioWrite(turnRight, false );
	gpioWrite(stop, false );

}
/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/


