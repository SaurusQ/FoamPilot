
#ifndef AHRS_HPP
#define AHRS_HPP

#include "altimeter.hpp"
#include "imu.hpp"
#include "gps.hpp"

#include "MadgwickAHRS.hpp"

#include <math.h>

extern volatile float q0, q1, q2, q3;

struct Quaternion {
    float w, x, y, z;
};

struct EulerAngles {
    float roll, pitch, yaw;
};

class AHRS
{
    public:
        AHRS(Imu* pImu);
        ~AHRS();

        void update();
        EulerAngles ToEulerAngles(Quaternion q);

    private:
        Imu* pImu_;

};

#endif
