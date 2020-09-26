#ifndef ButtonGPIO_H
#define ButtonGPIO_H
#include <Arduino.h>
#include "Button.h"
class ButtonGPIO : public Button
{

public:
  ButtonGPIO(byte pin, int _edge);
  virtual void init();
  virtual byte getState();
};
#endif