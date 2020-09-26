#ifndef SensorI2C_H
#define SensorI2C_H
#include <Arduino.h>
#include "I2CWrapper.h"
#include "Sensor.h"
class SensorI2C : public Sensor
{

private:
  I2CWrapper *i2c;
  int DEPRESSED = 0;

public:
  SensorI2C(I2CWrapper *_i2c, byte pin, int _edge);
  virtual void init();
  virtual byte getState();
};
#endif