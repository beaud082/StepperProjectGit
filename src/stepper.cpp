#include "stepper.h"
#include "application.h"
#include "motor_config.h"

stepper stepperarray [] = {
  stepper(Motor1_StepPin, Motor1_DirPin, 100),
  stepper(Motor2_StepPin, Motor2_DirPin, 100)/*,
  stepper(Motor3_StepPin, Motor3_DirPin, 100),
  stepper(Motor4_StepPin, Motor4_DirPin, 100)*/
  };

void stepperSetup()
{
  pinMode(Motor1_DirPin, OUTPUT);
  pinMode(Motor1_StepPin, OUTPUT);
  pinMode(Motor2_DirPin, OUTPUT);
  pinMode(Motor2_StepPin, OUTPUT);
}

void motor_array_movement_backend()
{
  do{
  for (int i = 0; i<NUMBER_OF_MOTORS; i++)
  {
      stepperarray[i].stepper_backend();
  }
  delayMicroseconds(threadResolution);
  }while (true);

}



////////////////////////////////////////////
/////    STEPPER CLASS IPLEMENTATION   /////
////////////////////////////////////////////
stepper::stepper(int p1, int p2, double s)
{
    steppin = p1;
    dirpin = p2;
    speed = 500000.0/s;
    stepLow();
    stepstotake = 0;
    oldmicros=0;
}
void stepper::moveSteps(int s)
{
    stepstotake = s;
}
void stepper::moveRadians(double s)
{
    stepstotake = s*steps_per_radian;
}

void stepper::setStepsPerSecondSpeed(double s) //speed in steps per second
{
    speed = 500000.0/s;
}

void stepper::setRadiansPerSecondSpeed(double s) //speed in radians per second
{
    setStepsPerSecondSpeed(steps_per_radian*s);
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

void stepper::stepper_backend()
{
  loadNextCommand();
  runCurrentCommand();
  checkCommandCompletion();
}
void stepper::loadNextCommand()
{
  if(!isBusy())
  {
    if(!commandlist.empty())
    {

      moveRadians(commandlist[0][0]);
      setRadiansPerSecondSpeed(commandlist[0][1]);
    }
  }
}
void stepper::checkCommandCompletion()
{
  if(!isBusy())
  {
    if(!commandlist.empty())
    {
      commandlist.erase(commandlist.begin());
    }
  }
}
void stepper::runCurrentCommand()
{
    if (micros() - oldmicros >= speed)
    {
      oldmicros = micros();

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
