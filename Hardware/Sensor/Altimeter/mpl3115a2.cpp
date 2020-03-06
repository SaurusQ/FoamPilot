
#include "mpl3115a2.hpp"

Mpl3115a2::Mpl3115a2()
    : Altimeter()
    , pI2cBus_(I2c_t::getInstance())
{
    this->init();
}

void Mpl3115a2::init()
{
    pI2cBus_->writeByte(I2C_ADDR, CTRL_REG1, 0xB8); // set OSR = 128
    pI2cBus_->writeByte(I2C_ADDR, PT_DATA_CFG, 0x07); // set data ready event
    pI2cBus_->writeByte(I2C_ADDR, CTRL_REG1, 0xB9); // set active
}

void Mpl3115a2::reset()
{
    pI2cBus_->writeByte(I2C_ADDR, CTRL_REG1, 0x04); // reset bit
    this->init();
}

void Mpl3115a2::update()
{
    // simple temp read
    // check for ready data
    uint8_t STA;
    do
    {
        STA = pI2cBus_->readByte(I2C_ADDR, STATUS);
    } while(!(STA & 0x08)); // is data ready

    uint8_t msb = pI2cBus_->readByte(I2C_ADDR, OUT_P_MSB);
    uint8_t csb = pI2cBus_->readByte(I2C_ADDR, OUT_P_CSB);
    uint8_t lsb = pI2cBus_->readByte(I2C_ADDR, OUT_P_LSB);

    altitude_ = 
        ((msb & ~(0x01 << 7)) << 12) |
        (csb << 4) |
        (lsb & 0x0F);
}