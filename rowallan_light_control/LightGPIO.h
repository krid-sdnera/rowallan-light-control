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
  virtual void init();
  virtual boolean isOn();
  virtual void toggle();
  virtual void on();
  virtual void off();
};
#endif
