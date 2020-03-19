
#include "imu.hpp"

ImuAccF Imu::getAccFloat() const
{
    return ImuAccF{imuData_.ax, imuData_.ay, imuData_.az};
}

ImuGyrF Imu::getGyrFloat() const
{
    return ImuGyrF{imuData_.gx, imuData_.gy, imuData_.gz};
}

ImuComF Imu::getComFloat() const
{
    return ImuComF{imuData_.cx, imuData_.cy, imuData_.cz};
}

ImuData Imu::getImuData() const
{
    return imuData_;
}
