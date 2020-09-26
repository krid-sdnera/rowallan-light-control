#include "SensorGPIO.h"

SensorGPIO::SensorGPIO(byte _pin, int _edge) : Sensor(_pin, _edge) {}

void SensorGPIO::init()
{
    pinMode(this->pin, INPUT_PULLUP);
}

byte SensorGPIO::getState()
{
    return digitalRead(this->pin);
}