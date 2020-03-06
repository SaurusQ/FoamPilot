
#ifndef IMU_HPP
#define IMU_HPP

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

class Imu
{
    public:
        Imu() {}
        virtual ~Imu();
        
        virtual void calibrate() =  0;
        virtual void update();
        virtual void isHealhty() = 0;

        virtual ImuAccI getAccInt();
        virtual ImuGyrI getGyrInt();
        virtual ImuComI getComInt();
        virtual ImuAccF getAccFloat();
        virtual ImuGyrF getGyrFloat();
        virtual ImuComF getComFloat();
    protected:
        Imu_d3_float imuFloatToInt(Imu_d3_uint16 a);
};

#endif
