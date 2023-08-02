#ifndef SRC_CALBIRATION_HPP
#define SRC_CALBIRATION_HPP
#include"ichigoplus/layer_controller/photo_interrputer.hpp"
#include"ichigoplus/layer_driver/circuit/lap_motor_driver.hpp"
using PhotoInt=photo_interrputer::PhotoInterrputerDigital;
class SRC_arm{
    public:
        SRC_arm(PhotoInt &topPhoto, PhotoInt &bottomPho, LAPMotorDriver &mcArmWheel)
                :topPhoto(topPhoto), bottomPhoto(bottomPhoto), mcArmWheel(mcArmWheel){};
        void calbiration();
        void arm_up();
        void arm_down();
        void arm_stop();

    private:
    PhotoInt &topPhoto;
    PhotoInt &bottomPhoto;
    LAPMotorDriver &mcArmWheel;
};
#endif