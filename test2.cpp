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
private:
	string name; //이름
	int power; //공격력
	int defense; //방어력
	int speed; //이동속도
	int stamina; //체력
public:
	Jagumon() {};
	Jagumon(string name, int power, int defense, int speed, int stamina) { //생성자
		this->name = name;
		this->power = power;
		this->defense = defense;
		this->speed = speed;
		this->stamina = stamina;
	}

	string showName() {return name;}
	int showPower() { return power;}
	int showDefense() { return defense; }
	int showSpeed() { return speed; }
	int showStamina() { return stamina; }

	void setStamina(int newst) { this->stamina = newst; }

	//복사생성자 (깊은 복사로)
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

Jagumon AAA("AAA", 50, 50, 5, 100);
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

void MAINPROGRAM()
{
	Player();
}
void Player(){
	string jagumoncall = "";
	bool found = false;

	cout << "<Jagumon List>" << endl;
	cout << "1. AAA" << endl;
	cout << "2. BBB" << endl;
	cout << "3. CCC" << endl;
	cout << "4. DDD" << endl;
	cout << "원하는 자구몬의 이름을 입력하세요!" << endl;
	
	cin >> jagumoncall;
	cout << "\n";

	for (int i = 0; i < jagumon.size(); i++) {
		if (jagumoncall == jagumon.at(i).showName()) {
			cout << "당신의 자구몬은 " << jagumon.at(i).showName() << " 입니다!" << endl;
			found = true;
			
			// User.push_back(jagumoncall); <- 방법1 : 입력한 것을 user 벡터에 입력하고싶음, 근데 인자로 int형이랑 char형만 받음
			// 방법2 : 복사 생성자를 이용해서 객체 하나를 만든다.
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
			cout << "상대방의 자구몬이 공격을 했습니다!" << endl;
			PlayerHealth -= 5;
			turn = false;
			break;
		case 1:
			cout << "상대방의 자구몬이 방어를 했습니다!" << endl;
			PlayerHealth -= 4;
			turn = false;
			break;
		case 2:
			cout << "상대방의 자구몬이 교체를 했습니다!" << endl;
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

void Attack(Jagumon &user, Jagumon &pc) { //첫번째 인자(user)가 두번째 인자(pc)에게 공격
	cout << user.showName() << "이(가) 공격을 했습니다!" << endl;
	if (user.showPower() >= pc.showStamina()) { //pc의 남은 체력이 user의 공격력보다 낮을 때 
		pc.setStamina(0); // 사망
		cout << "상대방의 자구몬이 사망했습니다." << endl;
		cout << user.showName() << "의 현재 체력 : " << user.showStamina() << endl;
	}
	else {
		pc.setStamina(pc.showStamina() - user.showPower()); // pc의 남은 체력이 user의 공격력보다 높을 때 : 공격력만큼 체력 감소
		cout << pc.showName() << "의 체력이 " << pc.showStamina() << "로 감소했습니다!" << endl;
		cout << user.showName() << "의 현재 체력 : " << user.showStamina() << endl;
		cout << pc.showName() << "의 현재 체력 : " << pc.showStamina() << endl;
	}
	cout << endl;
}

void Defense(Jagumon &user, Jagumon &pc) { //첫번째 인자가 두번째 인자의 공격을 방어
	cout << user.showName() << "이(가) 방어를 선택했습니다!" << endl;
	if (user.showDefense() > pc.showPower()) { // user의 방어력이 pc의 공격력보다 높을 때 : 방어 성공 + 체력 10 증가
		cout<< user.showName() << "이(가) 방어에 성공했습니다!" << endl;
		user.setStamina(user.showStamina() + 10);
		cout << user.showName() << "의 현재 체력 : " << user.showStamina() << endl;
		cout << pc.showName() << "의 현재 체력 : " << pc.showStamina() << endl;
	}
	else { // user의 방어력이 pc의 공격력보다 낮을 때 : user의 체력이 pc의 공격력만큼 감소
		cout << user.showName() << "의 체력이 " << user.showStamina() << "로 감소했습니다!" << endl;
		user.setStamina(pc.showStamina() - pc.showPower());
		cout << user.showName() << "의 현재 체력 : " << user.showStamina() << endl;
		cout << pc.showName() << "의 현재 체력 : " << pc.showStamina() << endl;
	}
	cout << endl;
}

void Change(Jagumon user) {
	cout << "어떤 자구몬으로 교체하시겠습니까?" << endl;
}

int main()
{
	string choice;
	int n;

	cout << "### Welcome to Jagumon ###" << endl;
	cout << "게임을 시작하려면 'Go' 를 입력하고 종료를 원하시면 'Exit' 눌러주세요." << endl;
	cin >> choice;
	cout << endl;

	if (choice == "Go" || choice == "go")
	{
		MAINPROGRAM();

		//user입장에서 구현
		
		while (BBB.showStamina() != 0) {
			cout << "<1. 공격> <2. 방어> <3. 교체> 중 하나를 선택하세요." << endl;
			cin >> n;
			switch (n)
			{
			case 1:
				Attack(AAA, BBB);
				break;
			case 2:
				Defense(AAA, BBB);
				break;
			case 3:
				Change(AAA);
				break;
			}
		}
		
	}
	else if (choice == "Exit" || choice == "exit")
		exit;
}