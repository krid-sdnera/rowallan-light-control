#include "Sensor.h"
Sensor::Sensor(byte _pin, int _edge) : pin(_pin), edgeDetection(_edge)
{
}
Sensor::~Sensor() {}

void Sensor::update()
{
    // You can handle the debounce of the sensor directly
    // in the class, so you don't have to think about it
    // elsewhere in your code
    byte newReading = getState();
    timeOfDepression = 0;

    Serial.println("sensor update:raw status");
    Serial.println(newReading);

    if (newReading != lastReading)
    {
        lastDebounceTime = millis();

        Serial.println("sensor update:changed");
        Serial.println(lastDebounceTime);
    }
    if (newReading != state && millis() - lastDebounceTime > debounceDelay)
    {
        // Update the 'state' attribute only if debounce is checked
        state = newReading;

        if (state == DEPRESSED)
        {
            lastDepressedTime = millis();
            timeOfDepression = 0;
        }
        else
        {
            // therefore newReading is Released
            // and return the delta
            timeOfDepression = millis() - lastDepressedTime;
        }

        Serial.println("sensor update:depression time");
        Serial.println(timeOfDepression);
    }
    lastReading = newReading;
}
bool Sensor::isPressed()
{
    return isLongPressed(100);
}
bool Sensor::isLongPressed(int duration)
{
    if (edgeDetection == Sensor::EDGE_LEADING)
    {
        return (state == DEPRESSED);
    }
    else
    {
        return (timeOfDepression > duration);
    }
}