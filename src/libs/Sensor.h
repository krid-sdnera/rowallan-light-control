#ifndef Sensor_H
#define Sensor_H
#include <Arduino.h>

class Sensor
{

protected:
  bool state = HIGH;
  bool lastReading = HIGH;
  bool DEPRESSED = LOW;
  unsigned long lastDebounceTime = 0;
  unsigned int debounceDelay = 20;
  unsigned long lastStateChangeTime = 0;

public:
  static const byte MODE_LEADING_EDGE = 1;
  static const byte MODE_TRAILING_EDGE = 2;
  static const byte MODE_BOTH_EDGE = 3;

  Sensor();
  virtual ~Sensor();
  virtual void init() = 0;
  virtual bool getState() = 0;
  void update();
  bool isActive();
  bool isActive(int duration);
  bool isActive(byte mode);
  bool isActive(int duration, byte mode);
};
#endif
