
#ifndef MPL3115A2_HPP
#define MPL3115A2_HPP
#include "hwSelect.hpp"
#ifdef SELECT_MPL3115A2

#include "altimeter.hpp"
#include "I2cBus.hpp"

#define MPL3115A2_I2C_ADDR 0x60

#define MPL3115A2_STATUS      0x00
#define MPL3115A2_OUT_P_MSB   0x01
#define MPL3115A2_OUT_P_CSB   0x02
#define MPL3115A2_OUT_P_LSB   0x03
#define MPL3115A2_PT_DATA_CFG 0x13
#define MPL3115A2_CTRL_REG1   0x26

class MPL3115A2 : public Altimeter
{
    public:
        MPL3115A2();
        virtual ~MPL3115A2() {}

        virtual void init();
        virtual void reset();
        virtual void calibrate() {}
        virtual void update();
    protected:
        I2cBus* pI2cBus_;
};

typedef MPL3115A2 Altimeter_t;

#endif
#endif
