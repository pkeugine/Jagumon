#include <iostream>
using namespace std;

class Jagumon{
private:
    int power;
    int defence;
    int speed;
    int stamina;

public:
    Jagumon(int power, int defence, int speed, int stamina){
        this->power = power;
        this->defence = defence;
        this->speed = speed;
        this->stamina = stamina;
        cout << power << defence << speed << stamina;
    }
};

int main(){
}
