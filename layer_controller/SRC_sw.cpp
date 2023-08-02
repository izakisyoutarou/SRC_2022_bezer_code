#include"SRC_sw.hpp"
int SRC_sw::sw(){
    if(sw0.digitalRead()==1&&sw1.digitalRead()==0&&sw2.digitalRead()==0&&sw3.digitalRead()==0){
        a1.digitalHigh();
        a2.digitalLow();
        a3.digitalLow();
        a4.digitalLow();
        return 1;
    }else if(sw0.digitalRead()==0&&sw1.digitalRead()==1&&sw2.digitalRead()==0&&sw3.digitalRead()==0){
        a1.digitalLow();
        a2.digitalHigh();
        a3.digitalLow();
        a4.digitalLow();
        return 2;
    }else if(sw0.digitalRead()==0&&sw1.digitalRead()==0&&sw2.digitalRead()==1&&sw3.digitalRead()==0){
        a1.digitalLow();
        a2.digitalLow();
        a3.digitalHigh();
        a4.digitalLow();
        return 3;
    }else if(sw0.digitalRead()==0&&sw1.digitalRead()==0&&sw2.digitalRead()==0&&sw3.digitalRead()==1){
        a1.digitalLow();
        a2.digitalLow();
        a3.digitalLow();
        a4.digitalHigh();
        return 4;
    }else{
        a1.digitalLow();
        a2.digitalLow();
        a3.digitalLow();
        a4.digitalLow();
        return 0;
    }
}
