#ifndef Button_H
#define Button_H
#include <Arduino.h>
class Button
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

  Button(byte _pin, int _edge);
  virtual ~Button();
  virtual void init() = 0;
  virtual byte getState() = 0;
  void update();
  bool isPressed();
  bool isLongPressed(int duration);
};
#endif