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
            Serial.println(F("circuit update:on:keypad"));
        }

        if (light->isOn())
        {
            // Check if the light should be turned off,
            // even if the sensor has been held down.
            if (timer->isExpired())
            {
                light->off();
                Serial.println(F("circuit update:off:keypad"));
            }
        }
        return;
    }

    // Vaild Circuit::Modes below this point
    // MODE_TOGGLE, MODE_ON

    int pressDuration = 100;

    light->flashUpdate();
    sensor->update();

    byte sensor_mode = (circuitMode == Circuit::MODE_TOGGLE) ? Sensor::MODE_BOTH_EDGE : Sensor::MODE_LEADING_EDGE;

    // If the sensor is active and we have not processed the active action
    // before, we can perform the toggle/on action for this circuit.
    if (sensor->isActive(pressDuration, sensor_mode) && !processedActiveStateEvent)
    {
        // (Re)Start timer
        if (timer->start() == 0)
        {
            light->off();
            Serial.println(F("circuit update:off:duration:0"));
        }
        else if (circuitMode == Circuit::MODE_TOGGLE)
        {
            light->toggle();
            Serial.println(F("circuit update:toggled"));
        }
        else if (!light->isOn() && circuitMode == Circuit::MODE_ON)
        {
            light->on();
            Serial.println(F("circuit update:on"));
        }

        // Mark this active state event as processed.
        processedActiveStateEvent = true;
        /// Mark almost expired event as not processed.
        processedAlmostExpiredEvent = false;
    }

    // Allow MODE_ON circuits to hold the sensor active.
    if (sensor->isActive(pressDuration, sensor_mode) && circuitMode == Circuit::MODE_ON)
    {
        // (Re)Start timer and unmark almost expired event as not processed.
        timer->start();
        processedAlmostExpiredEvent = false;
    }

    // If the sensor is inactive we want to reset the flag marking the active
    // action as processed so the next time the sensor is acitve we can procecess
    // that event.
    if (!sensor->isActive(sensor_mode))
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
            Serial.println(F("circuit update:off"));
        }

        // FLash the circuit if the timer is almost expired
        if (timer->isAlmostExpired() && !processedAlmostExpiredEvent)
        {
            processedAlmostExpiredEvent = true;
            light->flash();
            Serial.println(F("circuit update:flash"));
        }
    }
}
