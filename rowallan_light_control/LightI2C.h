#ifndef LightI2C_H
#define LightI2C_H
#include <Arduino.h>
#include "Light.h"
#include "I2CWrapper.h"

class LightI2C : public Light
{
protected:
  I2CWrapper *i2c;

public:
  LightI2C(I2CWrapper *_i2c, byte pin);

  virtual void init();
  virtual boolean isOn();
  virtual void toggle();
  virtual void on();
  virtual void off();
};
#endif
