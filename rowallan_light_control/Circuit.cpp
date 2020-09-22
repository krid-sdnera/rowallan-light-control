#include "Circuit.h"
#include "Button.h"
#include "Light.h"
#include "Timer.h"

Circuit::Circuit(Button *b, Light *l, Timer *t) : button(b), light(l), timer(t) {}

Circuit::~Circuit() {}

void Circuit::init()
{
    button->init();
    light->init();
    // timer->init();
}
void Circuit::update()
{
    Serial.println("circuit update");

    button->update();
    if (button->isPressed())
    {
        Serial.println("circuit update:pressed");
        light->toggle();
        timer->start(10000);
    }
    else
    {
        Serial.println("circuit update:not pressed");

        if (light->isOn() && timer->isExpired())
        {
            light->off();
        }
    }
}
