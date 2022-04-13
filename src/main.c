/*=============================================================================
 * Author Sergio Alberino <alberino@gmail.com>
 * All rights reserved.
 * Date: 2020/08/11
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "statemachine.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

// Periodicidad de ejecucion de la FSM

#define SM_PERIODICITY  20

/*=====[Definitions of public data types]====================================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main(void)
{
   // ----- Setup -----------------------------------
    delay_t sm;
delayInit( &sm, SM_PERIODICITY );
    
    statemachineInit();

   // ----- Repeat for ever -------------------------
   while( true ) {
        if( delayRead(&sm) ){
        	statemachineUpdate();
        }
    }
    
   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
