
#ifndef HARDWARE_SELECT_HPP
    #define HARDWARE_SELECT_HPP

    #define MCU_TYPE ARDUINO

    #define GPS_TYPE
    #define IMU_TYPE

    #if MCU_TYPE == ARDUINO 
        #define I2C_TYPE ArdI2c
        #include "ArdI2c.hpp"
    #endif
#endif
