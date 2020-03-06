

#ifndef HARDWARE_SELECT_HPP
    #define HARDWARE_SELECT_HPP

    #define ARDUINO     1
    #define ESP32       2

    #define MCU_TYPE ARDUINO

    //#define GPS_TYPE
    //#define IMU_TYPE
    //#define ALT_TYPE

    #define MPL3115A2

    #if MCU_TYPE == ARDUINO
        #define ARD_I2C
        #include "ArdI2c.hpp"
    #endif
#endif
