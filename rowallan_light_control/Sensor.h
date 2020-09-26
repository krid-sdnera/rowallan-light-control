#ifndef Sensor_H
#define Sensor_H
#include <Arduino.h>
class Sensor
{

protected:
  int edgeDetection;
  byte pin;
  byte state;
  byte lastReading = 0;
  byte DEPRESSED = 1;
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 20;
  unsigned long lastDepressedTime = 0;
  unsigned long timeOfDepression = 0;

public:
  static const int EDGE_LEADING = 1;
  static const int EDGE_TRAILING = 2;

  Sensor(byte _pin, int _edge);
  virtual ~Sensor();
  virtual void init() = 0;
  virtual byte getState() = 0;
  void update();
  bool isPressed();
  bool isLongPressed(int duration);
};
#endif