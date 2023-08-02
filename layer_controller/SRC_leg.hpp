#ifndef SRC_LEG_HPP
#define SRC_LEG_HPP
#include"ichigoplus/layer_driver/circuit/lap_motor_driver.hpp"
#include"SRC_front.hpp"
class SRC_leg{
    public:
        SRC_leg( LAPMotorDriver &mcRightWheel,LAPMotorDriver &mcLeftWheel,LAPMotorDriver &mcBackWheel, SRC_front &src_front):
                mcRightWheel(mcRightWheel),mcLeftWheel(mcLeftWheel),mcBackWheel(mcBackWheel),src_front(src_front){};
        void legwheel(float theta);
        void legwheel_stop();

    private:
        LAPMotorDriver &mcRightWheel;
        LAPMotorDriver &mcLeftWheel;
        LAPMotorDriver &mcBackWheel;
        SRC_front &src_front;

        float M1=0;
        float M2=0;
        float M3=0;
        float absmax=0;
        
};
#endif