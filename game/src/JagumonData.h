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

std::vector<Jagumon>jagumon = { AAA, BBB, CCC, DDD, EEE, GGG, HHH, JJJ, KKK, LLL };

std::vector<Jagumon> User(3);
std::vector<Jagumon> PC(3);

int opponentRand = 0;

void Attack(Jagumon&, Jagumon&);
void Defense(Jagumon&, Jagumon&);
void actingBySpeed(Jagumon&, Jagumon&, char);

#endif
