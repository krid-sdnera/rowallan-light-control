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
    daylightSensor = _sensor;
    daylightSensor->init();
}

void AppState::setLateNightTimer(Timer *_timer)
{
    lateNightTimer = _timer;
}

void AppState::setNightLight(Light *_light)
{
    nightLight = _light;
    nightLight->init();
}

void AppState::setStatusIndicatorLight(Light *_light)
{
    statusIndicatorLight = _light;
    statusIndicatorLight->init();
}

void AppState::setStatusIndicatorTimer(Timer *_timer)
{
    statusIndicatorTimer = _timer;
}

void AppState::updateMode()
{
    daylightSensor->update();
    if (daylightSensor->isActive())
    {
        // Mode: Night or Late Night
        if (!lateNightTimer->isStarted())
        {
            // 6 * 60 = 6h
            lateNightTimer->start(360, Timer::UNIT_MINUTE);
        }

        if (lateNightTimer->isExpired())
        {
            mode = AppState::MODE_LATE_NIGHT;
        }
        else
        {
            mode = AppState::MODE_NIGHT;
        }

        // If the a night light is defined and off, turn it on.
        if (nightLight != 0 && !nightLight->isOn())
        {
            Serial.println(F("night light update:on:NIGHT"));
            nightLight->on();
        }
    }
    else
    {
        // Mode: Day
        mode = AppState::MODE_DAY;
        lateNightTimer->clear();

        // If the a night light is defined and on, turn it off.
        if (nightLight != 0 && nightLight->isOn())
        {
            Serial.println(F("night light update:off:DAY"));
            nightLight->off();
        }
    }
}

void AppState::updateStatusIndicator()
{
    // Mode 1: Day time mode
    if (AppState::getInstance()->AppMode() == AppState::MODE_DAY)
    {
        // TODO: Check if there is at least one circuit in override mode.
        if (statusIndicatorLight->isOn() && statusIndicatorTimer->isExpired())
        {
            Serial.println(F("status light update:off:DAY"));
            statusIndicatorLight->off();
            statusIndicatorTimer->start(5000);
        }
        if (!statusIndicatorLight->isOn() && statusIndicatorTimer->isExpired())
        {
            Serial.println(F("status light update:on:DAY"));
            statusIndicatorLight->on();
            statusIndicatorTimer->start(1000);
        }
    }
    // Mode 2: Night time mode
    if (AppState::getInstance()->AppMode() == AppState::MODE_NIGHT)
    {
        if (statusIndicatorLight->isOn() && statusIndicatorTimer->isExpired())
        {
            Serial.println(F("status light update:off:NIGHT"));
            statusIndicatorLight->off();
            statusIndicatorTimer->start(2000);
        }
        if (!statusIndicatorLight->isOn() && statusIndicatorTimer->isExpired())
        {
            Serial.println(F("status light update:on:NIGHT"));
            statusIndicatorLight->on();
            statusIndicatorTimer->start(2000);
        }
    }
    // Mode 3: Late night time mode
    if (AppState::getInstance()->AppMode() == AppState::MODE_LATE_NIGHT)
    {
        if (statusIndicatorLight->isOn() && statusIndicatorTimer->isExpired())
        {
            Serial.println(F("status light update:off:LATENIGHT"));
            statusIndicatorLight->off();
            statusIndicatorTimer->start(4000);
        }
        if (!statusIndicatorLight->isOn() && statusIndicatorTimer->isExpired())
        {
            Serial.println(F("status light update:on:LATENIGHT"));
            statusIndicatorLight->on();
            statusIndicatorTimer->start(4000);
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
