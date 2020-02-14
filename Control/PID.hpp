
#include "Arduino.h"

#include <inttypes.h>

struct PidData {
    float input;
    float output;
    float setPoint;
};

class PID
{
    public:
        PID(PidData* pPidData,
            uint16_t sampleTimeMS,
            float min, float max,
            float Kp, float Ki, float Kd,
            bool reverseActing_ = false);                   // initialize pid
        void reInit();                                      // reinit pid after pause in periodic use to prevent spikes in output, needs last input / output values to do that
        void calculate();                                   // calculate output value of the pid
        void tune(float Kp, float Ki, float Kd);            // tune all PID coefficients
        void setP(float Kp);                                // tune p
        void setI(float Ki);                                // tune i
        void setD(float Kd);                                // tune d
        bool setLimits(float min, float max);               // sets min/max to limit PID output and prevent ouput lag
        void setSampleTimeMS(uint16_t newSampeleTimeMS);
        float getSampleTimeSec();
    private:
        PidData* pPidData_;

        uint16_t sampleTimeMS_;

        float Kp_;
        float Ki_;
        float Kd_;

        float min_;
        float max_;

        float iTerm_;
        float lastInput_;

        bool reverseActing_;
};
