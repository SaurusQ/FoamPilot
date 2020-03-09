#ifndef HARDWARE_SELECT_HPP
    #define HARDWARE_SELECT_HPP

    #define MCU_ARDUINO     1
    #define MCU_ESP32       2

    #define MCU_TYPE MCU_ARDUINO

    #define GPS_TYPE
    #define IMU_TYPE

    // altimeter
    #define SELECT_MPL3115A2
    #include "mpl3115a2.hpp"

    // imu
    #define SELECT_MPU9150
    #include "mpu9150.hpp"

    #if MCU_TYPE == MCU_ARDUINO 
        #define ARD_I2C
        #include "ArdI2c.hpp"
    #endif
#endif
