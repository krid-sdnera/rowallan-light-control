#include "AppState.h"

/* Null, because instance will be initialized on demand. */
AppState *AppState::instance = 0;

AppState *AppState::getInstance()
{
    if (instance == 0)
    {
        instance = new AppState();
    }

    return instance;
}

AppState::AppState() {}
AppState::~AppState() {}
void AppState::setDaylightSensor(Sensor *_sensor)
{
    sensor = _sensor;
}
void AppState::setLateNightTimer(Timer *_timer)
{
    timer = _timer;
}

void AppState::update()
{
    sensor->update();
    if (sensor->isPressed())
    {
        // Mode: Day
        mode = AppState::MODE_DAY;
        timer->clear();
    }
    else
    {
        // Mode: Night or Late Night
        if (!timer->isStarted())
        {
            timer->start(6, Timer::UNIT_SECOND);
        }

        if (timer->isExpired())
        {
            mode = AppState::MODE_LATE_NIGHT;
        }
        else
        {
            mode = AppState::MODE_NIGHT;
        }
    }
}
int AppState::AppMode()
{
    return mode;
}
int AppState::AppModeTransition(byte currentMode)
{
    // Poormans state engine
    if (currentMode == mode)
    {
        // There has been no change
        return 0;
    }

    return mode;
}
