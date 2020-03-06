
#ifndef ALTIMETER_HPP
#define ALTIMETER_HPP

class Altimeter
{
    public:
        Altimeter() {};
        virtual ~Altimeter() {};
        virtual void calibrate() = 0;
        virtual void update() = 0;

        virtual float getAltitudeF();
        virtual uint32_t getAltitudeI();
    protected:
        uint32_t altitude_;

};


#endif
