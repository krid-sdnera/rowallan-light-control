#ifndef Timer_H
#define Timer_H
#include <Arduino.h>
class Timer
{

protected:
  unsigned long startTime = 0;
  unsigned long expiryDuration = 0;
  unsigned long almostDuration = 0;

public:
  Timer();
  Timer(unsigned long _almost);
  virtual ~Timer();

  // Values in milliseconds
  static const byte UNIT_MILLI = 1;
  static const unsigned int UNIT_SECOND = 1000;
  static const unsigned int UNIT_MINUTE = 60000;
  static const unsigned long UNIT_HOUR = 3600000ul;

  unsigned long start();
  unsigned long start(unsigned long duration);
  unsigned long start(unsigned long duration, unsigned int unit);
  virtual unsigned long modifyDuration(unsigned long duration);
  virtual bool isExpired();
  bool isAlmostExpired();
  bool isStarted();
  void clear();
};
#endif
