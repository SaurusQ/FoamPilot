
#include "altimeter.hpp"

float Altimeter::getAltitudeF()
{
    return (float)altitude_;
}

uint32_t Altimeter::getAltitudeI()
{
    return altitude_;
}