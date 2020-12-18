#ifndef SensorI2CKeypad_H
#define SensorI2CKeypad_H
#include <Arduino.h>
#include "AppState.h"
#include "Sensor.h"
#include "SparkFun_Qwiic_Keypad_Arduino_Library.h"
// typedef void(voidFuncPtr)(void);

class SensorI2CKeypad : public Sensor
{

private:
  KEYPAD keypad;
  char keysPressed[4] = {0, 0, 0, 0};
  char keysExpected[4] = {'1', '2', '3', '4'};

public:
  SensorI2CKeypad(byte pin);
  virtual void init() override;
  virtual bool getState() override;
};
#endif
