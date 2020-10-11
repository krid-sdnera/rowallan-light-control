#include "Timer.h"
Timer::Timer() {}
Timer::Timer(int _almost) : almostDuration(_almost) {}
Timer::~Timer() {}
void Timer::start()
{
    start(-1, Timer::UNIT_MILLI);
}

void Timer::start(int duration)
{
    start(duration, Timer::UNIT_MILLI);
}

void Timer::start(int duration, unsigned int unit)
{
    clear();

    // Convert into seconds
    duration = duration * unit;

    duration = modifyDuration(duration);

    startTime = millis();
    expiryDuration = duration;
}

int Timer::modifyDuration(int duration)
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
