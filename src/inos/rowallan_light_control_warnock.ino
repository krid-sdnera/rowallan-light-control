#include "Arduino.h"

#include "I2CWrapper.h"
#include "AppState.h"

#include "LightGPIO.h"
#include "LightI2C.h"
#include "SensorGPIO.h"
#include "SensorI2C.h"
#include "SensorCombine.h"
#include "SensorI2CKeypad.h"
#include "Timer.h"
#include "TimerModeAware.h"

#include "Circuit.h"

// Define the two relay boards
I2CWrapper relayI2CBoard1(0, 0, 0);
I2CWrapper relayI2CBoard2(1, 0, 0);

SensorI2C sensor11(&relayI2CBoard1, 1);       // Kitchen
SensorI2C sensor12(&relayI2CBoard1, 2);       // Kitchen Work
SensorI2C sensor13(&relayI2CBoard1, 3);       // Kitchen Spot
SensorI2C sensor14(&relayI2CBoard1, 4);       // Dining (Kitchen Button)
SensorI2C sensor21(&relayI2CBoard2, 1);       // Covered (Kitchen Button)
SensorI2C sensor22(&relayI2CBoard2, 2);       // Trough
SensorI2C sensor23(&relayI2CBoard2, 3);       // BBQ Area
SensorGPIO sensorD8(8);                       // Dining (Dining Button)
SensorGPIO sensorD9(9);                       // Covered (Dining Button)
SensorCombine sensorC1(&sensor14, &sensorD8); // Dining Combined
SensorCombine sensorC2(&sensor21, &sensorD9); // Covered Combined
SensorGPIO sensorD7(7);                       // Day night detector
SensorI2CKeypad sensorKeypad();               // Kitchen Door Keypad

LightI2C light11(&relayI2CBoard1, 1); // Kitchen
LightI2C light12(&relayI2CBoard1, 2); // Kitchen Work
LightI2C light13(&relayI2CBoard1, 3); // Kitchen Spot
LightI2C light14(&relayI2CBoard1, 4); // Dining
LightI2C light21(&relayI2CBoard2, 1); // Covered
LightI2C light22(&relayI2CBoard2, 2); // Trough
LightI2C light23(&relayI2CBoard2, 3); // BBQ Area
LightI2C light24(&relayI2CBoard2, 4); // Kitchen Door Release
LightGPIO lightD6(6);                 // Status Light

// Set the durations for day, night, lateNight
//      5 * 60 * 1000 =   300000 =  5 minutes
//     10 * 60 * 1000 =   600000 = 10 minutes
//     30 * 60 * 1000 =  1800000 = 30 minutes
//     60 * 60 * 1000 =  3600000 = 60 minutes
// 2 * 60 * 60 * 1000 =  7200000 =  2 hours
// 6 * 60 * 60 * 1000 = 21600000 =  6 hours
TimerModeAware timer1(3600000ul, 21600000ul, 1800000ul, 300000ul); // Kitchen
TimerModeAware timer2(3600000ul, 7200000ul, 1800000ul, 300000ul);  // Kitchen Work
TimerModeAware timer3(0, 600000ul, 600000ul, 0);                   // Kitchen Spot
TimerModeAware timer4(3600000ul, 21600000ul, 1800000ul, 300000ul); // Dining
TimerModeAware timer5(3600000ul, 21600000ul, 1800000ul, 300000ul); // Covered
TimerModeAware timer6(0, 600000ul, 600000ul, 0);                   // Trough
TimerModeAware timer7(3600000ul, 7200000ul, 600000ul, 300000ul);   // BBQ Area
Timer timer8;                                                      // Kitchen Door Keypad and Release
Timer statusIndicatorTimer;
Timer lateNightModeTimer;

Circuit circuit1(&sensor11, &light11, &timer1, Circuit::MODE_TOGGLE, 2000); // Kitchen
Circuit circuit2(&sensor12, &light12, &timer2, Circuit::MODE_TOGGLE, 2000); // Kitchen Work
Circuit circuit3(&sensor13, &light13, &timer3, Circuit::MODE_ON, 100);      // Kitchen Spot
Circuit circuit4(&sensorC1, &light14, &timer4, Circuit::MODE_TOGGLE, 2000); // Dining
Circuit circuit5(&sensorC2, &light21, &timer5, Circuit::MODE_TOGGLE, 2000); // Covered
Circuit circuit6(&sensor22, &light22, &timer6, Circuit::MODE_ON, 100);      // Trough
Circuit circuit7(&sensor23, &light23, &timer7, Circuit::MODE_TOGGLE, 2000); // BBQ Area
// Circuit circuit8(&sensorKeypad, &light24, &timer8, Circuit::MODE_KEYPAD, 0); // Kitchen Door Keypad and Release

void setup()
{
    Serial.begin(9600);
    Serial.println(F("initialising"));

    AppState::getInstance()->setDaylightSensor(&sensorD7);
    AppState::getInstance()->setLateNightTimer(&lateNightModeTimer);
    AppState::getInstance()->setStatusIndicatorLight(&lightD6);
    AppState::getInstance()->setStatusIndicatorTimer(&statusIndicatorTimer);

    relayI2CBoard1.init();
    relayI2CBoard2.init();
    circuit1.init();
    circuit2.init();
    circuit3.init();
    circuit4.init();
    circuit5.init();
    circuit6.init();
    circuit7.init();
    // circuit8.init();

    Serial.println(F("initialisation done"));
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
    // circuit8.update();
}
