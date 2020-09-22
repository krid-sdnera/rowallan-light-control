#include "ButtonGPIO.h"

ButtonGPIO::ButtonGPIO(byte _pin) : Button(_pin) {}

void ButtonGPIO::init()
{
    pinMode(this->pin, INPUT_PULLUP);
}

byte ButtonGPIO::getState()
{
    return digitalRead(this->pin);
}