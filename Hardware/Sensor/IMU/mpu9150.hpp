
#ifndef MPU9150_HPP
#define MPU9150_HPP
#include "hwSelect.hpp"
#ifdef SELECT_MPU9150

#include "imu.hpp"
#include "I2cBus.hpp"

#define MPU9150_I2C_ADDR        0x68

#define MPU9150_GYRO_CONFIG     0x27
#define MPU9150_ACCEL_CONFIG    0x28
#define MPU9150_ACCEL_XOUT_H    0x3B
#define MPU9150_PWR_MGMT_1      0x6B

// compass
#define MPU9150_MAG_I2C_ADDR    0x0C

#define MPU9150_MAG_XOUT_L      0x03
#define MPU9150_INT_PIN_CFG     0x37

enum AccelSens {
    FS_2 =      0x00,
    FS_4 =      0x01,
    FS_8 =      0x02,
    FS_16 =     0x03,
};

enum GyroSens {
    FS_250 =    0x00,
    FS_500 =    0x01,
    FS_1000 =   0x02,
    FS_2000 =   0x03,
};

class MPU9150 : public Imu
{
    public:
        MPU9150();
        virtual ~MPU9150() {}

        virtual void init();
        virtual void reset();
        virtual void calibrate();
        virtual void update();
        virtual void isHealhty();

        virtual void setAccelSens(AccelSens sens);
        virtual void setGyroSens(GyroSens sens);
        virtual void setSleepEnabled(bool enabled);
    protected:
        I2cBus* pI2cBus_;

};

#endif
#endif
