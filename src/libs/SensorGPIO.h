#ifndef SensorGPIO_H
#define SensorGPIO_H
#include <Arduino.h>
#include "Sensor.h"
class SensorGPIO : public Sensor
{
protected:
  const byte pin;

public:
  SensorGPIO(byte pin);
  virtual void init() override;
  virtual bool getState() override;
};
#endif
