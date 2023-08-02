#ifndef SRC_SW_HPP
#define SRC_SW_HPP
#include"layer_driver/device/pin.hpp"
class SRC_sw{
    public:
        SRC_sw(Sw0 &sw0, Sw1 &sw1, Sw2 &sw2, Sw3 &sw3, A1 &a1, A2 &a2, A3 &a3, A4 &a4):
                sw0(sw0),sw1(sw1),sw2(sw2),sw3(sw3),a1(a1),a2(a2),a3(a3),a4(a4){};
        int sw();
    private:
    Sw0 &sw0;
    Sw1 &sw1;
    Sw2 &sw2;
    Sw3 &sw3;
    A1 &a1;
    A2 &a2;
    A3 &a3;
    A4 &a4;
    
};
#endif
