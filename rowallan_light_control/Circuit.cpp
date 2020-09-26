#include "Circuit.h"
#include "Sensor.h"
#include "Light.h"
#include "Timer.h"

Circuit::Circuit(Sensor *b, Light *l, Timer *t, int _mode) : sensor(b), light(l), timer(t), mode(_mode) {}

Circuit::~Circuit() {}

void Circuit::init()
{
    sensor->init();
    light->init();
    // timer->init();
}
void Circuit::update()
{
    Serial.println("circuit update");

    int pressDuration;
    int timerDuration;
    if (SunState::isDay())
    {
        pressDuration = 2000;
        timerDuration = 5000;
    }
    else
    {
        pressDuration = 100;
        timerDuration = 10000;
    }

    sensor->update();
    if (sensor->isLongPressed(pressDuration))
    {
        Serial.println("circuit update:pressed");
        if (mode == Circuit::MODE_TOGGLE)
        {
            light->toggle();
        }
        else if (!light->isOn())
        {
            light->on();
        }
        timer->start(timerDuration);
    }
    else
    {
        Serial.println("circuit update:not pressed");

        if (light->isOn() && timer->isExpired())
        {
            light->off();
        }
    }
}
