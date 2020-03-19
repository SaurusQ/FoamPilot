
#include "AHRS.hpp"

#include "Arduino.h"

AHRS::AHRS(Imu* pImu)
    : pImu_(pImu)    
{

}

AHRS::~AHRS()
{
    delete pImu_;
}

void AHRS::update()
{
    pImu_->update();
    ImuData d = pImu_->getImuData();

    #if 0
    MadgwickAHRSupdate( d.gx, d.gy, d.gz, 
                        d.ax, d.ay, d.az,
                        d.cx, d.cy, d.cz);
    #else
    MadgwickAHRSupdateIMU(d.gx, d.gy, d.gz, 
                        d.ax, d.ay, d.az);
    #endif
    Quaternion quad = {q0, q1, q2, q3};
    EulerAngles e = this->ToEulerAngles(quad);
    Serial.print(e.pitch);
    Serial.print(" ");
    Serial.print(e.roll);
    Serial.print(" ");
    Serial.println(e.yaw);
}

EulerAngles AHRS::ToEulerAngles(Quaternion q) {
    EulerAngles angles;

    // roll (x-axis rotation)
    float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    angles.roll = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    float sinp = 2 * (q.w * q.y - q.z * q.x);
    if (abs(sinp) >= 1)
        angles.pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        angles.pitch = asin(sinp);

    // yaw (z-axis rotation)
    float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
    angles.yaw = atan2(siny_cosp, cosy_cosp);

    return angles;
}