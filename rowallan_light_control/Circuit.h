#ifndef Circuit_H
#define Circuit_H
#include <Arduino.h>

#include "Button.h"
#include "Light.h"
#include "Timer.h"

class Circuit
{

private:
  Button *button;
  Light *light;
  Timer *timer;

public:
  Circuit(Button *b, Light *l, Timer *t);
  virtual ~Circuit();
  void init();
  void update();
};
#endif