#ifndef TimerModeAware_H
#define TimerModeAware_H
#include <Arduino.h>
#include "Timer.h"

class TimerModeAware : public Timer
{

private:
  byte storedAppMode = 0;
  int durationDay;
  int durationNight;
  int durationLateNight;

public:
  TimerModeAware(int _day, int _night, int _lateNight, int _almost);
  virtual ~TimerModeAware();
  virtual int modifyDuration(int duration) override;
  virtual bool isExpired() override;
};
#endif
