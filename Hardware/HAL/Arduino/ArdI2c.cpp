
#include "ArdI2c.hpp"

ArdI2c::ArdI2c()
    : I2cBus()
{
    Wire.begin();
    Wire.setClock(400000);
}

I2cBus* ArdI2c::getInstance()
{
    static ArdI2c instance;
    return &instance;
}

void ArdI2c::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t* pData, uint8_t len)
{
    Wire.beginTransmission(devAddr);
    Wire.write(regAddr);
    Wire.write(pData, len);
    Wire.endTransmission(true);
}

uint8_t ArdI2c::readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t* pBuf, uint8_t len)
{
    Wire.beginTransmission(devAddr);
    Wire.write(regAddr);
    Wire.endTransmission(false);
    Wire.requestFrom(devAddr, len, true);
    for(int i = 0; i < len; i++)
    {
        pBuf[i] = Wire.read();
    }
    Wire.endTransmission(true);
    return 0;
}
