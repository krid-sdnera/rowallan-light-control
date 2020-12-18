#ifndef Sensor_H
#define Sensor_H
#include <Arduino.h>
class Sensor
{

protected:
  byte pin;
  bool state = HIGH;
  bool lastReading = HIGH;
  bool DEPRESSED = LOW;
  unsigned long lastDebounceTime = 0;
  unsigned int debounceDelay = 20;
  unsigned long lastStateChangeTime = 0;

public:
  Sensor(byte _pin);
  virtual ~Sensor();
  virtual void init() = 0;
  virtual bool getState() = 0;
  void update();
  bool isActive();
  bool isActive(int duration);
  bool isInactive();
  bool isInactive(int duration);
};
#endif
