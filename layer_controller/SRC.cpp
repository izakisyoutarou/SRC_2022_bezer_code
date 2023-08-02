#include"SRC.hpp"
#include"ichigoplus/lib_src/utilplus.hpp"
using namespace rp_lib;

void SRC::cycle(){
    if(src_sw.sw()==1){
        duty();
    }else if(src_sw.sw()==2){
        duty2();
    }else if(src_sw.sw()==3){
        duty3();
    }else if(src_sw.sw()==4){
        duty4();
    }else{
        src_arm.arm_stop();
        src_leg.legwheel_stop();
    }
};

void SRC::duty(){
    src_location.calculation();
    if(i<=7){
        
        //bezerクラスで計算した目標座標から現在の座標を引く
        difference_x=src_bezer.bezer_x()-src_location.Coordinate_X();
        difference_y=src_bezer.bezer_y()-src_location.Coordinate_Y();

        //tの値が増え続けているときは目標座標に到達していないため、次の配列にはいかない…ロボットは曲線を描くように走る
        //しかし、tの値が0になれば目標座標に到達したことになるので次に配列に進むことができる
        if(abs(difference_x)<10&&abs(difference_y)<10){
            if(t <= 1){
                t += 0.01;
            } else {
                t = 0;
                i++;
            }
            
        }
        //2次元配列のためポインタ渡しで配列の先頭だけを持ってきている
        src_bezer.bezer(cose1_X[i], cose1_Y[i], t);
        difference_x=src_bezer.bezer_x()-src_location.Coordinate_X();
        difference_y=src_bezer.bezer_y()-src_location.Coordinate_Y();
        
        src_leg.legwheel(atan2(difference_y,difference_x));

        if(i==5){
            src_arm.arm_down();
        }else if(i==7){
            src_arm.arm_up();
        } else {
            src_arm.arm_stop();
        }
        }else{
            src_arm.arm_stop();
            src_leg.legwheel_stop();
    }
}
void SRC::duty2(){
    src_location.calculation();
    if(h<=3){
        
        difference_x=src_bezer.bezer_x()-src_location.Coordinate_X();
        difference_y=src_bezer.bezer_y()-src_location.Coordinate_Y();
        if(abs(difference_x)<10&&abs(difference_y)<10){
            if(t<=1){
                t+=0.01;
            }else{
                h++;
                t=0;
            }
        }
        src_bezer.bezer(cose2_X[h],cose2_Y[h],t);
        difference_x=src_bezer.bezer_x()-src_location.Coordinate_X();
        difference_y=src_bezer.bezer_y()-src_location.Coordinate_Y();
        
        src_leg.legwheel(atan2(difference_y,difference_x));

        if(h==3){
            src_arm.arm_down();
        }else if(h==7){
            src_arm.arm_up();
        } else{
            src_arm.arm_stop();
        }
        }else{
            src_arm.arm_stop();
            src_leg.legwheel_stop();
    }
}
void SRC::duty3(){
    src_location.calculation();
    if(j<=7){
        
        difference_x=src_bezer.bezer_x()-src_location.Coordinate_X();
        difference_y=src_bezer.bezer_y()-src_location.Coordinate_Y();
        if(abs(difference_x)<10&&abs(difference_y)<10){
            if(t<=1){
                t+=0.01;
            }else{
                t=0;
                j++;
            }
        }
        src_bezer.bezer(cose3_X[j],cose3_Y[j],t);
        difference_x=src_bezer.bezer_x()-src_location.Coordinate_X();
        difference_y=src_bezer.bezer_y()-src_location.Coordinate_Y();
        src_leg.legwheel(atan2(difference_y,difference_x));

        if(j==5){
            src_arm.arm_down();
        }else if(j==8){
            src_arm.arm_up();
        } else{
            src_arm.arm_stop();
        }
        }else{
            src_arm.arm_stop();
            src_leg.legwheel_stop();
    }
}
void SRC::duty4(){
    src_location.calculation();
    if(k<=7){
        
        difference_x=src_bezer.bezer_x()-src_location.Coordinate_X();
        difference_y=src_bezer.bezer_y()-src_location.Coordinate_Y();
        if(abs(difference_x)<10&&abs(difference_y)<10){
            if(t<=1){
                t+=0.01;
            }else{
                t=0;
                k++;
            }
        }
        
        src_bezer.bezer(cose4_X[k],cose4_Y[k],t);
        difference_x=src_bezer.bezer_x()-src_location.Coordinate_X();
        difference_y=src_bezer.bezer_y()-src_location.Coordinate_Y();
        src_leg.legwheel(atan2(difference_y,difference_x));

        if(k==6){
            src_arm.arm_down();
        }else if(k==8){
            src_arm.arm_up();
        } else{
            src_arm.arm_stop();
        }

    }else{
            src_arm.arm_stop();
            src_leg.legwheel_stop();
    }
}





