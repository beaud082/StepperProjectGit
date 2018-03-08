#include "application.h"

#ifndef STEPPER_H
#define STEPPER_H
class stepper
{
public:
    stepper(int p1, int p2, unsigned int s);
    void moveMotor(int s);
    void checkCommands();
    void setSpeed(unsigned int s);
    bool isBusy();
private:
    void takeStep();
    void takeReverseStep();
    void stepHigh();
    void stepLow();

int steppin;
int dirpin;
bool pinstate;
unsigned int speed;
unsigned int oldmillis;
int stepstotake;
};

void stepperSetup();

os_thread_return_t stepperMovement(void*);

extern Thread *stepperMovementThread;
extern stepper stepperarray [];

#endif
