#include "SensorCombine.h"

SensorCombine::SensorCombine(Sensor *_sensor1, Sensor *_sensor2) : sensor1(_sensor1), sensor2(_sensor2), Sensor() {}

void SensorCombine::init()
{
    sensor1->init();
    sensor2->init();
    state = getState();
}

bool SensorCombine::getState()
{
    return (sensor1->getState() != sensor2->getState());
}
