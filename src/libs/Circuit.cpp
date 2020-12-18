#include "Circuit.h"
#include "Sensor.h"
#include "Light.h"
#include "Timer.h"
#include "AppState.h"

Circuit::Circuit(Sensor *b, Light *l, Timer *t, byte _circuitMode, int _sensorOverrideActiveDuration) : sensor(b), light(l), timer(t), circuitMode(_circuitMode), sensorOverrideActiveDuration(_sensorOverrideActiveDuration) {}

Circuit::~Circuit() {}

void Circuit::init()
{
    sensor->init();
    light->init();
    // timer->init();
}
void Circuit::update()
{
    if (circuitMode == Circuit::MODE_KEYPAD)
    {
        if (sensor->getState())
        {
            timer->start(3000);
            light->on();
            Serial.println("circuit update:on:keypad");
        }

        if (light->isOn())
        {
            // Check if the light should be turned off,
            // even if the sensor has been held down.
            if (timer->isExpired())
            {
                light->off();
                Serial.println("circuit update:off:keypad");
            }
        }
        return;
    }

    // Vaild Circuit::Modes below this point
    // MODE_TOGGLE, MODE_ON

    int pressDuration;
    if (AppState::getInstance()->AppMode() == AppState::MODE_DAY && !light->isOn())
    {
        pressDuration = sensorOverrideActiveDuration;
    }
    else
    {
        pressDuration = 100;
    }

    light->flashUpdate();
    sensor->update();

    // If the sensor is active and we have not processed the active action
    // before, we can perform the toggle/on action for this circuit.
    if (sensor->isActive(pressDuration) && !processedActiveStateEvent)
    {
        if (circuitMode == Circuit::MODE_TOGGLE)
        {
            light->toggle();
            Serial.println("circuit update:toggled");
        }
        else if (!light->isOn() && circuitMode == Circuit::MODE_ON)
        {
            light->on();
            Serial.println("circuit update:on");
        }

        // Mark this active state event as processed.
        processedActiveStateEvent = true;

        // (Re)Start timer and unmark almost expired event as not processed.
        timer->start();
        processedAlmostExpiredEvent = false;
    }

    // If the sensor is inactive we want to reset the flag marking the active
    // action as processed so the next time the sensor is acitve we can procecess
    // that event.
    if (sensor->isInactive())
    {
        processedActiveStateEvent = false;
    }

    if (light->isOn())
    {
        // Check if the light should be turned off,
        // even if the sensor has been held down.
        if (timer->isExpired())
        {
            light->off();
            Serial.println("circuit update:off");
        }

        // FLash the circuit if the timer is almost expired
        if (timer->isAlmostExpired() && !processedAlmostExpiredEvent)
        {
            processedAlmostExpiredEvent = true;
            light->flash();
            Serial.println("circuit update:flash");
        }
    }
}
