#ifndef Timer_H
#define Timer_H
#include <Arduino.h>
class Timer
{

protected:
  unsigned long startTime = 0;
  unsigned long expiryDuration = 0;

public:
  Timer();
  virtual ~Timer();

  // Values in milliseconds
  static const int UNIT_SECOND = 1000;
  static const int UNIT_MINUTE = 60000;
  static const int UNIT_HOUR = 3600000;

  void start();
  void start(int duration);
  void start(int duration, int unit);
  virtual bool isExpired();
  bool isStarted();
  void clear();
};
#endif