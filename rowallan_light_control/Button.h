#ifndef Button_H
#define Button_H
#include <Arduino.h>
class Button
{

protected:
  byte pin;
  byte state;
  byte lastReading = 0;
  byte DEPRESSED = 1;
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 20;
  unsigned long lastDepressedTime = 0;
  unsigned long timeOfDepression = 0;

public:
  Button(byte _pin);
  virtual ~Button();
  virtual void init() = 0;
  virtual byte getState() = 0;
  void update();
  bool isPressed();
  bool isLongPressed(int duration);
};
#endif