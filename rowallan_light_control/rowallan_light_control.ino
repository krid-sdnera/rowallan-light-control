#include "Arduino.h"

#include "I2CWrapper.h"

#include "LightGPIO.h"
#include "LightI2C.h"
#include "ButtonGPIO.h"
#include "ButtonI2C.h"
#include "Timer.h"

#include "Circuit.h"

// Define the two relay boards
I2CWrapper relayI2CBoard1(0, 0, 0);
I2CWrapper relayI2CBoard2(1, 0, 0);

ButtonI2C button11(&relayI2CBoard1, 1, Button::EDGE_TRAILING);
ButtonI2C button12(&relayI2CBoard1, 2, Button::EDGE_TRAILING);
ButtonI2C button13(&relayI2CBoard1, 3, Button::EDGE_TRAILING);
ButtonI2C button14(&relayI2CBoard1, 4, Button::EDGE_TRAILING);
ButtonI2C button21(&relayI2CBoard2, 1, Button::EDGE_TRAILING);
ButtonI2C button22(&relayI2CBoard2, 2, Button::EDGE_LEADING);
ButtonI2C button23(&relayI2CBoard2, 3, Button::EDGE_TRAILING);
ButtonI2C button24(&relayI2CBoard2, 4, Button::EDGE_TRAILING);
ButtonGPIO buttonD7(7, Button::EDGE_TRAILING);
ButtonGPIO buttonD8(8, Button::EDGE_LEADING); // Day night detector

LightI2C light1(&relayWapper1, 1);
// LightGPIO light2(LED_2_PIN);

Timer timer1;
Timer timer2;

// // TODO: define sunState

Circuit circuit1(&button11, &light1, &timer1);
Circuit circuit2(&button12, &light1, &timer2);

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