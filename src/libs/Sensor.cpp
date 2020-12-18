#include "Sensor.h"
Sensor::Sensor() {}
Sensor::~Sensor() {}

void Sensor::update()
{
    // You can handle the debounce of the sensor directly
    // in the class, so you don't have to think about it
    // elsewhere in your code
    bool newReading = getState();

    if (newReading != lastReading)
    {
        // Save the time the reading changed.
        lastDebounceTime = millis();
    }
    if (newReading != state && millis() - lastDebounceTime > debounceDelay)
    {
        // Update the 'state' attribute only if debounce is checked
        state = newReading;
        lastStateChangeTime = millis();

        Serial.print("sensor update:state: ");
        Serial.println(state);
    }
    lastReading = newReading;
}

bool Sensor::isActive()
{
    return isActive(100);
}

bool Sensor::isActive(int duration)
{

    if (state == DEPRESSED)
    {
        // True if the sensor has been active for at least the duration
        return (millis() - lastStateChangeTime) > duration;
    }

    // The sensor is inactive
    return false;
}

bool Sensor::isInactive()
{
    return isInactive(100);
}

bool Sensor::isInactive(int duration)
{

    if (state != DEPRESSED)
    {
        // True if the sensor has been inactive for at least the duration
        return (millis() - lastStateChangeTime) > duration;
    }

    // The sensor is active
    return false;
}
