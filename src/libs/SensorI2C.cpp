#include "SensorI2C.h"

SensorI2C::SensorI2C(I2CWrapper *_i2c, byte _pin) : i2c(_i2c), pin(_pin), Sensor() {}

void SensorI2C::init() {}

bool SensorI2C::getState()
{
    return (i2c->rc().readInputStatus(pin) == 1);
}
