#include <iostream>
#include <list>
#include <string>
using namespace std;

class Jagumon {
private:
	int power; //���ݷ�
	int defence; //����
	int speed; //�̵��ӵ�
	int stamina; //ü��

public:
	Jagumon(int power, int defence, int speed, int stamina) { //������
		this->power = power;
		this->defence = defence;
		this->speed = speed;
		this->stamina = stamina;
	}
};

int main() {
	Jagumon a(10, 10, 10, 10);
	list<Jagumon> User(5); //����ڰ� ������ �ڱ����� ������ linked list
	list<Jagumon> PC(5); //pc�� �ڱ����� ������ linked list
	

	for (int i = 0; i < User.size(); i++) { //����ڰ� ���ϴ� �ڱ����� �Է�
		string input;
		cout << "<< ���ϴ� �ڱ��� 5������ �Է��ϼ���! : " << endl;
		cin >> input;
	}

}