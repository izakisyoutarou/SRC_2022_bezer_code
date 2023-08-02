#ifndef SRC22MOTOR_HPP
#define SRC22MOTOR_HPP

#include "pwm.hpp"

class MotorDriver{
    public:
    MotorDriver(Pwm &pwm0,Pwm &pwm1, float frequency);

    int setup();
    void duty(float value);
    float duty(){return request;}
    void cycle();
    void rev(int r);

    private:

    Pwm *pwm0;
    Pwm *pwm1;
    float request;
    float frequency;

};
#endif
