#include "SensorI2CKeypad.h"

SensorI2CKeypad::SensorI2CKeypad(byte _pin) : Sensor(_pin) {}

void SensorI2CKeypad::init()
{
    if (keypad.begin() == false)
    {
        Serial.println("Keypad does not appear to be connected. Please check wiring. Freezing...");
        while (1)
        {
        }
    }
    Serial.print("Keypad Initialized. Firmware Version: ");
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
    Serial.print("Got keypad data: ");
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
        Serial.print("checking: ");
        Serial.print(n);
        Serial.print(": ");
        Serial.print(keysExpected[n]);
        Serial.print(" != ");
        Serial.print(keysPressed[n]);
        Serial.print(" = ");
        Serial.println(keysExpected[n] != keysPressed[n]);

        if (keysExpected[n] != keysPressed[n])
        {
            keysMatch = false;
        }
    }
    return keysMatch;
}
