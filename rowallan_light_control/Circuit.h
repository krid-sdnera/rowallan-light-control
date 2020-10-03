#ifndef Circuit_H
#define Circuit_H
#include <Arduino.h>

#include "Sensor.h"
#include "Light.h"
#include "Timer.h"

class Circuit
{

private:
  Sensor *sensor;
  Light *light;
  Timer *timer;
  int mode;

public:
  static int const MODE_TOGGLE = 1;
  static int const MODE_ON = 2;

  Circuit(Sensor *b, Light *l, Timer *t, int _mode);
  virtual ~Circuit();
  void init();
  void update();
};
#endif