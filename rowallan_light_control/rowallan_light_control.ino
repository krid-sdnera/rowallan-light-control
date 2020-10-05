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
SensorI2C sensor13(&relayI2CBoard1, 3, Sensor::EDGE_LEADING);
SensorI2C sensor14(&relayI2CBoard1, 4, Sensor::EDGE_TRAILING);
SensorI2C sensor21(&relayI2CBoard2, 1, Sensor::EDGE_TRAILING);
SensorI2C sensor22(&relayI2CBoard2, 2, Sensor::EDGE_LEADING);
SensorI2C sensor23(&relayI2CBoard2, 3, Sensor::EDGE_TRAILING);
SensorI2C sensor24(&relayI2CBoard2, 4, Sensor::EDGE_TRAILING);
SensorGPIO sensorD7(7, Sensor::EDGE_LEADING); // Day night detector

LightI2C light11(&relayI2CBoard1, 1);
LightI2C light12(&relayI2CBoard1, 2);
LightI2C light13(&relayI2CBoard1, 3);
LightGPIO lightD8(8);
LightGPIO lightD9(9); // Status Light

// Set the durations for_day, night, lateNight
TimerModeAware timer1(10000, 20000, 5000);
TimerModeAware timer2(10000, 20000, 5000);
TimerModeAware timer3(10000, 20000, 5000);
Timer statusIndicatorTimer;
Timer lateNightModeTimer;

Circuit circuit1(&sensor11, &light11, &timer1, Circuit::MODE_TOGGLE);
Circuit circuit2(&sensor12, &light12, &timer2, Circuit::MODE_TOGGLE);
Circuit circuit3(&sensor13, &light13, &timer3, Circuit::MODE_ON);

void setup()
{
    Serial.begin(9600);
    Serial.println("initialising");

    AppState::getInstance()->setDaylightSensor(&sensorD7);
    AppState::getInstance()->setLateNightTimer(&lateNightModeTimer);
    AppState::getInstance()->setStatusIndicatorLight(&lightD9);
    AppState::getInstance()->setStatusIndicatorTimer(&statusIndicatorTimer);

    relayI2CBoard1.init();
    circuit1.init();
    circuit2.init();
    circuit3.init();

    Serial.println("initialisation done");
}

void loop()
{
    // Serial.println("loop: begin");

    AppState::getInstance()->updateMode();
    AppState::getInstance()->updateStatusIndicator();

    circuit1.update();
    circuit2.update();
    circuit3.update();
    // circuit4.update();
    // circuit5.update();
    // circuit6.update();
    // circuit7.update();
}
