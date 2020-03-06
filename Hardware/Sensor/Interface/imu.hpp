
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

typedef Imu_d3_uint16 ImuAccI;
typedef Imu_d3_uint16 ImuGyrI;
typedef Imu_d3_uint16 ImuComI;

typedef Imu_d3_float ImuAccF;
typedef Imu_d3_float ImuGyrF;
typedef Imu_d3_float ImuComF;

struct ImuData
{
    ImuAccI accelometer;
    ImuGyrI gyro;
    ImuComI compass;
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

        virtual ImuAccI getAccInt();
        virtual ImuGyrI getGyrInt();
        virtual ImuComI getComInt();
        virtual ImuAccF getAccFloat();
        virtual ImuGyrF getGyrFloat();
        virtual ImuComF getComFloat();
    protected:
        Imu_d3_float imuIntToFloat(Imu_d3_uint16 a);

        ImuData data_;

};

#endif
