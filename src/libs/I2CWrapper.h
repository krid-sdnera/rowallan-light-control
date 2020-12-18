#ifndef I2CWrapper_H
#define I2CWrapper_H
#include <Arduino.h>
#include "MCP23008.h"

class I2CWrapper
{

private:
  /* Here will be the instance stored. */
  // static I2CWrapper *instance;

  /* Private constructor to prevent instancing. */
  MCP23008 relayController;

public:
  I2CWrapper(byte a0, byte a1, byte a2);
  /* Static access method. */
  // static I2CWrapper *getInstance();

  virtual ~I2CWrapper();
  void init();
  MCP23008 rc();
};
#endif
