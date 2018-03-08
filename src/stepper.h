#ifndef STEPPER_H
#define STEPPER_H
#include <vector>
#include <array>
class stepper
{
public:
    stepper(int p1, int p2, double s);
    void moveSteps(int s);
    void moveRadians(double s);
    void stepper_backend();
    void setStepsPerSecondSpeed(double s);
    void setRadiansPerSecondSpeed(double s);
    bool isBusy();
private:
    void runCurrentCommand();
    void loadNextCommand();
    void checkCommandCompletion();
    void takeStep();
    void takeReverseStep();
    void stepHigh();
    void stepLow();

int steppin;
int dirpin;
bool pinstate;
unsigned long speed;
unsigned long oldmicros;
int stepstotake;
std::vector<std::array<double,2>> commandlist;
};

void stepperSetup();

void motor_array_movement_backend();

extern stepper stepperarray [];

#endif
