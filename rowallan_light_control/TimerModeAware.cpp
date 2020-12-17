#include "TimerModeAware.h"
#include "AppState.h"
TimerModeAware::TimerModeAware(unsigned long _day, unsigned long _night, unsigned long _lateNight, unsigned long _almost) : durationDay(_day), durationNight(_night), durationLateNight(_lateNight), Timer(_almost) {}
TimerModeAware::~TimerModeAware() {}

unsigned long TimerModeAware::modifyDuration(unsigned long duration)
{
    if (!isStarted())
    {
        storedAppMode = 0;
    }
    byte targetMode = AppState::getInstance()->AppModeTransition(storedAppMode);
    unsigned long modeDuration = duration;

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
    if (duration <= 0)
    {
        duration = modeDuration;
    }

    if (modeDuration < duration)
    {
        // The mode has changed and the duration needs to be shortened.
        // Restart the timer at now and update the duration.
        start(modeDuration);
        // Also return the updated duration just incase.
        duration = modeDuration;
    }

    // Store app mode
    storedAppMode = AppState::getInstance()->AppMode();

    return duration;
}

bool TimerModeAware::isExpired()
{
    // Modify but dont save, if the duration needs to be shortened
    // then the timer should be restarted automatically.
    modifyDuration(expiryDuration);

    return ((millis() - startTime) > expiryDuration);
}
