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
  byte circuitMode;
  int sensorOverrideActiveDuration;
  bool processedActiveStateEvent = false;
  bool processedAlmostExpiredEvent = false;

public:
  static const byte MODE_TOGGLE = 1;
  static const byte MODE_ON = 2;
  static const byte MODE_KEYPAD = 3;

  Circuit(Sensor *b, Light *l, Timer *t, byte _mode, int _sensorOverrideActiveDuration);
  virtual ~Circuit();
  void init();
  void update();
};
#endif
