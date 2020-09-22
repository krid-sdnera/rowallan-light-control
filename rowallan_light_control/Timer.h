#ifndef Timer_H
#define Timer_H
#include <Arduino.h>
class Timer
{

private:
  unsigned long startTime = 0;
  unsigned long expiryDuration = 0;

public:
  Timer();
  virtual ~Timer();
  void start(int duration);
  bool isExpired();
};
#endif