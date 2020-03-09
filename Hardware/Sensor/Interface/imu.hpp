
#ifndef IMU_HPP
#define IMU_HPP

#include <inttypes.h>

struct Imu_d3_uint16
{
    int16_t x;
    int16_t y;
    int16_t z;
};

struct Imu_d3_float
{
    float x;
    float y;
    float z;
};

typedef Imu_d3_float ImuAccF;
typedef Imu_d3_float ImuGyrF;
typedef Imu_d3_float ImuComF;

struct ImuData
{
    ImuAccF accelometer;
    ImuGyrF gyro;
    ImuComF compass;
};

class Imu
{
    public:
        Imu() {}
        virtual ~Imu() {};

        virtual void init() = 0;
        virtual void reset() = 0;
        virtual void calibrate() =  0;
        virtual void update() = 0;
        virtual void isHealhty() = 0;

        ImuAccF getAccFloat() const;
        ImuGyrF getGyrFloat() const;
        ImuComF getComFloat() const;
        ImuData getImuData() const;
    protected:
        ImuData imuData_;

};

#endif
