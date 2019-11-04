#include <iostream>
#include <list>
#include <string>
using namespace std;

class Jagumon {
private:
	string name; //이름
	int power; //공격력
	int defense; //방어력
	int speed; //이동속도
	int stamina; //체력

public:
	Jagumon(){}
	Jagumon(string name, int power, int defense, int speed, int stamina) { //생성자
		this->name = name;
		this->power = power;
		this->defense = defense;
		this->speed = speed;
		this->stamina = stamina;
	}
	
	string ShowName() {
		return name;
	}
};

typedef struct NODE {
	string name;
	struct NODE* next;
}node;

void addNode(node* head, string name) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->name = name;
	newNode->next = head->next;
	head->next = newNode;
}

int main() {
	string JagumonCall;
	Jagumon AAA("AAA", 10, 50, 5, 100);
	Jagumon BBB("BBB", 20, 45, 10, 100);
	Jagumon CCC("CCC", 30, 40, 15, 100);
	Jagumon DDD("DDD", 40, 35, 20, 100);
	Jagumon EEE("EEE", 50, 30, 25, 100);
	Jagumon GGG("GGG", 60, 25, 30, 100);
	Jagumon HHH("HHH", 70, 20, 35, 100);
	Jagumon JJJ("JJJ", 80, 15, 40, 100);
	Jagumon KKK("KKK", 90, 10, 45, 100);
	Jagumon LLL("LLL", 95, 10, 50, 100);

	list<Jagumon> User(5); //사용자가 선택한 자구몬을 저장할 linked list
	list<Jagumon> PC(5); //pc의 자구몬을 저장할 linked list
	
	node* head = (node*)malloc(sizeof(node));
	head->next = NULL;
	
	cout << "<< 원하는 자구몬 5 마리를 입력하세요! : \n" << endl;

	for (int i = 0; i < User.size(); i++) { //사용자가 원하는 자구몬을 입력
		cout << i+1 << " 번째: ";
		cin >> JagumonCall;
		addNode(head,JagumonCall);
	}

}