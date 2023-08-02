#ifndef SRC_BEZER_HPP
#define SRC_BEZER_HPP
class SRC_bezer{
    public:
        void bezer(float *X, float *Y, float t);
        float bezer_x();
        float bezer_y();
    private:
        float x;
        float y;
        // float cose1_X[6][3]={{30,75,75},{76,80,145},{145,147,246},{246,147,145},{145,80,76},{75,75,30}};
        // float cose1_Y[6][3]={{0,0,75},{75,-154,-81},{-81,-25,-10},{-10,-25,-81},{-81,-154,75},{75,0,0}};

};
#endif