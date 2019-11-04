#include <iostream>
#include <list>
#include <string>
using namespace std;

class Jagumon {
private:
	string name; //�̸�
	int power; //���ݷ�
	int defense; //����
	int speed; //�̵��ӵ�
	int stamina; //ü��

public:
	Jagumon(){}
	Jagumon(string name, int power, int defense, int speed, int stamina) { //������
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

	list<Jagumon> User(5); //����ڰ� ������ �ڱ����� ������ linked list
	list<Jagumon> PC(5); //pc�� �ڱ����� ������ linked list
	
	node* head = (node*)malloc(sizeof(node));
	head->next = NULL;
	
	cout << "<< ���ϴ� �ڱ��� 5 ������ �Է��ϼ���! : \n" << endl;

	for (int i = 0; i < User.size(); i++) { //����ڰ� ���ϴ� �ڱ����� �Է�
		cout << i+1 << " ��°: ";
		cin >> JagumonCall;
		addNode(head,JagumonCall);
	}

}