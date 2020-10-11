#include "SensorGPIO.h"

SensorGPIO::SensorGPIO(byte _pin) : Sensor(_pin) {}

void SensorGPIO::init()
{
    pinMode(pin, INPUT);
    // pinMode(pin, INPUT_PULLUP);
}

bool SensorGPIO::getState()
{
    return digitalRead(pin);
}
