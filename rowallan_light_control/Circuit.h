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
  int mode;

public:
  int MODE_TOGGLE = 1;
  int MODE_ON = 2;

  Circuit(Button *b, Light *l, Timer *t, int _mode);
  virtual ~Circuit();
  void init();
  void update();
};
#endif