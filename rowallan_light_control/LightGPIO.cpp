#include "LightGPIO.h"

LightGPIO::LightGPIO(byte _pin) : Light(_pin) {}

void LightGPIO::init()
{
    pinMode(pin, OUTPUT);
    off();
}

boolean LightGPIO::isOn()
{
    return (state == true);
}

void LightGPIO::toggle()
{
    if (isOn() == true)
    {
        off();
    }
    else
    {
        on();
    }
}

void LightGPIO::on()
{
    state = true;
    digitalWrite(pin, HIGH);
}

void LightGPIO::off()
{
    state = false;
    digitalWrite(pin, LOW);
}