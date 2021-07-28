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
#include <MdE.h>

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
	RETURN,
	STOPPED,
} state_t;

typedef enum{
    goForward = LED2,
    turnLeft = LED1,
    turnRight = LEDG,
	stop = LEDB,
} leds_t;

unsigned char INPUT1=0x00,INPUT2=0x00;
unsigned char STATE= 0x00;
unsigned char COM=1,Parametro=0;

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/
int8_t  i=0;

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

//void statemachineUpdatex(void)
//{
//    static uint32_t contador = 0;
//
//    // Update state of sensors
//    sensorsUpdate();
//
//    switch( actualState ){
//        case FORWARD:
//        	clean_leds();
//        	gpioWrite(goForward, true );
//        	gpioWrite(rele, true );
//
//        	// update motors
//        	//motorDriveUpdate(motorsFW);
//        	SEL_COM(1,180);
//
//        	// Check if is there an obstacle at front and not at right
//            if ( valSensorF && !(valSensorR)){    // Check if is there an obstacle in front
//                actualState = TURN_R;
//                }
//        	// Check if is there an obstacle at front and at right
//            if ( valSensorF && valSensorR){    // Check if is there an obstacle in front
//                actualState = TURN_L;
//                }
//            // if PushButton pressed go STOPPED
//            if ( valPushButton){
//            	contador++;
//            	if ( contador >=pushCont){
//            		contador=0;
//            		actualState = STOPPED;
//            		one_piip();
//            		}
//                }
//        break;
//
//        case TURN_R:	//Turning right
//        	clean_leds();
//        	gpioWrite(turnRight, true );
//        	gpioWrite(rele, false );
//
//        	// update motors
//        	//motorDriveUpdate(motorsTR);
//        	SEL_COM(2,180);
//
//         	// Check if is there an obstacle at front and at right
//            if ( valSensorF && valSensorR){    // Check if is there an obstacle in front
//            	actualState = TURN_L;
//                }
//
//            // If no obstacle at front, go FORWARD
//            if ( !valSensorF ){
//                actualState = FORWARD;
//            	}
//
//
//            // if PushButton pressed go STOPPED
//            if ( valPushButton){
//            	contador++;
//            	if ( contador >=pushCont){
//            		contador=0;
//            		actualState = STOPPED;
//            		}
//                }
//        break;
//
//        case TURN_L:
//        	clean_leds();
//        	gpioWrite(turnLeft, true );
//        	gpioWrite(rele, false );
//
//        	// update motors
//        	motorDriveUpdate(motorsTL);
//
//            // If no obstacle at front, go FORWARD
//            if ( !valSensorF ){
//                actualState = FORWARD;
//            	}
////            if ( valSensorF && !(valSensorR)){    // Check if is there an obstacle in front
////                actualState = TURN_R;
////                }
//
//            // if PushButton pressed go STOPPED
//            if ( valPushButton){
//            	contador++;
//            	if ( contador >=pushCont){
//            		contador=0;
//            		actualState = STOPPED;
//            		}
//                }
//        break;
//
//        case STOPPED:
//        	clean_leds();
//        	gpioWrite(stop, true );
//        	gpioWrite(rele, false );
//
//        	// update motors
//        	//motorDriveUpdate(motorsST);
//        	SEL_COM(5,180);
//
//            // if PushButton pressed go FORWARD
//            if ( valPushButton){
//            	contador++;
//            	// only change if it is pressed some time
//            	if ( contador >=pushCont){
//            		contador=0;
//            		double_piip();
//            		actualState = FORWARD;
//            		}
//            	}
//        break;
//
//        default:
//        	statemachineError();
//        break;
//    }
//
//}
    void statemachineUpdate(void)
    {
        // Update state of sensors
        INPUT2 = sensorsUpdatex();
        // *************** Rutina MdE. recorre la tabla, hasta que encuentra un Estado FF *****************
        	i=0;
        	while(Planilla[i][0]!=0xFF)
        			{
        			if(STATE == Planilla[i][0] )
        			{
        				// coincide la entrada con la combinación de la Planilla?
                if(Planilla[i][2] == INPUT2)
        					{
        						send_com(Planilla[i][3], Planilla[i][4], Planilla[i][5], STATE);
        						STATE= Planilla[i][5];
        						break; // sale del while porque encontró el ESTADO y la condición coincidente en la TABLA
        					}
        			}
             i++;
             }
                 // ********************** Fin rutina Maquina de Estados ********************************

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

void send_com(short COM,short Parametro, short STATENEW, short STATE )
{
	set_leds(COM);
	SEL_COM (COM,Parametro);
	if (STATENEW==0 & STATE==1)
			{
			double_piip();
			}
	if (STATENEW==1 & STATE==0)
			{
			one_piip();
			}

}

void clean_leds(void)
{
	gpioWrite(goForward, false );
	gpioWrite(turnLeft, false );
	gpioWrite(turnRight, false );
	gpioWrite(stop, false );

}
void set_leds(unsigned char COM)
{
	clean_leds();

	 switch(COM){

	    case 1:
	    	gpioWrite(goForward, true );
	    		break;
	    case 2:
	    	gpioWrite(turnRight, true );
	    		break;
	    case 3:
	    	gpioWrite(turnLeft, true );
	    		break;
	    case 4:
	    	gpioWrite(goForward, true );
	    		break;
	    case 5:
	    	gpioWrite(stop, true );
	    		break;
	    	default:
	    		break;
	    	}

}
/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/


