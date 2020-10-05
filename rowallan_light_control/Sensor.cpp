#include "Sensor.h"
Sensor::Sensor(byte _pin, byte _edge) : pin(_pin), edgeDetection(_edge) {}
Sensor::~Sensor() {}

void Sensor::update()
{
    // You can handle the debounce of the sensor directly
    // in the class, so you don't have to think about it
    // elsewhere in your code
    bool newReading = getState();
    timeOfDepression = 0;

    if (newReading != lastReading)
    {
        // Save the time the reading changed.
        lastDebounceTime = millis();
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

        Serial.print("sensor update:state: ");
        Serial.println(state);
    }
    lastReading = newReading;
}
bool Sensor::isPressed()
{
    return isPressed(100);
}
bool Sensor::isPressed(int duration)
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