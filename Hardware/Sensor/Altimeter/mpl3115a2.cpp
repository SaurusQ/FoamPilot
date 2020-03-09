
#include "mpl3115a2.hpp"

MPL3115A2::MPL3115A2()
    : Altimeter()
    , pI2cBus_(I2c_t::getInstance())
{
    this->init();
}

void MPL3115A2::init()
{
    pI2cBus_->writeByte(MPL3115A2_I2C_ADDR, MPL3115A2_CTRL_REG1, 0x88); // set OSR = 10ms
    pI2cBus_->writeByte(MPL3115A2_I2C_ADDR, MPL3115A2_PT_DATA_CFG, 0x07); // set data ready event
    pI2cBus_->writeByte(MPL3115A2_I2C_ADDR, MPL3115A2_CTRL_REG1, 0xB9); // set active
}

void MPL3115A2::reset()
{
    pI2cBus_->writeByte(MPL3115A2_I2C_ADDR, MPL3115A2_CTRL_REG1, 0x04); // reset bit
    this->init();
}

void MPL3115A2::update()
{
    // simple temp read
    // check for ready data
    uint8_t STA;
    do
    {
        STA = pI2cBus_->readByte(MPL3115A2_I2C_ADDR, MPL3115A2_STATUS);
    } while(!(STA & 0x08)); // is data ready

    uint8_t buf[3];
    pI2cBus_->readBytes(MPL3115A2_I2C_ADDR, MPL3115A2_OUT_P_MSB, buf, 3);
    
    uint32_t alt = 
        ((uint32_t)buf[0] << 24) |
        ((uint32_t)buf[1] << 16) |
        ((uint32_t)buf[2] << 8);

    altitude_ = alt / 655.36;
}