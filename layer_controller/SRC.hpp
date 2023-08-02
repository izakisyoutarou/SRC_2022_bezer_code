#ifndef SRC_HPP
#define SRC_HPP
#include"ichigoplus/layer_controller/filtered_encoder.hpp"
#include"ichigoplus/layer_driver/circuit/bno055.hpp"
#include"ichigoplus/layer_driver/circuit/lap_motor_driver.hpp"
#include"layer_driver/device/pin.hpp"
#include"ichigoplus/lib_src/utilplus.hpp"
#include"ichigoplus/layer_controller/photo_interrputer.hpp"
#include"ichigoplus/layer_driver/base/pwm.hpp"
#include"SRC_location.hpp"
#include"SRC_arm.hpp"
#include"SRC_sw.hpp"
#include"SRC_leg.hpp"
#include"SRC_bezer.hpp"


class SRC{
public:
    SRC( SRC_location &src_location, SRC_arm &src_arm, SRC_leg &src_leg,SRC_sw &src_sw):
    	src_location(src_location),src_arm(src_arm),src_leg(src_leg),src_sw(src_sw){
    	src_arm.calbiration();
    };
    void cycle();
    void duty();
    void duty2();
    void duty3();
    void duty4();
  
private:
 SRC_location &src_location;
 SRC_arm &src_arm;
 SRC_sw &src_sw;
 SRC_leg &src_leg;
 SRC_bezer src_bezer;
 
 float cose1_X[8][3]={{0,75,75},{75,80,145},{145,147,165},{165,190,246},{246,190,165},{165,147,145},{145,80,75},{75,75,0}};
 float cose1_Y[8][3]={{0,0,75},{75,-85,-54},{-54,-25,-10},{-10,-10,-10},{-10,-10,-10},{-10,-25,-54},{-54,-85,75},{75,0,0}};
 float cose2_X[4][3]={{0,75,75},{75,80,216},{216,80,75},{75,75,0}};
 float cose2_Y[4][3]={{0,0,75},{75,80,81},{81,80,75},{75,0,0}};
 float cose3_X[8][3]={{0,75,75},{75,75,44},{44,10,10},{10,10,70},{70,10,10},{10,10,44},{44,75,75},{75,75,0}};
 float cose3_Y[8][3]={{0,0,-45},{-45,-80,-85},{-85,-83,-118},{-118,-157,-157},{-157,-157,-118},{-118,-83,-85},{-85,-80,-45},{-45,0,0}};
 float cose4_X[8][3]={{0,75,75},{75,75,44},{44,10,10},{10,20,120},{120,20,10},{10,10,44},{44,75,75},{75,75,0}};
 float cose4_Y[8][3]={{0,0,-45},{-45,-80,-85},{-85,-83,-203},{-203,-225,-220},{-220,-225,-203},{-203,-83,-85},{-85,-80,-45},{-45,0,0}};
 float difference_x;
 float difference_y;
 int h=0;
 int i=0;
 int j=0;
 int k=0;
 float t = 0.f;

};
#endif
