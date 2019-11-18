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
	string name; //�̸�
	int power; //���ݷ�
	int defense; //����
	int speed; //�̵��ӵ�
	int stamina; //ü��
public:
	Jagumon() {};
	Jagumon(string name, int power, int defense, int speed, int stamina) { //������
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

	//��������� (���� �����)
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

vector<Jagumon> User(5); //����ڰ� ������ �ڱ����� ������ ���� 
vector<Jagumon> PC(5); //pc�� �ڱ����� ������ ����

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
	cout << "���ϴ� �ڱ����� �̸��� �Է��ϼ���!" << endl;
	
	cin >> jagumoncall;
	cout << "\n";

	for (int i = 0; i < jagumon.size(); i++) {
		if (jagumoncall == jagumon.at(i).showName()) {
			cout << "����� �ڱ����� " << jagumon.at(i).showName() << " �Դϴ�!" << endl;
			found = true;
			
			// User.push_back(jagumoncall); <- ���1 : �Է��� ���� user ���Ϳ� �Է��ϰ����, �ٵ� ���ڷ� int���̶� char���� ����
			// ���2 : ���� �����ڸ� �̿��ؼ� ��ü �ϳ��� �����.
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
			cout << "������ �ڱ����� ������ �߽��ϴ�!" << endl;
			PlayerHealth -= 5;
			turn = false;
			break;
		case 1:
			cout << "������ �ڱ����� �� �߽��ϴ�!" << endl;
			PlayerHealth -= 4;
			turn = false;
			break;
		case 2:
			cout << "������ �ڱ����� ��ü�� �߽��ϴ�!" << endl;
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

void Attack(Jagumon &user, Jagumon &pc) { //ù��° ����(user)�� �ι�° ����(pc)���� ����
	cout << user.showName() << "��(��) ������ �߽��ϴ�!" << endl;
	if (user.showPower() >= pc.showStamina()) { //pc�� ���� ü���� user�� ���ݷº��� ���� �� 
		pc.setStamina(0); // ���
		cout << "������ �ڱ����� ����߽��ϴ�." << endl;
		cout << user.showName() << "�� ���� ü�� : " << user.showStamina() << endl;
	}
	else {
		pc.setStamina(pc.showStamina() - user.showPower()); // pc�� ���� ü���� user�� ���ݷº��� ���� �� : ���ݷ¸�ŭ ü�� ����
		cout << pc.showName() << "�� ü���� " << pc.showStamina() << "�� �����߽��ϴ�!" << endl;
		cout << user.showName() << "�� ���� ü�� : " << user.showStamina() << endl;
		cout << pc.showName() << "�� ���� ü�� : " << pc.showStamina() << endl;
	}
	cout << endl;
}

void Defense(Jagumon &user, Jagumon &pc) { //ù��° ���ڰ� �ι�° ������ ������ ���
	cout << user.showName() << "��(��) �� �����߽��ϴ�!" << endl;
	if (user.showDefense() > pc.showPower()) { // user�� ������ pc�� ���ݷº��� ���� �� : ��� ���� + ü�� 10 ����
		cout<< user.showName() << "��(��) �� �����߽��ϴ�!" << endl;
		user.setStamina(user.showStamina() + 10);
		cout << user.showName() << "�� ���� ü�� : " << user.showStamina() << endl;
		cout << pc.showName() << "�� ���� ü�� : " << pc.showStamina() << endl;
	}
	else { // user�� ������ pc�� ���ݷº��� ���� �� : user�� ü���� pc�� ���ݷ¸�ŭ ����
		cout << user.showName() << "�� ü���� " << user.showStamina() << "�� �����߽��ϴ�!" << endl;
		user.setStamina(pc.showStamina() - pc.showPower());
		cout << user.showName() << "�� ���� ü�� : " << user.showStamina() << endl;
		cout << pc.showName() << "�� ���� ü�� : " << pc.showStamina() << endl;
	}
	cout << endl;
}

void Change(Jagumon user) {
	cout << "� �ڱ������� ��ü�Ͻðڽ��ϱ�?" << endl;
}

int main()
{
	string choice;
	int n;

	cout << "### Welcome to Jagumon ###" << endl;
	cout << "������ �����Ϸ��� 'Go' �� �Է��ϰ� ���Ḧ ���Ͻø� 'Exit' �����ּ���." << endl;
	cin >> choice;
	cout << endl;

	if (choice == "Go" || choice == "go")
	{
		MAINPROGRAM();

		//user���忡�� ����
		
		while (BBB.showStamina() != 0) {
			cout << "<1. ����> <2. ���> <3. ��ü> �� �ϳ��� �����ϼ���." << endl;
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