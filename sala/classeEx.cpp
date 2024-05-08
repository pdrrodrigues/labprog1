#include<math>
#include<iostream>

using namespace std;

class Complexo{
    public:
        Complexo(float cx, float cy){
            x = cx;
            y = cy;
        }

        float modulo(){
            return sqrt(x^2 + y^2);
        }

        Complexo conjugado(){
            return Complexo(x, -y);
        }

        void print(){
            cout << "Complexo(" + x + ", " + y + ")";
        }

        Complexo adicao(Complexo c){
            return Complexo(x+c.x, y+c.y);
        }

        Complexo subtracao(Complexo c){
            return Complexo(x-c.x, y-c.y);
        }

        Complexo multiplicacao(Complexo c){
            return Complexo(x*c.x-y*c.y, x*c.y+y*c.x);
        }

        Complexo divisao(Complexo c){
            return Complexo((x*c.x+y*c.y)/c.modulo(), (-x*c.y+y*c.x)/c.modulo());
        }
    private:
        float x;
        float y;
}