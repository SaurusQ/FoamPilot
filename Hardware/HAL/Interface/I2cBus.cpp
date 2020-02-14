
#include "I2cBus.hpp"

void I2cBus::writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
    this->writeBytes(devAddr, regAddr, &data, 1);
}

void I2cBus::writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t bitMask)
{
    uint8_t oldData = I2cBus::readByte(devAddr, regAddr);
    this->writeByte(devAddr, regAddr, (data & bitMask) | oldData);
}

void I2cBus::writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t bitNum)
{
    uint8_t oldData = I2cBus::readByte(devAddr, regAddr);
    this->writeByte(devAddr, regAddr, data ? (oldData | (0x01 << bitNum)) : (oldData & ~(0x01 << bitNum)));
}

uint8_t I2cBus::readByte(uint8_t devAddr, uint8_t regAddr)
{
    uint8_t byte;
    this->readBytes(devAddr, regAddr, &byte, 1);
    return byte;
}

uint8_t I2cBus::readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum)
{
    uint8_t byte;
    this->readBytes(devAddr, regAddr, &byte, 1);
    return (byte >> bitNum) & 0x01;
}
