#ifndef JAGUMONDATA_H
#define JAGUMONDATA_H

class Jagumon {
private:
  const char* name; // name
  int power; // offense
  int defense; // shield
  int speed; // move priority
  int stamina; // health
public:
  Jagumon() {};
  Jagumon(const char* name, int power, int defense, int speed, int stamina) { //생성자
  this->name = name;
  this->power = power;
  this->defense = defense;
  this->speed = speed;
  this->stamina = stamina;
  }

  const char* showName() {return name;}
  int showPower() { return power;}
  int showDefense() { return defense; }
  int showSpeed() { return speed; }
  int showStamina() { return stamina; }
  void setStamina(int newst) { this->stamina = newst; }

  //복사생성자 (얕은 복사)
  //Jagumon(Jagumon &jagu) {
  //name = jagu.showName();
  //power = jagu.showPower();
  //defense = jagu.showDefense();
  //speed = jagu.showSpeed();
  //stamina = jagu.showStamina();
  //}

};

//Jagumons
Jagumon AAA("AAA", 45, 40, 60, 100);
Jagumon BBB("BBB", 50, 20, 20, 100);
Jagumon CCC("CCC", 30, 50, 30, 100);
Jagumon DDD("DDD", 60, 10, 20, 100);
Jagumon EEE("EEE", 30, 30, 60, 100);
Jagumon GGG("GGG", 40, 45, 40, 100);
Jagumon HHH("HHH", 65, 10, 10, 100);
Jagumon JJJ("JJJ", 40, 50, 20, 100);
Jagumon KKK("KKK", 20, 45, 65, 100);
Jagumon LLL("LLL", 100, 10, 5, 100);

std::vector<Jagumon>jagumon = { AAA, BBB, CCC, DDD, EEE, GGG, HHH, JJJ, KKK, LLL };

std::vector<Jagumon> User(3);
std::vector<Jagumon> PC(3);

int opponentRand = 0;

void Attack(Jagumon&, Jagumon&);
void Defense(Jagumon&, Jagumon&);
void actingBySpeed(Jagumon&, Jagumon&, char);

#endif
