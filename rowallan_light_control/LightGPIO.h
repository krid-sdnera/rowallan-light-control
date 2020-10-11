#ifndef LightGPIO_H
#define LightGPIO_H
#include <Arduino.h>
#include "Light.h"

class LightGPIO : public Light
{

private:
  boolean state = false;

public:
  LightGPIO(byte _pin);
  virtual void init() override;
  virtual boolean isOn() override;
  virtual void toggle() override;
  virtual void on() override;
  virtual void off() override;
};
#endif
