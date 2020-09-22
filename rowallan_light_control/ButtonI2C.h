#ifndef ButtonI2C_H
#define ButtonI2C_H
#include <Arduino.h>
#include "I2CWrapper.h"
#include "Button.h"
class ButtonI2C : public Button
{

private:
  I2CWrapper *i2c;
  int DEPRESSED = 0;

public:
  ButtonI2C(I2CWrapper *_i2c, byte pin);
  virtual void init();
  virtual byte getState();
};
#endif