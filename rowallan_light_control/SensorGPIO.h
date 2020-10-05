#ifndef SensorGPIO_H
#define SensorGPIO_H
#include <Arduino.h>
#include "Sensor.h"
class SensorGPIO : public Sensor
{

public:
  SensorGPIO(byte pin, byte _edge);
  virtual void init();
  virtual bool getState();
};
#endif