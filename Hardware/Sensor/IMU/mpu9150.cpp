
#include "mpu9150.hpp"

MPU9150::MPU9150()
    : Imu()
    , pI2cBus_(I2c_t::getInstance())
{
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

    imuData_.accelometer.x = static_cast<float>((((int16_t)buffer[0]) << 8)  | buffer[1]);
    imuData_.accelometer.y = static_cast<float>((((int16_t)buffer[2]) << 8)  | buffer[3]);
    imuData_.accelometer.z = static_cast<float>((((int16_t)buffer[4]) << 8)  | buffer[5]);
    imuData_.gyro.x =        static_cast<float>((((int16_t)buffer[8]) << 8)  | buffer[9]);
    imuData_.gyro.y =        static_cast<float>((((int16_t)buffer[10]) << 8) | buffer[11]);
    imuData_.gyro.z =        static_cast<float>((((int16_t)buffer[12]) << 8) | buffer[13]);

    // read compass
    pI2cBus_->writeByte(MPU9150_I2C_ADDR, MPU9150_INT_PIN_CFG, 0x02); //set i2c bypass enable pin to true to access magnetometer
    //delay(10);
    pI2cBus_->writeByte(MPU9150_MAG_I2C_ADDR, 0x0A, 0x01); //enable the magnetometer
    //delay(10);
    pI2cBus_->readBytes(MPU9150_MAG_I2C_ADDR, MPU9150_MAG_XOUT_L, buffer, 6);
    imuData_.compass.x = static_cast<float>((((int16_t)buffer[0]) << 8) | buffer[1]);
    imuData_.compass.y = static_cast<float>((((int16_t)buffer[2]) << 8) | buffer[3]);
    imuData_.compass.z = static_cast<float>((((int16_t)buffer[4]) << 8) | buffer[5]);
}

void MPU9150::isHealhty()
{

}

void MPU9150::setAccelSens(AccelSens sens)
{
    pI2cBus_->writeBits(MPU9150_I2C_ADDR, MPU9150_ACCEL_CONFIG, sens, 4, 2);
}

void MPU9150::setGyroSens(GyroSens sens)
{
    pI2cBus_->writeBits(MPU9150_I2C_ADDR, MPU9150_GYRO_CONFIG, sens, 4, 2);
}

void MPU9150::setSleepEnabled(bool enabled)
{
    pI2cBus_->writeBit(MPU9150_I2C_ADDR, MPU9150_PWR_MGMT_1, enabled, 6);
}
