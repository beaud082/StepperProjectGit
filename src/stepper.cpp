#include "stepper.h"
#include "motor_config.h"

stepper stepperarray [] = {
  stepper(Motor1_StepPin, Motor1_DirPin, 100),
  stepper(Motor2_StepPin, Motor2_DirPin, 100)/*,
  stepper(Motor3_StepPin, Motor3_DirPin, 100),
  stepper(Motor4_StepPin, Motor4_DirPin, 100)*/
  };

void stepperSetup()
{
  stepperMovementThread = new Thread("stepper_movement", stepperMovement);
  pinMode(Motor1_DirPin, OUTPUT);
  pinMode(Motor1_StepPin, OUTPUT);
  pinMode(Motor2_DirPin, OUTPUT);
  pinMode(Motor2_StepPin, OUTPUT);
}




//////////////////////////////////////////
///    MULTITHREADING IMPLEMENTATION   ///
//////////////////////////////////////////
os_thread_return_t stepperMovement(void*)
{
    do{
    for (int i = 0; i<NUMBER_OF_MOTORS; i++)
    {
        stepperarray[i].checkCommands();
    }
    delay(threadResolution);
    }while (true);

}
//////////////////////////////////////////
/// END MULTITHREADING IMPLEMENTATION  ///
//////////////////////////////////////////




////////////////////////////////////////////
/////    STEPPER CLASS IPLEMENTATION   /////
////////////////////////////////////////////
stepper::stepper(int p1, int p2, unsigned int s)
{
    steppin = p1;
    dirpin = p2;
    speed = s;
    stepLow();
    stepstotake = 0;
    oldmillis=0;
}
void stepper::moveMotor(int s)
{
    stepstotake = s;
}
void stepper::checkCommands()
{
    if (millis() - oldmillis >= speed)
    {


      oldmillis = millis();

      if(pinstate)
      {
          stepLow();
      }

      else
      {

          if(stepstotake!=0)
          {

              if(stepstotake>0)
              {
                  takeStep();
                  stepstotake--;
              }
              else
              {
                  takeReverseStep();
                  stepstotake++;
              }
           }


       }
    }
}
void stepper::setSpeed(unsigned int s)
{
    speed = 1/s;
}
bool stepper::isBusy()
{
    if(stepstotake != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void stepper::takeStep()
{
    pinResetFast(dirpin);
    stepHigh();
}
void stepper::takeReverseStep()
{
    pinSetFast(dirpin);
    stepHigh();
}
void stepper::stepHigh()
{
    pinSetFast(steppin);
    pinstate = true;
}
void stepper::stepLow()
{
    pinResetFast(steppin);
    pinstate = false;
}
////////////////////////////////////////////
/////     END CLASS IPLEMENTATION      /////
////////////////////////////////////////////
