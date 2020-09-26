#ifndef SensorGPIO_H
#define SensorGPIO_H
#include <Arduino.h>
#include "Sensor.h"
class SensorGPIO : public Sensor
{

public:
  SensorGPIO(byte pin, int _edge);
  virtual void init();
  virtual byte getState();
};
#endif