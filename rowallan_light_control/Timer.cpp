#include "Timer.h"
Timer::Timer() {}
Timer::Timer(unsigned long _almost) : almostDuration(_almost) {}
Timer::~Timer() {}
void Timer::start()
{
    start(-1, Timer::UNIT_MILLI);
}

void Timer::start(unsigned long duration)
{
    start(duration, Timer::UNIT_MILLI);
}

void Timer::start(unsigned long duration, unsigned int unit)
{
    clear();

    // Convert into seconds
    duration = duration * unit;

    duration = modifyDuration(duration);

    startTime = millis();
    expiryDuration = duration;
}

unsigned long Timer::modifyDuration(unsigned long duration)
{
    return duration;
}

bool Timer::isExpired()
{
    return ((millis() - startTime) > expiryDuration);
}

bool Timer::isAlmostExpired()
{
    if (almostDuration == 0)
    {
        return false;
    }

    return ((millis() - startTime) > (expiryDuration - almostDuration));
}

bool Timer::isStarted()
{
    return (startTime != 0);
}

void Timer::clear()
{
    startTime = 0;
    expiryDuration = 0;
}
