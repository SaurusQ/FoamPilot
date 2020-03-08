
#ifndef MPU9150_HPP
#define MPU9150_HPP
#include "hwSelect.hpp"
#ifdef MPU9150

#include "imu.hpp"

class Mpu9150 : public Imu
{
    public:
        Mpu9150();
        virtual ~Mpu9150() {}

        virtual void init();
        virtual void reset();
        virtual void calibrate();
        virtual void update();
        virtual void isHealhty();
    private:

};

#endif
#endif
