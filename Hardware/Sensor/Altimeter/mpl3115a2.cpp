
#include "mpl3115a2.hpp"

Mpl3115a2::Mpl3115a2()
    : Altimeter()
    , pI2cBus_(I2c_t::getInstance())
{
    this->init();
}

void Mpl3115a2::init()
{
    pI2cBus_->writeByte(I2C_ADDR, CTRL_REG1, 0x88); // set OSR = 10ms
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

    uint8_t buf[3];
    pI2cBus_->readBytes(I2C_ADDR, OUT_P_MSB, buf, 3);
    
    uint32_t alt = 
        ((uint32_t)buf[0] << 24) |
        ((uint32_t)buf[1] << 16) |
        ((uint32_t)buf[3] << 8);
    
    altitude_ = alt / 65536;
}