#include "ButtonGPIO.h"

ButtonGPIO::ButtonGPIO(byte _pin, int _edge) : Button(_pin, _edge) {}

void ButtonGPIO::init()
{
    pinMode(this->pin, INPUT_PULLUP);
}

byte ButtonGPIO::getState()
{
    return digitalRead(this->pin);
}