#include <iostream>
#include <string>
#include <ctime>
#include <random>

#include "game.h"
#include "JagumonData.h"
/*
void MAINPROGRAM() {
  Player();
}

void Player() {

}

void Attack(Jagumon &user, Jagumon &pc) { // user attacks pc
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
*/
