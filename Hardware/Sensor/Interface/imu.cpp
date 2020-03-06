
#include "imu.hpp"

ImuAccI Imu::getAccInt()
{
    return data_.accelometer;
}

ImuGyrI Imu::getGyrInt()
{
    return data_.gyro;
}

ImuComI Imu::getComInt()
{
    return data_.compass;
}

ImuAccF Imu::getAccFloat()
{
    return this->imuIntToFloat(this->getAccInt());
}

ImuGyrF Imu::getGyrFloat()
{
    return this->imuIntToFloat(this->getGyrInt());
}

ImuComF Imu::getComFloat()
{
    return this->imuIntToFloat(this->getComInt());
}

Imu_d3_float Imu::imuIntToFloat(Imu_d3_uint16 a)
{
    Imu_d3_float b;
    b.x = static_cast<float>(a.x);
    b.y = static_cast<float>(a.y);
    b.z = static_cast<float>(a.z);
    return b;
}
