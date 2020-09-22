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
        on();
    }
    else
    {
        off();
    }
}

void LightGPIO::on()
{
    this->state = true;
    digitalWrite(pin, HIGH);
}

void LightGPIO::off()
{
    this->state = false;
    digitalWrite(this->pin, LOW);
}