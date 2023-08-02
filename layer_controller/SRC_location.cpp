#include"SRC_location.hpp"
#include"math.h"
#define _USE_MATH_DEFINES
void SRC_location::calculation(){
    gyro_old=gyro_new;
    gyro_new=gyro.angleZ();
    angle=gyro_new-gyro_old;

    filenc1_old=filenc1_new;
    filenc1_new=encoder1.radian();
    filenc1=filenc1_new-filenc1_old;

    filenc2_old=filenc2_new;
    filenc2_new=encoder2.radian();
    filenc2=filenc2_new-filenc2_old;

    filenc1=filenc1*2.f-angle*10.f;

    filenc2=filenc2*2.f-angle*10.f;

    x+=(filenc1*cosf((M_PI*5.f)/4.f+gyro_new))+(filenc2*cosf((M_PI*7.f)/4.f+gyro_new));
    y+=(filenc1*sinf((M_PI*5.f)/4.f+gyro_new))+(filenc2*sinf((M_PI*7.f)/4.f+gyro_new));
    printf("X:%.3f Y:%.3f gyro:%.3f\n",x,y,gyro_new);

}
float SRC_location::Coordinate_X(){
    return x;
}
float SRC_location::Coordinate_Y(){
    return y;
}
