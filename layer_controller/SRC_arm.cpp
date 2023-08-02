#include"SRC_arm.hpp"
#define _USE_MATH_DEFINES
#include<math.h>

void SRC_arm::calbiration(){
    topPhoto.startReading(2.f);
        while (topPhoto.read()){
                mcArmWheel.duty(-0.6);
                mcArmWheel.cycle();
        }
        mcArmWheel.duty(0.f);
        mcArmWheel.cycle();
         while (topPhoto.read()){
                mcArmWheel.duty(0.6);
                mcArmWheel.cycle();
        }
        mcArmWheel.duty(0.f);
        mcArmWheel.cycle();
        topPhoto.stopReading();
}

void SRC_arm::arm_up(){
        topPhoto.startReading(2.f);
        if(topPhoto.read()==1){
                mcArmWheel.duty(-0.6);
        }else{
                mcArmWheel.duty(0.f);
        }
        topPhoto.stopReading();
}
void SRC_arm::arm_down(){
        bottomPhoto.startReading(2.f);
        if(bottomPhoto.read()==1){
                mcArmWheel.duty(0.6);
        }else{
                mcArmWheel.duty(0.f);
        }
        bottomPhoto.stopReading();
}
void SRC_arm::arm_stop(){
        mcArmWheel.duty(0.f);
}

