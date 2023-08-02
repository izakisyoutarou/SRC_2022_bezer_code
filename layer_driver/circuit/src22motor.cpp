#include <stdio.h>
#include <math.h>
#include "src22motor.hpp"

MotorDriver::MotorDriver(Pwm &pwm0,Pwm &pwm1, float frequency){
    this->pwm0 = &pwm0;
    this->pwm1 = &pwm1;
    this->frequency = frequency;
}

int MotorDriver::setup(){

    pwm0->setupPwmOut(frequency,0.0);
    pwm1->setupPwmOut(frequency,0.0);

}

void MotorDriver::duty(float value){

	if(-0.95<=value,value<=0.95){//floatmillit()でよい。なぜか使えなかった
		request = value;
	}

}

void MotorDriver::rev(int r){
	if(r=0){

	}
	else{
		request = -1*request;
	}
}

void MotorDriver::cycle(){

    //LAP駆動
    #if 0
	    pwm0->pwmWrite(0.5+(request/2));
        pwm1->pwmWrite(0.5-(request/2));

    //SM駆動
    #else
        if(request >= 0){
            pwm0->pwmWrite(request);
            pwm1->pwmWrite(0.0);
        }
        else{

            pwm0->pwmWrite(0.0);
            pwm1->pwmWrite(-1.0*request);
        }
    #endif    
}

