////
#include "stepper.h"
//Thread *stepperMovementThread1;


void setup() {
stepperSetup();
//stepperMovementThread1 = new Thread("stepper_movement1", stepperMovement1);
}

void loop()
{
    delay(10);
}

/*os_thread_return_t stepperMovement1(void*)
{
    do{
    for (int i = 0; i<NUMBER_OF_MOTORS; i++)
    {
        stepperarray[i].checkCommands();
    }
    delay(1);
    }while (true);

}
*/
