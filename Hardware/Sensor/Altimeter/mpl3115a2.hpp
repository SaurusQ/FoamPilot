
#ifndef MPL3115A2_HPP
#define MPL3115A2_HPP
#include "hwSelect.hpp"
#ifdef MPL3115A2

#include "altimeter.hpp"
#include "I2cBus.hpp"

#define I2C_ADDR 0x60

#define STATUS      0x00
#define OUT_P_MSB   0x01
#define OUT_P_CSB   0x02
#define OUT_P_LSB   0x03
#define PT_DATA_CFG 0x13
#define CTRL_REG1   0x26

class Mpl3115a2 : public Altimeter
{
    public:
        Mpl3115a2();
        virtual ~Mpl3115a2() {}

        virtual void init();
        virtual void reset();
        virtual void calibrate() {}
        virtual void update();
    protected:
        I2cBus* pI2cBus_;
};

typedef Mpl3115a2 Altimeter_t;

#endif
#endif
