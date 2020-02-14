
#ifndef I2CBUS_HPP
#define I2CBUS_HPP

#include <inttypes.h>

class I2cBus
{
    public:
        I2cBus(I2cBus const&) = delete;
        void operator=(I2cBus const&) = delete;

        virtual void writeBytes  (uint8_t devAddr, uint8_t regAddr, uint8_t* pData, uint8_t len) = 0;
        virtual void writeByte   (uint8_t devAddr, uint8_t regAddr, uint8_t data);
        virtual void writeBits   (uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t bitMask);
        virtual void writeBit    (uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t bitNum);
        
        virtual uint8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t* pBuf, uint8_t len) = 0;
        virtual uint8_t readByte (uint8_t devAddr, uint8_t regAddr);
        virtual uint8_t readBit  (uint8_t devAddr, uint8_t regAddr, uint8_t bitNum);

    protected:
        I2cBus() {}
        virtual ~I2cBus() {}
};

#endif
