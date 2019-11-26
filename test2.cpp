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

	//��������� (���� ����)
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

vector<Jagumon> User(3); //����ڰ� ������ �ڱ����� ������ ���� 
vector<Jagumon> PC(3); //pc�� �ڱ����� ������ ����

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
	
	cout << "<< ����! ���� ������ 1��° -> 2��° -> 3��° �ڱ��� �����̹Ƿ� �����ϰ� ����ּ���! >>" << endl;
	for (int i = 1; i < 4; i++) {

		cout << "���ϴ� �ڱ����� �̸��� �Է��ϼ���!" << endl;
		
		cin >> jagumoncall;
		cout << "\n";
		
		if (jagumoncall == "AAA") {
			User[i - 1] = AAA;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << AAA.showName() << " �Դϴ�." << endl;
		}
		else if (jagumoncall == "BBB") {
			User[i - 1] = BBB;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << BBB.showName() << " �Դϴ�." << endl;
		}	
		else if (jagumoncall == "CCC") {
			User[i - 1] = CCC;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << CCC.showName() << " �Դϴ�." << endl;
		}
		else if (jagumoncall == "DDD") {
			User[i - 1] = DDD;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << DDD.showName() << " �Դϴ�." << endl;
		}
		else if (jagumoncall == "EEE") {
			User[i - 1] = EEE;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << EEE.showName() << " �Դϴ�." << endl;
		}
		else if (jagumoncall == "GGG") {
			User[i - 1] = GGG;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << GGG.showName() << " �Դϴ�." << endl;
		}
		else if (jagumoncall == "HHH") {
			User[i - 1] = HHH;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << HHH.showName() << " �Դϴ�." << endl;
		}
		else if (jagumoncall == "JJJ") {
			User[i - 1] = JJJ;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << JJJ.showName() << " �Դϴ�." << endl;
		}
		else if (jagumoncall == "KKK") {
			User[i - 1] = KKK;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << KKK.showName() << " �Դϴ�." << endl;
		}
		else if (jagumoncall == "LLL") {
			User[i - 1] = LLL;
			cout << "�����Ͻ� " << i << "��° �ڱ����� " << LLL.showName() << " �Դϴ�." << endl;
		}
		else {
			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl;
			i--;
		}
		cout << endl;
	}
}
//����ڰ� �� ���� ������ ��ü �� 3�� �������� ���� ������ �Ѵ�.
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
*/
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
// ���� ���¸�ŭ ������ ü�� ȸ��
void Defense(Jagumon &user, Jagumon &pc) { //ù��° ���ڰ� �ι�° ������ ������ ���
	cout << user.showName() << "��(��) �� �����߽��ϴ�!" << endl;
	cout << user.showName() << "�� ü���� " << user.showDefense() << " ��ŭ ȸ���Ǿ����ϴ�."<<endl;
	user.setStamina(user.showStamina() + user.showDefense());
	cout << user.showName() << "�� ���� ü�� : " << user.showStamina() << endl;
	cout << pc.showName() << "�� ���� ü�� : " << pc.showStamina() << endl;
	/*
	if (user.showDefense() > pc.showPower()) { // user�� ������ pc�� ���ݷº��� ���� �� : ��� ���� + ü�� 10 ����
		cout<< user.showName() << "��(��) �� �����߽��ϴ�!" << endl;
		user.setStamina(user.showStamina() + 10);
		cout << user.showName() << "�� ���� ü�� : " << user.showStamina() << endl;
		cout << pc.showName() << "�� ���� ü�� : " << pc.showStamina() << endl;
	}
	else { // user�� ������ pc�� ���ݷº��� ���� �� : user�� ü���� pc�� ���ݷ¸�ŭ ����
		cout << user.showName() << "�� ü���� " << pc.showPower() << "��ŭ �����߽��ϴ�!" << endl;
		user.setStamina(pc.showStamina() - pc.showPower());
		if (user.showStamina() <= 0)
			cout << user.showName() << "�� ����߽��ϴ�." << endl;
		else
			cout << user.showName() << "�� ���� ü�� : " << user.showStamina() << endl;
		cout << pc.showName() << "�� ���� ü�� : " << pc.showStamina() << endl;
	}
	cout << endl;
	*/
}
//���ݰ� ���� �� �ϳ��� �����ϴ� �Լ� 
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

//�ڱ����� �̵��ӵ��� ���� �켱������ �����ϴ� �Լ�
void actingBySpeed(Jagumon &user, Jagumon &pc) {
	if (user.showSpeed() > pc.showSpeed()) { // �� �ӵ�(ù��° ����)�� ������ �ӵ�(�ι�° ����)���� ���� ���
		makeTurn(user, pc); // �� �� ���� ����
		makeTurn(pc, user); // �� �� ��� �� ���� -> �̰� ��ǻ���� ���� �Լ��� ��ü�ؾ���!
	}
	else {
		makeTurn(pc, user);
		makeTurn(user, pc);
	}
	//(user.showSpeed() > pc.showSpeed()) ? makeTurn(user, pc) : makeTurn(pc, user);
}



/*
void Change(Jagumon user) {
	cout << "� �ڱ������� ��ü�Ͻðڽ��ϱ�?" << endl;
}
*/

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

		int num1 = 0;
		int num2 = 0;

		cout << "����ڰ� ������ Jagumon�� ";
		for (int i = 0; i < 3; i++)
			cout << User.at(i).showName() << " ";
		cout << "�Դϴ�." << endl;

		cout << "PC�� ������ Jagumon�� ";
		for (int i = 0; i < 3; i++)
			cout << PC.at(i).showName() << " ";
		cout << "�Դϴ�." << endl;

		cout << endl;
		
		// ���� ��ῡ ������ �� �ڱ���� pc�� �ڱ���
		Jagumon presentUser = User.at(num1);
		Jagumon presentPC = PC.at(num2);
		while (num1 < 3 || num2 < 3) {
			while (presentUser.showStamina() != 0 || presentPC.showStamina() != 0) {
				cout << "<1. ����> <2. ���> �� �ϳ��� �����ϼ���." << endl;
				actingBySpeed(presentUser, presentPC);
				if (presentUser.showStamina() <= 0) {
					if (num1 >= 3)
						break;
					else {
						num1++;
						presentUser = User.at(num1);
						cout << "User�� ����� �ڱ����� " << presentUser.showName() << "���� �ٲ�����ϴ�!" << endl;
					}
				}
				else if (presentPC.showStamina() <= 0) {
					if (num2 == 3)
						break;
					else {
						num2++;
						presentPC = PC.at(num2);
						cout << "PC�� ����� �ڱ����� " << presentPC.showName() << "���� �ٲ�����ϴ�!" << endl;
					}
				}
			}
		}
		if (num1 == 3)
			cout << "����� �ڱ��� 3���� ��� ����߽��ϴ�. �й��ϼ̽��ϴ�." << endl;
		else if(num2 == 3)
			cout << "PC�� �ڱ��� 3���� ��� ����߽��ϴ�. �¸��ϼ̽��ϴ�." << endl;
	}
	else if (choice == "Exit" || choice == "exit")
		exit;
}