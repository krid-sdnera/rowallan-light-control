#ifndef TimerModeAware_H
#define TimerModeAware_H
#include <Arduino.h>
#include "Timer.h"

class TimerModeAware : public Timer
{

private:
  int durationDay;
  int durationNight;
  int durationLateNight;
  int storedAppMode = 0;

public:
  TimerModeAware(int _day, int _night, int _lateNight);
  virtual ~TimerModeAware();
  virtual bool isExpired();
};
#endif
