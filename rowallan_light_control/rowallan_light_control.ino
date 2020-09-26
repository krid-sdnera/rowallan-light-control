#include "Arduino.h"

#include "I2CWrapper.h"

#include "LightGPIO.h"
#include "LightI2C.h"
#include "SensorGPIO.h"
#include "SensorI2C.h"
#include "Timer.h"

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

Timer timer1;
Timer timer2;

// // TODO: define sunState

Circuit circuit1(&sensor11, &light1, &timer1);
Circuit circuit2(&sensor12, &light1, &timer2);

void setup()
{
    Serial.begin(9600);
    Serial.println("initialising");

    relayWapper1.init();
    circuit1.init();
    circuit2.init();

    Serial.println("initialisation done");
}

void loop()
{
    Serial.println("loop: begin");

    circuit1.update();
    circuit2.update();
    // circuit2.update();
    // circuit3.update();
    // circuit4.update();
    // circuit5.update();
    // circuit6.update();
    // circuit7.update();
}