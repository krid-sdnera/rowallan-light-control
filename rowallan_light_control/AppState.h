#ifndef AppState_H
#define AppState_H
#include <Arduino.h>
#include "Sensor.h"
#include "Light.h"
#include "Timer.h"

class AppState
{

private:
  /* Here will be the instance stored. */
  static AppState *instance;
  Sensor *daylightSensor;
  Timer *lateNightTimer;
  Light *statusIndicatorLight;
  Timer *statusIndicatorTimer;
  byte mode;

  /* Private constructor to prevent instancing. */
  AppState();

public:
  static const byte MODE_DAY = 1;
  static const byte MODE_NIGHT = 2;
  static const byte MODE_LATE_NIGHT = 3;

  /* Static access method. */
  static AppState *getInstance();
  virtual ~AppState();

  void setDaylightSensor(Sensor *_sensor);
  void setLateNightTimer(Timer *_timer);
  void setStatusIndicatorLight(Light *_light);
  void setStatusIndicatorTimer(Timer *_timer);

  void updateMode();
  void updateStatusIndicator();
  int AppMode();
  int AppModeTransition(byte currentMode);
};
#endif