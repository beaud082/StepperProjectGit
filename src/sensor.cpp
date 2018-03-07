
#include "application.h"
#include "sensor.h"

sensor::sensor(int p)
{
  p1 = p;
}

int sensor::getSensorReading()
{
  return sensorreading;
}

unsigned int sensor::getLastPollTime()
{
  return lastpolltime;
}

void sensor::pollSensor()
{
  capturePollTime();
  sensorreading = analogRead(p1);
}
void sensor::capturePollTime()
{
  lastpolltime=millis();
}
double sensor::getConvertedReading()
{
  return convertedsensorreading = 0.000806* (double) getSensorReading();

}
