// sourced from: https://github.com/ncd-io/MCP23008/tree/master/Particle
#include "MCP23008.h"
#include "Wire.h"
#include <Arduino.h>
// #include "Particle.h"
// #include "spark_wiring_usbserial.h"

//Comment line below out to turn off Serial logging
//#define LOGGING
// MCP23008::MCP23008() : timer(100, &MCP23008::momentaryOff, *this, true) {}

MCP23008::MCP23008(){};
MCP23008::~MCP23008(){};

void MCP23008::setAddress(int a0, int a1, int a2)
{
    address |= (a0 * 1 + a1 * 2 + a2 * 4);
}

void MCP23008::setAddress(int a)
{
    address = a;
}

void MCP23008::setRelays(int num)
{
    relayCount = num;
    setOutputs(256 - (1 << num));
}
void MCP23008::setOutputs(int map)
{
    outputMap = map;
}
void MCP23008::setOutput(int num)
{
    outputMap = outputMap ^ (1 << num);
}

void MCP23008::setInputs(int map)
{
    inputMap = map;
}

void MCP23008::init()
{
    //Start I2C port
    Wire.begin();
    //Open connection to specified address
    sendCommand(0x00, outputMap);
    sendCommand(0x06, inputMap);
    readStatus();
}

void MCP23008::turnOnRelay(int relay)
{
    relayOp(relay, 1);
}
void MCP23008::turnOffRelay(int relay)
{
    relayOp(relay, 2);
}
void MCP23008::toggleRelay(int relay)
{
    relayOp(relay, 3);
}
void MCP23008::relayOp(int relay, int op)
{
    readStatus();
    byte rbit = (1 << (relay - 1));
    if ((outputMap & rbit) > 0)
        return;
    setBankStatus(bitop(bankStatus, rbit, op));
}
byte MCP23008::bitop(byte b1, byte b2, int op)
{
    if (op == 1)
        return b1 | b2;
    if (op == 2)
        return b1 & ~b2;
    if (op == 3)
        return b1 ^ b2;
    return 0;
}

void MCP23008::turnOnAllRelays()
{
    setBankStatus((255 ^ outputMap));
}

void MCP23008::turnOffAllRelays()
{
    setBankStatus(bankStatus & outputMap);
}

void MCP23008::setBankStatus(int status)
{
    sendCommand(0x0A, status);
    readStatus();
}

int MCP23008::readRelayStatus(int relay)
{
    int value = (1 << (relay - 1));
    if ((outputMap & value) > 0)
    {
        return 256;
    }
    byte bankStatus = readRelayBankStatus();
    if (bankStatus & value)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int MCP23008::readRelayBankStatus()
{
    int status = sendCommand(0x0A);
    return status;
}

void MCP23008::readStatus()
{
    byte status = readRelayBankStatus();
    bankStatus = status;
}

int MCP23008::readInputStatus(int input)
{
    if (!iosetCustom)
    {
        input += relayCount;
    }
    int inRangeBitmask = (1 << (input - 1));
    int inputBitmask = (1 << (input - relayCount - 1));
    if ((outputMap & inRangeBitmask) == 0)
    {
        return 256;
    }
    byte bankStatus = readAllInputs();
    if (bankStatus & inputBitmask)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int lastChanges[8];
int MCP23008::readAllInputs()
{
    byte status = sendCommand(0x09);
    byte inverted = ~status;
    byte shifted;
    if (!iosetCustom)
    {
        shifted = inverted >> relayCount;
    }
    else
    {
        shifted = inverted;
    }

    inputStatus = shifted;
    return shifted;
}
int MCP23008::sendCommand(int reg)
{
    return sendCommand(reg, 256);
}

int MCP23008::sendCommand(int reg, int cmd)
{
    int status = 256;
    while (retrys < 4 && status > 0)
    {
        Wire.beginTransmission(address);
        Wire.write(reg);
        if (cmd < 256)
            Wire.write(cmd);
        status = Wire.endTransmission();
        retrys++;
    }
    initialized = false;
    int ret = 256;
    if (retrys < 4)
    {
        initialized = true;
        Wire.requestFrom(address, 1);
        ret = Wire.read();
    }
    retrys = 0;
    return ret;
}
