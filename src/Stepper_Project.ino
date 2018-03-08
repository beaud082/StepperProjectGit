
#include "stepper.h"
Thread *stepperthread;

void setup() {
stepperSetup();
stepperthread = new Thread("stepper_movement", stepperMovement);
}

void loop()
{
    delay(10);
}

os_thread_return_t stepperMovement(void*)
{

  motor_array_movement_backend();

}
