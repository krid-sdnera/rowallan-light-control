#include "ButtonI2C.h"

ButtonI2C::ButtonI2C(I2CWrapper *_i2c, byte _pin, int _edge) : i2c(_i2c), Button(_pin, _edge) {}

void ButtonI2C::init() {}

byte ButtonI2C::getState()
{
    return i2c->rc().readInputStatus(this->pin);
}
