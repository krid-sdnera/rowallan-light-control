#ifndef Sensor_H
#define Sensor_H
#include <Arduino.h>
class Sensor
{

protected:
  byte edgeDetection;
  byte pin;
  bool state = HIGH;
  bool lastReading = HIGH;
  bool DEPRESSED = LOW;
  unsigned long lastDebounceTime = 0;
  unsigned int debounceDelay = 20;
  unsigned long lastDepressedTime = 0;
  unsigned long timeOfDepression = 0;

public:
  static const byte EDGE_LEADING = 1;
  static const byte EDGE_TRAILING = 2;

  Sensor(byte _pin, byte _edge);
  virtual ~Sensor();
  virtual void init() = 0;
  virtual bool getState() = 0;
  void update();
  bool isPressed();
  bool isPressed(int duration);
};
#endif