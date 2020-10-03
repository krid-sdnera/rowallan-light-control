#ifndef AppState_H
#define AppState_H
#include <Arduino.h>
#include "Sensor.h"
#include "Timer.h"

class AppState
{

private:
  /* Here will be the instance stored. */
  static AppState *instance;
  Sensor *sensor;
  int mode;
  Timer *timer;

  /* Private constructor to prevent instancing. */
  AppState();

public:
  static const int MODE_DAY = 1;
  static const int MODE_NIGHT = 2;
  static const int MODE_LATE_NIGHT = 3;

  /* Static access method. */
  static AppState *getInstance();
  virtual ~AppState();

  void setDaylightSensor(Sensor *_sensor);
  void setLateNightTimer(Timer *_timer);

  void update();
  int AppMode();
  int AppModeTransition(int currentMode);
};
#endif