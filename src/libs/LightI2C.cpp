#include "LightI2C.h"
#include "I2CWrapper.h"

LightI2C::LightI2C(I2CWrapper *_i2c, byte _pin) : i2c(_i2c), Light(_pin) {}

void LightI2C::init()
{
    off();
}

bool LightI2C::isOn()
{
    // return (i2c->rc().readRelayStatus(this->pin) == 1);
    return (state == true);
}

void LightI2C::toggle()
{
    state = !state;
    i2c->rc().toggleRelay(pin);
}

void LightI2C::on()
{
    state = true;
    i2c->rc().turnOnRelay(pin);
}

void LightI2C::off()
{
    state = false;
    i2c->rc().turnOffRelay(pin);
}
