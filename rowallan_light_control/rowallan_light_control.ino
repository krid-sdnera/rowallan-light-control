#include "Arduino.h"

#include "I2CWrapper.h"
#include "AppState.h"

#include "LightGPIO.h"
#include "LightI2C.h"
#include "SensorGPIO.h"
#include "SensorI2C.h"
#include "Timer.h"
#include "TimerModeAware.h"

#include "Circuit.h"

// Define the two relay boards
I2CWrapper relayI2CBoard1(0, 0, 0);
I2CWrapper relayI2CBoard2(1, 0, 0);

SensorI2C sensor11(&relayI2CBoard1, 1, Sensor::EDGE_TRAILING);
SensorI2C sensor12(&relayI2CBoard1, 2, Sensor::EDGE_TRAILING);
SensorI2C sensor13(&relayI2CBoard1, 3, Sensor::EDGE_TRAILING);
SensorI2C sensor14(&relayI2CBoard1, 4, Sensor::EDGE_TRAILING);
SensorI2C sensor21(&relayI2CBoard2, 1, Sensor::EDGE_TRAILING);
SensorI2C sensor22(&relayI2CBoard2, 2, Sensor::EDGE_LEADING);
SensorI2C sensor23(&relayI2CBoard2, 3, Sensor::EDGE_TRAILING);
SensorI2C sensor24(&relayI2CBoard2, 4, Sensor::EDGE_TRAILING);
SensorGPIO sensorD7(7, Sensor::EDGE_TRAILING);
SensorGPIO sensorD8(8, Sensor::EDGE_LEADING); // Day night detector

LightI2C light1(&relayWapper1, 1);
// LightGPIO light2(LED_2_PIN);

// Set the durations for_day, night, lateNight
TimerModeAware timer1(10000, 20000, 5000);
TimerModeAware timer2(10000, 20000, 5000);
TimerModeAware timer3(10000, 20000, 5000);
Timer statusTimer;
Timer lateNightModeTimer;

Circuit circuit1(&sensor11, &light1, &timer1, Circuit::MODE_TOGGLE);
Circuit circuit2(&sensor12, &light1, &timer2, Circuit::MODE_TOGGLE);

void setup()
{
    Serial.begin(9600);
    Serial.println("initialising");

    AppState::getInstance()->setDaylightSensor(&sensorD7);
    AppState::getInstance()->setLateNightTimer(&lateNightModeTimer);

    relayI2CBoard1.init();
    circuit1.init();
    circuit2.init();

    Serial.println("initialisation done");
}

void loop()
{
    Serial.println("loop: begin");

    AppState::getInstance()->update();

    circutStatusUpdate(&lightD9, &statusTimer);

    circuit1.update();
    circuit2.update();
    // circuit2.update();
    // circuit3.update();
    // circuit4.update();
    // circuit5.update();
    // circuit6.update();
    // circuit7.update();
}

void circutStatusUpdate(Light *light, Timer *timer)
{
    // Mode 1: Day time mode
    if (AppState::getInstance()->AppMode() == AppState::MODE_DAY)
    {
        // TODO: Check if there is at least one circuit in override mode.
        if (light->isOn() && timer->isExpired())
        {
            Serial.println("status light update:off:DAY");
            light->off();
            timer->start(5000);
        }
        if (!light->isOn() && timer->isExpired())
        {
            Serial.println("status light update:on:DAY");
            light->on();
            timer->start(1000);
        }
    }
    // Mode 2: Night time mode
    if (AppState::getInstance()->AppMode() == AppState::MODE_NIGHT)
    {
        if (light->isOn() && timer->isExpired())
        {
            Serial.println("status light update:off:NIGHT");
            light->off();
            timer->start(2000);
        }
        if (!light->isOn() && timer->isExpired())
        {
            Serial.println("status light update:on:NIGHT");
            light->on();
            timer->start(2000);
        }
    }
    // Mode 3: Late night time mode
    if (AppState::getInstance()->AppMode() == AppState::MODE_LATE_NIGHT)
    {
        if (light->isOn() && timer->isExpired())
        {
            Serial.println("status light update:off:LATENIGHT");
            light->off();
            timer->start(4000);
        }
        if (!light->isOn() && timer->isExpired())
        {
            Serial.println("status light update:on:LATENIGHT");
            light->on();
            timer->start(4000);
        }
    }
}