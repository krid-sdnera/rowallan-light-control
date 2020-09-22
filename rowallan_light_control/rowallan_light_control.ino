#include "Arduino.h"

#include "MCP23008.h"

// #include "Light.h"
#include "LightI2C.h"
#include "ButtonGPIO.h"
#include "ButtonI2C.h"
#include "Timer.h"

#include "Circuit.h"

#define LED_1_PIN 1
// #define LED_2_PIN 10
#define BUTTON_1_PIN 1
#define BUTTON_2_PIN 7

// // Define the two relay boards
MCP23008 RelayController1;
// // We only need one for testing
// // MCP23008 RelayController2();

I2CWrapper relayWapper1(0, 0, 0);
// // I2CWrapper relayWapper2(RelayController2, 1, 1, 0);

ButtonI2C button1(&relayWapper1, BUTTON_1_PIN);
ButtonI2C button2(&relayWapper1, 2);
ButtonI2C button3(&relayWapper1, 3);
ButtonI2C button4(&relayWapper1, 4);
ButtonGPIO button5(BUTTON_2_PIN);

LightI2C light1(&relayWapper1, LED_1_PIN);
// LightGPIO light2(LED_2_PIN);

Timer timer1;
Timer timer2;

// // TODO: define sunState

Circuit circuit1(
    // sunState,
    &button1,
    &light1,
    &timer1);

Circuit circuit2(
    // sunState,
    &button5,
    &light1,
    &timer2);

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
    // Serial.println("not loop");
    // Serial.println(relayWapper1.rc().readAllInputs());
    // Serial.println(relayWapper1.rc().readInputStatus(1));
    // Serial.println(relayWapper1.rc().readInputStatus(2));
    // Serial.println(relayWapper1.rc().readInputStatus(3));
    // Serial.println(relayWapper1.rc().readInputStatus(4));
    // Serial.println(relayWapper1.rc().readInputStatus(5));
    // button2.update();
    // button3.update();
    // button4.update();
    // Serial.println(button2.isPressed());
    // Serial.println(button3.isPressed());
    // Serial.println(button4.isPressed());

    Serial.println("loop: begin");

    circuit1.update();
    // circuit2.update();
    // circuit2.update();
    // circuit3.update();
    // circuit4.update();
    // circuit5.update();
    // circuit6.update();
    // circuit7.update();
}