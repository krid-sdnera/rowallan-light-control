#include "Light.h"

Light::Light(byte _pin) : pin(_pin) {}
Light::~Light() {}

void Light::flashUpdate()
{
    if (flashTime == 0)
    {
        return;
    }

    if ((millis() - flashTime) > 300)
    {
        // 300 ms have passed so we need to turn the light back on.
        on();
        flashTime = 0;
    }
}

void Light::flash()
{
    if (flashTime != 0)
    {
        return;
    }

    flashTime = millis();
    off();
}
