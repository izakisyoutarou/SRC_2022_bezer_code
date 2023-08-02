#ifndef SRC_LOCATION_HPP
#define SRC_LOCATION_HPP
#include"ichigoplus/layer_driver/circuit/bno055.hpp"
#include"ichigoplus/layer_controller/filtered_encoder.hpp"
class SRC_location{
public:
    SRC_location(Bno055 &gyro, encoder::FilteredEncoder &encoder1, encoder::FilteredEncoder &encoder2):
                gyro(gyro), encoder1(encoder1),encoder2(encoder2){};
    void calculation();
    float Coordinate_X();
    float Coordinate_Y();
private:
    Bno055 &gyro;
    encoder::FilteredEncoder &encoder1;
    encoder::FilteredEncoder &encoder2;
    float gyro_new=0;
    float gyro_old=0;
    float angle=0;
    float filenc1_new=0;
    float filenc1_old=0;
    float filenc1=0;
    float filenc2_new=0;
    float filenc2_old=0;
    float filenc2=0;
    float x=0,y=0;
};
#endif

