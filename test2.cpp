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
	string name; //이름
	int power; //공격력
	int defense; //방어력
	int speed; //이동속도
	int stamina; //체력

	Jagumon() {};
	Jagumon(string name, int power, int defense, int speed, int stamina) { //생성자
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

	//복사생성자
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

vector<Jagumon> User(5); //사용자가 선택한 자구몬을 저장할 벡터 
vector<Jagumon> PC(5); //pc의 자구몬을 저장할 벡터

int main()
{
	string choice;

	cout << "### Welcome to Jagumon ###" << endl;
	cout << "게임을 시작하려면 'Go' 를 입력하고 종료를 원하시면 'Exit' 눌러주세요." << endl;
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
	cout << "원하는 자구몬의 이름을 입력하세요!" << endl;
	cout << "\n";
	
	cin >> jagumoncall;

	for (int i = 0; i < jagumon.size(); i++) {
		if (jagumoncall == jagumon.at(i).name) {
			cout << "당신의 자구몬은 " << jagumon.at(i).name << " 입니다!" << endl;
			found = true;
			//User.push_back(jagumoncall); <- 입력한 것을 user 벡터에 입력하고싶음 근데 인자로 int형만 받음
		}
	}
	if (found == false) {
		cout << "잘못 입력했습니다. 다시 입력해주세요." << endl;
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
			cout << "PC의 자구몬이 공격을 했습니다!" << endl;
			PlayerHealth -= 5;
			turn = false;
			break;
		case 1:
			cout << "PC의 자구몬이 방어를 했습니다!" << endl;
			PlayerHealth -= 4;
			turn = false;
			break;
		case 2:
			cout << "PC의 자구몬이 교체를 했습니다!" << endl;
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