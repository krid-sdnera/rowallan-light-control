#ifndef LightI2C_H
#define LightI2C_H
#include <Arduino.h>
#include "Light.h"
#include "I2CWrapper.h"

class LightI2C : public Light
{
private:
  boolean state = false;

protected:
  I2CWrapper *i2c;

public:
  LightI2C(I2CWrapper *_i2c, byte pin);

  virtual void init() override;
  virtual boolean isOn() override;
  virtual void toggle() override;
  virtual void on() override;
  virtual void off() override;
};
#endif
