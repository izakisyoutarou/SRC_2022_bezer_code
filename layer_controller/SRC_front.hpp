#ifndef SRC_FRONT_HPP
#define SRC_FRONT_HPP
#include"ichigoplus/lib_src/utilplus.hpp"
#include"ichigoplus/layer_driver/circuit/bno055.hpp"
class SRC_front{
    public:
        SRC_front(Bno055 &gyro):gyro(gyro){};
        void front_correction();
        float compass();
    private:
    Bno055 &gyro;
    float gyro_s=0;
    float duty_g=0;
};
#endif