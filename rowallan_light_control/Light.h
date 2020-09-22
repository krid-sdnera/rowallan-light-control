#ifndef Light_H
#define Light_H
#include <Arduino.h>

class Light
{

protected:
  byte pin;

public:
  Light(byte _pin);
  virtual ~Light();
  virtual void init() = 0;
  virtual boolean isOn() = 0;
  virtual void toggle() = 0;
  virtual void on() = 0;
  virtual void off() = 0;
};
#endif
