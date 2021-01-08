#include <SPI.h>
#include <EthernetServer.h>
#include <Ethernet.h>

#include "Arduino.h"
#include "LightGPIO.h"
#include "SensorGPIO.h"
#include "TimerModeAware.h"
#include "Circuit.h"

#include "RestServer.h"

SensorGPIO sensorTest(7);
LightGPIO lightTest(9);
TimerModeAware timerTest(0, 1800000ul, 1800000ul, 0);
Circuit circuitTest(&sensorTest, &lightTest, &timerTest, Circuit::MODE_ON, 100);

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {10, 90, 10, 70};
EthernetServer server(80);
RestServer api(&server);

void setup()
{
    Serial.begin(9600);
    Serial.println(F("initialising"));

    api.begin(mac, ip);

    circuitTest.init();

    Serial.println(F("initialisation done"));
}

void loop()
{
    api.serve();

    circuitTest.update();
}
