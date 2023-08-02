#include"SRC_leg.hpp"
#include"ichigoplus/lib_src/utilplus.hpp"
using namespace rp_lib;
void SRC_leg::legwheel(float theta){
    src_front.front_correction();
    M1=sinf(theta+f_pi/3)+src_front.compass();
    M2=sinf(theta-f_pi/3)+src_front.compass();
    M3=sinf(theta-f_pi)+src_front.compass();

    absmax=absMax(absMax(M1,M2),M3);
    if(absmax<0){
        absmax*=-1;
    }

    M1=M1*(0.9/absmax);
    M2=M2*(0.9/absmax);
    M3=M3*(0.9/absmax);

    mcRightWheel.duty(M1);
    mcLeftWheel.duty(M2);
    mcBackWheel.duty(M3);
}
void SRC_leg::legwheel_stop(){
    M1=0.f;
    M2=0.f;
    M3=0.f;
    mcRightWheel.duty(M1);
    mcLeftWheel.duty(M2);
    mcBackWheel.duty(M3);
}