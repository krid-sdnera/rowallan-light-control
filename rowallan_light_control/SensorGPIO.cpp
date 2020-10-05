#include "SensorGPIO.h"

SensorGPIO::SensorGPIO(byte _pin, byte _edge) : Sensor(_pin, _edge) {}

void SensorGPIO::init()
{
    pinMode(pin, INPUT_PULLUP);
}

bool SensorGPIO::getState()
{
    return digitalRead(pin);
}