
#include "hwSelect.hpp"

#ifdef ARD_I2C
#ifndef ARD_I2C_HPP
#define ARD_I2C_HPP

#include "I2cBus.hpp"

#include "Arduino.h"
#include "Wire.h"

class ArdI2c : public I2cBus
{
    public:
        static I2cBus* getInstance();
        virtual void writeBytes  (uint8_t regAddr, uint8_t devAddr, uint8_t* pData, uint8_t len);
        uint8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t* pBuf, uint8_t len);
    private:
        ArdI2c();
};

typedef ArdI2c I2c_t;

#endif
#endif
