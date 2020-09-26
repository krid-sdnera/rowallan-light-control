#include "SensorI2C.h"

SensorI2C::SensorI2C(I2CWrapper *_i2c, byte _pin, int _edge) : i2c(_i2c), Sensor(_pin, _edge) {}

void SensorI2C::init() {}

byte SensorI2C::getState()
{
    return i2c->rc().readInputStatus(this->pin);
}
