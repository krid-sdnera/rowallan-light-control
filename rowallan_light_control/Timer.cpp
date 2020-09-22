#include "Timer.h"
Timer::Timer() {}
Timer::~Timer() {}
void Timer::start(int duration)
{
    startTime = millis();
    expiryDuration = duration;
}
bool Timer::isExpired()
{
    return ((millis() - startTime) > expiryDuration);
}