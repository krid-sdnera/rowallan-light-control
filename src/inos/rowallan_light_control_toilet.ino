#include "Arduino.h"

#include "I2CWrapper.h"
#include "AppState.h"

#include "LightGPIO.h"
#include "LightI2C.h"
#include "SensorGPIO.h"
#include "SensorI2C.h"
#include "SensorI2CKeypad.h"
#include "Timer.h"
#include "TimerModeAware.h"

#include "Circuit.h"

// Define the two relay boards
I2CWrapper relayI2CBoard1(0, 0, 0);

SensorI2C sensor11(&relayI2CBoard1, 1); // Male Toilet
SensorI2C sensor12(&relayI2CBoard1, 2); // Female Toilet
SensorI2C sensor13(&relayI2CBoard1, 3); // Shared Shower
SensorGPIO sensorD7(7);                 // Day night detector

LightI2C light11(&relayI2CBoard1, 1); // Male Toilet
LightI2C light12(&relayI2CBoard1, 2); // Female Toilet
LightI2C light13(&relayI2CBoard1, 3); // Shared Shower
LightI2C light14(&relayI2CBoard1, 4); // Overnight power (door light and sensor power)
LightGPIO lightD9(9);                 // Status Light

// Set the durations for day, night, lateNight
// 30 * 60 * 1000 = 1800000 = 30 minutes
TimerModeAware timer1(0, 1800000ul, 1800000ul, 0);
TimerModeAware timer2(0, 1800000ul, 1800000ul, 0);
TimerModeAware timer3(0, 1800000ul, 1800000ul, 0);
Timer statusIndicatorTimer;
Timer lateNightModeTimer;

Circuit circuit1(&sensor11, &light11, &timer1, Circuit::MODE_ON, 100);
Circuit circuit2(&sensor12, &light12, &timer2, Circuit::MODE_ON, 100);
Circuit circuit3(&sensor13, &light13, &timer3, Circuit::MODE_ON, 100);

void setup()
{
    Serial.begin(9600);
    Serial.println(F("initialising"));

    AppState::getInstance()->setDaylightSensor(&sensorD7);
    AppState::getInstance()->setLateNightTimer(&lateNightModeTimer);
    AppState::getInstance()->setNightLight(&light14);
    AppState::getInstance()->setStatusIndicatorLight(&lightD9);
    AppState::getInstance()->setStatusIndicatorTimer(&statusIndicatorTimer);

    relayI2CBoard1.init();
    circuit1.init();
    circuit2.init();
    circuit3.init();

    Serial.println(F("initialisation done"));
}

void loop()
{
    AppState::getInstance()->updateMode();
    AppState::getInstance()->updateStatusIndicator();

    circuit1.update();
    circuit2.update();
    circuit3.update();
}
