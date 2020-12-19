#ifndef SensorCombine_H
#define SensorCombine_H
#include <Arduino.h>
#include "AppState.h"
#include "Sensor.h"
#include "SparkFun_Qwiic_Keypad_Arduino_Library.h"

class SensorCombine : public Sensor
{

private:
  Sensor *sensor1;
  Sensor *sensor2;

public:
  SensorCombine(Sensor *_sensor1, Sensor *_sensor2);
  virtual void init() override;
  virtual bool getState() override;
};
#endif
