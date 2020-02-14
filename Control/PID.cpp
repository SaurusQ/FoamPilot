
#include "PID.hpp"

PID::PID(PidData* pPidData, uint16_t sampleTimeMS, float min, float max, float Kp, float Ki, float Kd, bool reverseActing)
    : pPidData_(pPidData)
    , sampleTimeMS_(sampleTimeMS)
    , reverseActing_(reverseActing)
{
    this->tune(Kp, Ki, Kd);
    if(!this->setLimits(min, max))
    {
        // if setting limits failed set some default values
        this->setLimits(0, 255);
    }
    this->reInit();
}

void PID::reInit()
{
    lastInput_ = pPidData_->input;
    iTerm_ = pPidData_->output;
    if(iTerm_ > max_) iTerm_ = max_; // clamp value
    else if(iTerm_ < min_) iTerm_ = min_;
}

void PID::calculate()
{
    // calculate errors
    float error = pPidData_->setPoint - pPidData_->input;
    iTerm_ += (Ki_ * error); // do this way to prevent bumps in output when Ki_ is changed
    if(iTerm_ > max_) iTerm_ = max_; // clamp values to prevent laggin
    else if(iTerm_ < min_) iTerm_ = min_;
    float dInput = (pPidData_->input - lastInput_);

    // remember input to calculate dIntput next time
    lastInput_ = pPidData_->input;

    // compute output
    pPidData_->output = Kp_ * error + iTerm_ + Kd_ * dInput;
    if(pPidData_->output > max_) pPidData_->output = max_; // clamp values to min / max
    else if(pPidData_->output < min_) pPidData_->output = min_;
}

void PID::tune(float Kp, float Ki, float Kd)
{
    float sampleTimeInSec = this->getSampleTimeSec();
    Kp_ = Kp;
    Ki_ = Ki * this->getSampleTimeSec();
    Kd_ = Kd / this->getSampleTimeSec();
    if(reverseActing_)
    {
        Kp_ = -Kp_;
        Ki_ = -Ki_;
        Kd_ = -Kd_;
    }
}

void PID::setP(float Kp)
{
    Kp_ = Kp;
    if(reverseActing_) Kp_ = -Kp_;
}

void PID::setI(float Ki)
{
    Ki_ = Ki * this->getSampleTimeSec();
    if(reverseActing_) Ki_ = -Ki_;
}

void PID::setD(float Kd)
{
    Kd_ = Kd / this->getSampleTimeSec();
    if(reverseActing_) Kd_ = -Kd_;
}

bool PID::setLimits(float min, float max)
{
    if(min > max) return false;
    min_ = min;
    max_ = max;
    return true;
}

void PID::setSampleTimeMS(uint16_t newSampleTimeMS)
{
    // need to recalculate Ki_ and Kd_ terms
    float ratio = (float)newSampleTimeMS / (float)sampleTimeMS_;
    Ki_ *= ratio;
    Kd_ /= ratio;

    sampleTimeMS_ = newSampleTimeMS;
}

float PID::getSampleTimeSec()
{
    return ((float)sampleTimeMS_) / 1000;
}