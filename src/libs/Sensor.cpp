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

        Serial.print(F("sensor update:state: "));
        Serial.println(state);
    }
    lastReading = newReading;
}

bool Sensor::isActive()
{
    return isActive(100, Sensor::MODE_LEADING_EDGE);
}

bool Sensor::isActive(int duration)
{
    return isActive(duration, Sensor::MODE_LEADING_EDGE);
}

bool Sensor::isActive(const byte mode)
{
    return isActive(100, mode);
}

bool Sensor::isActive(int duration, byte mode)
{
    switch (mode)
    {
    case Sensor::MODE_LEADING_EDGE:
        // True if the sensor has been active for at least the duration.
        // False if the sensor is not depressed or has not yet reached the `duration`.
        return (state == DEPRESSED) ? (millis() - lastStateChangeTime) > duration : false;
    case Sensor::MODE_BOTH_EDGE:
        // True if the sensor has changed state, up until 500 ms later.
        return lastStateChangeTime != 0 && (millis() - lastStateChangeTime) > duration && (millis() - lastStateChangeTime) < 500;
    default:
        return false;
    }
}
