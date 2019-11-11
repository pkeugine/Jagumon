#include <iostream>
#include <string>
#include <ctime>
#include <random>
using namespace std;

void MAINPROGRAM();
void JagumonRandomize();
void PCJagumon();
void Player();

int PlayerHealth = 100;
int TrexHealth = 100;

bool turn = true;

class Jagumon {
public:
	string name; //�̸�
	int power; //���ݷ�
	int defense; //����
	int speed; //�̵��ӵ�
	int stamina; //ü��

	Jagumon() {};
	Jagumon(string name, int power, int defense, int speed, int stamina) { //������
		this->name = name;
		this->power = power;
		this->defense = defense;
		this->speed = speed;
		this->stamina = stamina;
	}

	string getName() {return name;}
	int getPower() { return power;}
	int getDefense() { return defense; }
	int getSpeed() { return speed; }
	int getStamin() { return stamina; }

	//���������
	/*
	Jagumon(Jagumon &jagu) {
		name = jagu.getName();
		power = jagu.getPower();
		defense = jagu.getDefense();
		speed = jagu.getSpeed();
		stamina = jagu.getStamin();
	}
	*/
};

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

vector<Jagumon>jagumon = { AAA,BBB,CCC,DDD,EEE,GGG,HHH,JJJ,KKK,LLL};

vector<Jagumon> User(5); //����ڰ� ������ �ڱ����� ������ ���� 
vector<Jagumon> PC(5); //pc�� �ڱ����� ������ ����

int main()
{
	string choice;

	cout << "### Welcome to Jagumon ###" << endl;
	cout << "������ �����Ϸ��� 'Go' �� �Է��ϰ� ���Ḧ ���Ͻø� 'Exit' �����ּ���." << endl;
	cin >> choice;

	if (choice == "Go" || choice == "go")
	{
		MAINPROGRAM();
	}
	else if (choice == "Exit" || choice == "exit")
		exit;
}


void MAINPROGRAM()
{
	Player();
}

void Player()
{
	string jagumoncall = "";
	bool found = false;

	cout << "<Jagumon List>" << endl;
	cout << "1. AAA" << endl;
	cout << "2. BBB" << endl;
	cout << "3. CCC" << endl;
	cout << "4. DDD" << endl;
	cout << "���ϴ� �ڱ����� �̸��� �Է��ϼ���!" << endl;
	cout << "\n";
	
	cin >> jagumoncall;

	for (int i = 0; i < jagumon.size(); i++) {
		if (jagumoncall == jagumon.at(i).name) {
			cout << "����� �ڱ����� " << jagumon.at(i).name << " �Դϴ�!" << endl;
			found = true;
			//User.push_back(jagumoncall); <- �Է��� ���� user ���Ϳ� �Է��ϰ���� �ٵ� ���ڷ� int���� ����
		}
	}
	if (found == false) {
		cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl;
		Player();
	}
	cout << endl;
}

void JagumonRandomize() //Unused At the moment
{
	time_t T;
	time(&T);
	srand(T);

	for (int R = 0; R < 1; ++R)
	{
		cout << rand() % 2 << endl;
	}
}


void PCJagumon()
{
	time_t T;
	time(&T);
	srand(T);

	for (int R = 0; R < 1; ++R)
	{
		cout << rand() % 5 << endl;
	}

	while (true)
	{
		switch (T)
		{
		case 0:
			cout << "PC�� �ڱ����� ������ �߽��ϴ�!" << endl;
			PlayerHealth -= 5;
			turn = false;
			break;
		case 1:
			cout << "PC�� �ڱ����� �� �߽��ϴ�!" << endl;
			PlayerHealth -= 4;
			turn = false;
			break;
		case 2:
			cout << "PC�� �ڱ����� ��ü�� �߽��ϴ�!" << endl;
			PlayerHealth -= 5;
			turn = false;
			break;
		}

		if (turn == false)
		{
			Player();
		}
	}
}