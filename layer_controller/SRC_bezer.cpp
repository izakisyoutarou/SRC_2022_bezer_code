#include"SRC_bezer.hpp"
void SRC_bezer::bezer(float *X, float *Y, float t){
    x=(X[0]-2*X[1]+X[2])*t*t+(-2*X[0]+2*X[1])*t+X[0];
    y=(Y[0]-2*Y[1]+Y[2])*t*t+(-2*Y[0]+2*Y[1])*t+Y[0];
}
float SRC_bezer::bezer_x(){
    return x;
}
float SRC_bezer::bezer_y(){
    return y;
}