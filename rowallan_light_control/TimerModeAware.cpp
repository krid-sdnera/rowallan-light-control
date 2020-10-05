#include "TimerModeAware.h"
#include "AppState.h"
TimerModeAware::TimerModeAware(int _day, int _night, int _lateNight) : durationDay(_day), durationNight(_night), durationLateNight(_lateNight), Timer() {}
TimerModeAware::~TimerModeAware() {}

bool TimerModeAware::isExpired()
{
    byte targetMode = AppState::getInstance()->AppModeTransition(storedAppMode);
    int modeDuration = expiryDuration;

    switch (targetMode)
    {
    case AppState::MODE_DAY:
        modeDuration = durationDay;
        break;
    case AppState::MODE_NIGHT:
        modeDuration = durationNight;
        break;
    case AppState::MODE_LATE_NIGHT:
        modeDuration = durationLateNight;
        break;
    }

    // Set the expiry duration to the limit for this mode,
    // if there was no duration set when initially started.
    if (expiryDuration <= 0)
    {
        expiryDuration = modeDuration;
    }

    if (modeDuration < expiryDuration)
    {
        // The mode has changed and the duration needs to be shortened.
        // Restart the timer at now and update the duration.
        start(modeDuration);
    }

    // Store app mode
    storedAppMode = AppState::getInstance()->AppMode();

    return ((millis() - startTime) > expiryDuration);
}