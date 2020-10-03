#include "Timer.h"
Timer::Timer() {}
Timer::~Timer() {}
void Timer::start()
{
    start(-1, Timer::UNIT_SECOND);
}

void Timer::start(int duration)
{
    start(duration, Timer::UNIT_SECOND);
}

void Timer::start(int duration, int unit)
{
    // Convert into seconds
    duration = duration * unit;

    startTime = millis();
    expiryDuration = duration;
}
bool Timer::isExpired()
{
    return ((millis() - startTime) > expiryDuration);
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