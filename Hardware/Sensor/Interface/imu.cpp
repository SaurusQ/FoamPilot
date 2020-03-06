
#include "imu.hpp"



ImuAccF Imu::getAccFloat()
{
    return this->imuFloatToInt(this->getAccInt());
}

ImuGyrF Imu::getGyrFloat()
{
    return this->imuFloatToInt(this->getGyrInt());
}

ImuComF Imu::getComFloat()
{
    return this->imuFloatToInt(this->getComInt());
}

Imu_d3_float Imu::imuFloatToInt(Imu_d3_uint16 a)
{
    Imu_d3_float b;
    b.x = static_cast<float>(a.x);
    b.y = static_cast<float>(a.y);
    b.z = static_cast<float>(a.z);
    return b;
}
