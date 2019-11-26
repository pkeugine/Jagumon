#include <iostream>
#include <string>
#include <ctime>
#include <random>
using namespace std;

void MAINPROGRAM();
//void JagumonRandomize();
//void PCJagumon();
void Player();
void COM();

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

	//복사생성자 (얕은 복사)
	/*
	Jagumon(Jagumon &jagu) {
		name = jagu.showName();
		power = jagu.showPower();
		defense = jagu.showDefense();
		speed = jagu.showSpeed();
		stamina = jagu.showStamina();
	}
	*/
};

Jagumon AAA("AAA", 100, 50, 60, 100);
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

vector<Jagumon> User(3); //사용자가 선택한 자구몬을 저장할 벡터 
vector<Jagumon> PC(3); //pc의 자구몬을 저장할 벡터

void MAINPROGRAM()
{
	Player();
	COM();
}
void Player(){
	string jagumoncall = "";

	cout << "<Jagumon List>" << endl;
	cout << "1. AAA" << endl;
	cout << "2. BBB" << endl;
	cout << "3. CCC" << endl;
	cout << "4. DDD" << endl;
	cout << "5. EEE" << endl;
	cout << "6. GGG" << endl;
	cout << "7. HHH" << endl;
	cout << "8. JJJ" << endl;
	cout << "9. KKK" << endl;
	cout << "10. LLL" << endl;
	
	cout << "<< 주의! 출전 순서는 1번째 -> 2번째 -> 3번째 자구몬 순서이므로 신중하게 골라주세요! >>" << endl;
	for (int i = 1; i < 4; i++) {

		cout << "원하는 자구몬의 이름을 입력하세요!" << endl;
		
		cin >> jagumoncall;
		cout << "\n";
		
		if (jagumoncall == "AAA") {
			User[i - 1] = AAA;
			cout << "선택하신 " << i << "번째 자구몬은 " << AAA.showName() << " 입니다." << endl;
		}
		else if (jagumoncall == "BBB") {
			User[i - 1] = BBB;
			cout << "선택하신 " << i << "번째 자구몬은 " << BBB.showName() << " 입니다." << endl;
		}	
		else if (jagumoncall == "CCC") {
			User[i - 1] = CCC;
			cout << "선택하신 " << i << "번째 자구몬은 " << CCC.showName() << " 입니다." << endl;
		}
		else if (jagumoncall == "DDD") {
			User[i - 1] = DDD;
			cout << "선택하신 " << i << "번째 자구몬은 " << DDD.showName() << " 입니다." << endl;
		}
		else if (jagumoncall == "EEE") {
			User[i - 1] = EEE;
			cout << "선택하신 " << i << "번째 자구몬은 " << EEE.showName() << " 입니다." << endl;
		}
		else if (jagumoncall == "GGG") {
			User[i - 1] = GGG;
			cout << "선택하신 " << i << "번째 자구몬은 " << GGG.showName() << " 입니다." << endl;
		}
		else if (jagumoncall == "HHH") {
			User[i - 1] = HHH;
			cout << "선택하신 " << i << "번째 자구몬은 " << HHH.showName() << " 입니다." << endl;
		}
		else if (jagumoncall == "JJJ") {
			User[i - 1] = JJJ;
			cout << "선택하신 " << i << "번째 자구몬은 " << JJJ.showName() << " 입니다." << endl;
		}
		else if (jagumoncall == "KKK") {
			User[i - 1] = KKK;
			cout << "선택하신 " << i << "번째 자구몬은 " << KKK.showName() << " 입니다." << endl;
		}
		else if (jagumoncall == "LLL") {
			User[i - 1] = LLL;
			cout << "선택하신 " << i << "번째 자구몬은 " << LLL.showName() << " 입니다." << endl;
		}
		else {
			cout << "잘못 입력했습니다. 다시 입력해주세요." << endl;
			i--;
		}
		cout << endl;
	}
}
//사용자가 고른 것을 제외한 객체 중 3개 랜덤으로 고르게 만들어야 한다.
void COM() {
	PC[0] = LLL;
	PC[1] = KKK;
	PC[2] = JJJ;
}
/*
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
*/
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
// 방어는 방어력만큼 무조건 체력 회복
void Defense(Jagumon &user, Jagumon &pc) { //첫번째 인자가 두번째 인자의 공격을 방어
	cout << user.showName() << "이(가) 방어를 선택했습니다!" << endl;
	cout << user.showName() << "의 체력이 " << user.showDefense() << " 만큼 회복되었습니다."<<endl;
	user.setStamina(user.showStamina() + user.showDefense());
	cout << user.showName() << "의 현재 체력 : " << user.showStamina() << endl;
	cout << pc.showName() << "의 현재 체력 : " << pc.showStamina() << endl;
	/*
	if (user.showDefense() > pc.showPower()) { // user의 방어력이 pc의 공격력보다 높을 때 : 방어 성공 + 체력 10 증가
		cout<< user.showName() << "이(가) 방어에 성공했습니다!" << endl;
		user.setStamina(user.showStamina() + 10);
		cout << user.showName() << "의 현재 체력 : " << user.showStamina() << endl;
		cout << pc.showName() << "의 현재 체력 : " << pc.showStamina() << endl;
	}
	else { // user의 방어력이 pc의 공격력보다 낮을 때 : user의 체력이 pc의 공격력만큼 감소
		cout << user.showName() << "의 체력이 " << pc.showPower() << "만큼 감소했습니다!" << endl;
		user.setStamina(pc.showStamina() - pc.showPower());
		if (user.showStamina() <= 0)
			cout << user.showName() << "이 사망했습니다." << endl;
		else
			cout << user.showName() << "의 현재 체력 : " << user.showStamina() << endl;
		cout << pc.showName() << "의 현재 체력 : " << pc.showStamina() << endl;
	}
	cout << endl;
	*/
}
//공격과 수비 중 하나를 선택하는 함수 
void makeTurn(Jagumon &jag1, Jagumon &jag2) {
	int n;
	cin >> n;

	switch (n)
	{
	case 1:
		Attack(jag1, jag2);
		break;
	case 2:
		Defense(jag1, jag2);
		break;
	}
}

//자구몬의 이동속도에 따른 우선순위를 구현하는 함수
void actingBySpeed(Jagumon &user, Jagumon &pc) {
	if (user.showSpeed() > pc.showSpeed()) { // 내 속도(첫번째 인자)가 상대방의 속도(두번째 인자)보다 빠른 경우
		makeTurn(user, pc); // 내 턴 먼저 실행
		makeTurn(pc, user); // 그 후 상대 턴 실행 -> 이걸 컴퓨터의 랜덤 함수로 대체해야함!
	}
	else {
		makeTurn(pc, user);
		makeTurn(user, pc);
	}
	//(user.showSpeed() > pc.showSpeed()) ? makeTurn(user, pc) : makeTurn(pc, user);
}



/*
void Change(Jagumon user) {
	cout << "어떤 자구몬으로 교체하시겠습니까?" << endl;
}
*/

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

		int num1 = 0;
		int num2 = 0;

		cout << "사용자가 선택한 Jagumon은 ";
		for (int i = 0; i < 3; i++)
			cout << User.at(i).showName() << " ";
		cout << "입니다." << endl;

		cout << "PC가 선택한 Jagumon은 ";
		for (int i = 0; i < 3; i++)
			cout << PC.at(i).showName() << " ";
		cout << "입니다." << endl;

		cout << endl;
		
		// 현재 대결에 출전한 내 자구몬과 pc의 자구몬
		Jagumon presentUser = User.at(num1);
		Jagumon presentPC = PC.at(num2);
		while (num1 < 3 || num2 < 3) {
			while (presentUser.showStamina() != 0 || presentPC.showStamina() != 0) {
				cout << "<1. 공격> <2. 방어> 중 하나를 선택하세요." << endl;
				actingBySpeed(presentUser, presentPC);
				if (presentUser.showStamina() <= 0) {
					if (num1 >= 3)
						break;
					else {
						num1++;
						presentUser = User.at(num1);
						cout << "User의 사용자 자구몬이 " << presentUser.showName() << "으로 바뀌었습니다!" << endl;
					}
				}
				else if (presentPC.showStamina() <= 0) {
					if (num2 == 3)
						break;
					else {
						num2++;
						presentPC = PC.at(num2);
						cout << "PC의 사용자 자구몬이 " << presentPC.showName() << "으로 바뀌었습니다!" << endl;
					}
				}
			}
		}
		if (num1 == 3)
			cout << "당신의 자구몬 3마리 모두 사망했습니다. 패배하셨습니다." << endl;
		else if(num2 == 3)
			cout << "PC의 자구몬 3마리 모두 사망했습니다. 승리하셨습니다." << endl;
	}
	else if (choice == "Exit" || choice == "exit")
		exit;
}