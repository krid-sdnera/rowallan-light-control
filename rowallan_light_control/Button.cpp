#include "Button.h"
Button::Button(byte _pin) : pin(_pin)
{
}
Button::~Button() {}

void Button::update()
{
    // You can handle the debounce of the button directly
    // in the class, so you don't have to think about it
    // elsewhere in your code
    byte newReading = getState();
    timeOfDepression = 0;

    Serial.println("button update:raw status");
    Serial.println(newReading);

    if (newReading != lastReading)
    {
        lastDebounceTime = millis();

        Serial.println("button update:changed");
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

        Serial.println("button update:depression time");
        Serial.println(timeOfDepression);
    }
    lastReading = newReading;
}
bool Button::isPressed()
{
    return (timeOfDepression > 100);
}
bool Button::isLongPressed(int duration)
{
    return (timeOfDepression > duration);
}