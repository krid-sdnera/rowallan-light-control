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
I2CWrapper relayI2CBoard2(1, 0, 0);

SensorI2C sensor11(&relayI2CBoard1, 1);
SensorI2C sensor12(&relayI2CBoard1, 2);
SensorI2C sensor13(&relayI2CBoard1, 3);
SensorI2C sensor14(&relayI2CBoard1, 4);
SensorI2C sensor21(&relayI2CBoard2, 1);
SensorI2C sensor22(&relayI2CBoard2, 2);
SensorI2C sensor23(&relayI2CBoard2, 3);
SensorI2C sensor24(&relayI2CBoard2, 4);
SensorGPIO sensorD7(7); // Day night detector
SensorI2CKeypad sensorKeypad(8);

LightI2C light11(&relayI2CBoard1, 1);
LightI2C light12(&relayI2CBoard1, 2);
LightI2C light13(&relayI2CBoard1, 3);
LightI2C light14(&relayI2CBoard1, 3);
LightI2C light21(&relayI2CBoard2, 1);
LightI2C light22(&relayI2CBoard2, 2);
LightI2C light23(&relayI2CBoard2, 3);
LightI2C light24(&relayI2CBoard2, 3);
LightGPIO lightD9(9); // Status Light

// Set the durations for day, night, lateNight
TimerModeAware timer1(15000, 20000, 10000, 5000);
TimerModeAware timer2(15000, 20000, 10000, 5000);
TimerModeAware timer3(15000, 20000, 10000, 0);
TimerModeAware timer4(15000, 20000, 10000, 5000);
TimerModeAware timer5(15000, 20000, 10000, 5000);
TimerModeAware timer6(15000, 20000, 10000, 5000);
TimerModeAware timer7(15000, 20000, 10000, 5000);
Timer timer8;
Timer statusIndicatorTimer;
Timer lateNightModeTimer;

Circuit circuit1(&sensor11, &light11, &timer1, Circuit::MODE_TOGGLE, 2000);
Circuit circuit2(&sensor12, &light12, &timer2, Circuit::MODE_TOGGLE, 2000);
Circuit circuit3(&sensor13, &light13, &timer3, Circuit::MODE_ON, 100);
Circuit circuit4(&sensor14, &light14, &timer4, Circuit::MODE_TOGGLE, 2000);
Circuit circuit5(&sensor21, &light21, &timer5, Circuit::MODE_TOGGLE, 2000);
Circuit circuit6(&sensor22, &light22, &timer6, Circuit::MODE_TOGGLE, 2000);
Circuit circuit7(&sensor23, &light23, &timer7, Circuit::MODE_TOGGLE, 2000);
Circuit circuit8(&sensorKeypad, &light24, &timer8, Circuit::MODE_KEYPAD, 0);

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
    circuit4.init();
    circuit5.init();
    circuit6.init();
    circuit7.init();
    circuit8.init();

    Serial.println("initialisation done");
}

void loop()
{
    AppState::getInstance()->updateMode();
    AppState::getInstance()->updateStatusIndicator();

    circuit1.update();
    circuit2.update();
    circuit3.update();
    circuit4.update();
    circuit5.update();
    circuit6.update();
    circuit7.update();
    circuit8.update();
}
