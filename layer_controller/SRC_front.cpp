#include"SRC_front.hpp"
#include"ichigoplus/lib_src/utilplus.hpp"
using namespace rp_lib;
void SRC_front::front_correction(){
    //正面補正
    gyro_s=area(gyro.angleZ(),0.f,2*f_pi);
    if(gyro_s<=f_pi){
        duty_g=-1*gyro_s*1.5f;
    }
    else{
        duty_g=(2*f_pi-gyro_s)*1.5f;
    }
}
float SRC_front::compass(){
    return duty_g;
}