#include "SensorI2CKeypad.h"

SensorI2CKeypad::SensorI2CKeypad() : Sensor() {}

void SensorI2CKeypad::init()
{
    if (keypad.begin() == false)
    {
        Serial.println(F("Keypad does not appear to be connected. Please check wiring. Freezing..."));
        while (1)
        {
        }
    }
    Serial.print(F("Keypad Initialized. Firmware Version: "));
    Serial.println(keypad.getVersion());

    // // Set up interrupt pin.
    // pinMode(pin, INPUT);
}

bool SensorI2CKeypad::getState()
{
    // Get key from I2C.
    keypad.updateFIFO();
    char keyGot = keypad.getButton();

    if (keyGot == 0)
    {
        return false;
    }
    Serial.print(F("Got keypad data: "));
    Serial.println(keyGot);

    int n;
    // Move the first three values down one place.
    for (n = 0; n < 3; ++n)
    {
        keysPressed[n] = keysPressed[n + 1];
    }
    // Put the new key into the first spot.
    keysPressed[3] = keyGot;

    // Check the key history for the key combo we are looking for.
    bool keysMatch = true;
    for (n = 0; n < 4; ++n)
    {
        Serial.print(F("checking: "));
        Serial.print(n);
        Serial.print(F(": "));
        Serial.print(keysExpected[n]);
        Serial.print(F(" != "));
        Serial.print(keysPressed[n]);
        Serial.print(F(" = "));
        Serial.println(keysExpected[n] != keysPressed[n]);

        if (keysExpected[n] != keysPressed[n])
        {
            keysMatch = false;
        }
    }
    return keysMatch;
}
