
#include "mpu9150.hpp"

MPU9150::MPU9150()
    : Imu()
    , pI2cBus_(I2c_t::getInstance())
{
    // default sensitivy multipliers if not set on init
    gyroSensMult_ = 250 / (float)SHRT_MAX;
    accSensMult_ = 2 / (float)SHRT_MAX;
    compSensMult_ = 1229 / 4095.0f;

    this->init();
}

void MPU9150::init()
{
    this->setSleepEnabled(false);
    this->setAccelSens(AccelSens::FS_2);
    this->setGyroSens(GyroSens::FS_250);
    // TODO set clock source
}

void MPU9150::reset()
{
    pI2cBus_->writeBit(MPU9150_I2C_ADDR, MPU9150_PWR_MGMT_1, 0x01, 7);
    this->init();
}

void MPU9150::calibrate()
{

}

void MPU9150::update()
{
    // read accelometer and gyro
    uint8_t buffer[14];
    pI2cBus_->readBytes(MPU9150_I2C_ADDR, MPU9150_ACCEL_XOUT_H, buffer, 14);

    imuData_.ax = static_cast<float>((((int16_t)buffer[0]) << 8)  | buffer[1]) * accSensMult_;
    imuData_.ay = static_cast<float>((((int16_t)buffer[2]) << 8)  | buffer[3]) * accSensMult_;
    imuData_.az = static_cast<float>((((int16_t)buffer[4]) << 8)  | buffer[5]) * accSensMult_;
    imuData_.gx = static_cast<float>((((int16_t)buffer[8]) << 8)  | buffer[9]) * gyroSensMult_;
    imuData_.gy = static_cast<float>((((int16_t)buffer[10]) << 8) | buffer[11]) * gyroSensMult_;
    imuData_.gz = static_cast<float>((((int16_t)buffer[12]) << 8) | buffer[13]) * gyroSensMult_;

    // read compass
    pI2cBus_->writeByte(MPU9150_I2C_ADDR, MPU9150_INT_PIN_CFG, 0x02); //set i2c bypass enable pin to true to access magnetometer
    //delay(10);
    pI2cBus_->writeByte(MPU9150_MAG_I2C_ADDR, 0x0A, 0x01); //enable the magnetometer
    //delay(10);
    pI2cBus_->readBytes(MPU9150_MAG_I2C_ADDR, MPU9150_MAG_XOUT_L, buffer, 6);
    imuData_.cx = static_cast<float>((((int16_t)buffer[0]) << 8) | buffer[1]) * compSensMult_;
    imuData_.cy = static_cast<float>((((int16_t)buffer[2]) << 8) | buffer[3]) * compSensMult_;
    imuData_.cz = static_cast<float>((((int16_t)buffer[4]) << 8) | buffer[5]) * compSensMult_;
}

void MPU9150::isHealhty()
{

}

void MPU9150::setAccelSens(AccelSens sens)
{
    pI2cBus_->writeBits(MPU9150_I2C_ADDR, MPU9150_ACCEL_CONFIG, sens, 4, 2);
    switch(sens)
    {
        case AccelSens::FS_2:
            accSensMult_ = 2.0f / (float)SHRT_MAX;
            break;
        case AccelSens::FS_4:
            accSensMult_ = 4.0f / (float)SHRT_MAX;
            break;
        case AccelSens::FS_8:
            accSensMult_ = 8.0f / (float)SHRT_MAX;
            break;
        case AccelSens::FS_16:
            accSensMult_ = 16.0f / (float)SHRT_MAX;
            break;
    }
}

void MPU9150::setGyroSens(GyroSens sens)
{
    pI2cBus_->writeBits(MPU9150_I2C_ADDR, MPU9150_GYRO_CONFIG, sens, 4, 2);
    switch(sens)
    {
        case GyroSens::FS_250:
            gyroSensMult_ = 250.0f / (float)SHRT_MAX;
            break;
        case GyroSens::FS_500:
            gyroSensMult_ = 500.0f / (float)SHRT_MAX;
            break;
        case GyroSens::FS_1000:
            gyroSensMult_ = 1000.0f / (float)SHRT_MAX;
            break;
        case GyroSens::FS_2000:
            gyroSensMult_ = 2000.0f / (float)SHRT_MAX;
            break;
    }
}

void MPU9150::setSleepEnabled(bool enabled)
{
    pI2cBus_->writeBit(MPU9150_I2C_ADDR, MPU9150_PWR_MGMT_1, enabled, 6);
}
