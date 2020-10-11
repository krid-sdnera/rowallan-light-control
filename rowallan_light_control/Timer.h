#ifndef Timer_H
#define Timer_H
#include <Arduino.h>
class Timer
{

protected:
  unsigned long startTime = 0;
  int expiryDuration = 0;
  int almostDuration = 0;

public:
  Timer();
  Timer(int _almost);
  virtual ~Timer();

  // Values in milliseconds
  static const byte UNIT_MILLI = 1;
  static const unsigned int UNIT_SECOND = 1000;
  static const unsigned int UNIT_MINUTE = 60000;
  static const unsigned long UNIT_HOUR = 3600000ul;

  void start();
  void start(int duration);
  void start(int duration, unsigned int unit);
  virtual int modifyDuration(int duration);
  virtual bool isExpired();
  bool isAlmostExpired();
  bool isStarted();
  void clear();
};
#endif
