#include "SensorGPIO.h"

SensorGPIO::SensorGPIO(byte _pin) : pin(_pin), Sensor() {}

void SensorGPIO::init()
{
    pinMode(pin, INPUT);
    state = getState();
    // pinMode(pin, INPUT_PULLUP);
}

bool SensorGPIO::getState()
{
    return digitalRead(pin);
}
