#include "Circuit.h"
#include "Sensor.h"
#include "Light.h"
#include "Timer.h"
#include "AppState.h"

Circuit::Circuit(Sensor *b, Light *l, Timer *t, byte _mode) : sensor(b), light(l), timer(t), mode(_mode) {}

Circuit::~Circuit() {}

void Circuit::init()
{
    sensor->init();
    light->init();
    // timer->init();
}
void Circuit::update()
{
    int pressDuration;
    if (AppState::getInstance()->AppMode() == AppState::MODE_DAY)
    {
        pressDuration = 2000;
    }
    else
    {
        pressDuration = 100;
    }

    sensor->update();
    if (sensor->isPressed(pressDuration))
    {
        if (mode == Circuit::MODE_TOGGLE)
        {
            light->toggle();
            Serial.println("circuit update:toggled");
        }
        else if (!light->isOn())
        {
            light->on();
            Serial.println("circuit update:on");
        }
        timer->start();
    }
    else
    {
        if (light->isOn() && timer->isExpired())
        {
            light->off();
            Serial.println("circuit update:off");
        }
        // Else check if the timer is at T-10m till expiry, then flash the lights
    }
}
