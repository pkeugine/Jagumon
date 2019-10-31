#include <iostream>
#include <list>
#include <string>
using namespace std;

class Jagumon {
private:
	int power; //공격력
	int defence; //방어력
	int speed; //이동속도
	int stamina; //체력

public:
	Jagumon(int power, int defence, int speed, int stamina) { //생성자
		this->power = power;
		this->defence = defence;
		this->speed = speed;
		this->stamina = stamina;
	}
};

int main() {
	Jagumon a(10, 10, 10, 10);
	list<Jagumon> User(5); //사용자가 선택한 자구몬을 저장할 linked list
	list<Jagumon> PC(5); //pc의 자구몬을 저장할 linked list
	

	for (int i = 0; i < User.size(); i++) { //사용자가 원하는 자구몬을 입력
		string input;
		cout << "<< 원하는 자구몬 5마리를 입력하세요! : " << endl;
		cin >> input;
	}

}