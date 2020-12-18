#ifndef TimerModeAware_H
#define TimerModeAware_H
#include <Arduino.h>
#include "Timer.h"

class TimerModeAware : public Timer
{

private:
  byte storedAppMode = 0;
  unsigned long durationDay;
  unsigned long durationNight;
  unsigned long durationLateNight;

public:
  TimerModeAware(unsigned long _day, unsigned long _night, unsigned long _lateNight, unsigned long _almost);
  virtual ~TimerModeAware();
  virtual unsigned long modifyDuration(unsigned long duration) override;
  virtual bool isExpired() override;
};
#endif
