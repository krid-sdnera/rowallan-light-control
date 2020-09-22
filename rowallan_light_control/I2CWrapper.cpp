#include "I2CWrapper.h"
#include "MCP23008.h"

/* Null, because instance will be initialized on demand. */
// I2CWrapper *I2CWrapper::instance = 0;

// I2CWrapper *I2CWrapper::getInstance()
// {
//     if (instance == 0)
//     {
//         instance = new I2CWrapper(0, 0, 0);
//     }

//     return instance;
// }

I2CWrapper::I2CWrapper(int a0, int a1, int a2)
{
    // relayController is constructed with no args in the header
    relayController.setAddress(a0, a1, a2);
    relayController.setRelays(4);
    relayController.setInputs(240); // BitMask
}
I2CWrapper::~I2CWrapper() {}
void I2CWrapper::init()
{
    relayController.init();
}
MCP23008 I2CWrapper::rc()
{
    return relayController;
}
