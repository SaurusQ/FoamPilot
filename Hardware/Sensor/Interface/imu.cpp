
#include "imu.hpp"

ImuAccF Imu::getAccFloat() const
{
    return imuData_.accelometer;
}

ImuGyrF Imu::getGyrFloat() const
{
    return imuData_.gyro;
}

ImuComF Imu::getComFloat() const
{
    return imuData_.compass;
}

ImuData Imu::getImuData() const
{
    return imuData_;
}
