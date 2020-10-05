#include "LightI2C.h"
#include "I2CWrapper.h"

LightI2C::LightI2C(I2CWrapper *_i2c, byte _pin) : i2c(_i2c), Light(_pin) {}

void LightI2C::init()
{
    off();
}

bool LightI2C::isOn()
{
    return (i2c->rc().readRelayStatus(this->pin) == 1);
}

void LightI2C::toggle()
{
    i2c->rc().toggleRelay(this->pin);
}

void LightI2C::on()
{
    i2c->rc().turnOnRelay(this->pin);
}

void LightI2C::off()
{
    i2c->rc().turnOffRelay(this->pin);
}