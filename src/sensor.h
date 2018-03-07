#ifndef SENSOR_H
#define SENSOR_H

class sensor
{
public:
    sensor(int p);
    int getSensorReading();
    unsigned int getLastPollTime();
    void pollSensor();
    double getConvertedReading();

private:
    void capturePollTime();


unsigned int lastpolltime;
int sensorreading;
int p1;
int i;
double convertedsensorreading; //converts from input to voltage
};


#endif
