#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <stdlib.h>
#include "game.h"
#include "JagumonData.h"

void Attack(Jagumon &user, Jagumon &other) {
  if(user.showPower() >= other.showStamina()) {
    other.setStamina(0);
  }
  else {
    other.setStamina(other.showStamina() - user.showPower());
  }
}

void Defense(Jagumon &user, Jagumon &other) {
  if(user.showStamina() >= 100) {
    user.setStamina(100);
  }
  else {
    user.setStamina(user.showStamina() + user.showDefense());
  }
}

void actingBySpeed(Jagumon &player, Jagumon &opponent, char choice) {
  opponentRand = rand() % 2;
  if (choice == 'a') {
    if(player.showSpeed() >= opponent.showSpeed()) {
      Attack(player, opponent);
      if(opponentRand == 0) Attack(opponent, player);
      else Defense(opponent, player);
    }
    else if(player.showSpeed() < opponent.showSpeed()) {
      if(opponentRand == 0) Attack(opponent, player);
      else Defense(opponent, player);
      Attack(player, opponent);
    }
  }
  else if(choice == 'd') {
    if(player.showSpeed() >= opponent.showSpeed()) {
      Defense(player, opponent);
      if(opponentRand == 0) Attack(opponent, player);
      else Defense(opponent, player);
    }
    else if(player.showSpeed() < opponent.showSpeed()) {
      if(opponentRand == 0) Attack(opponent, player);
      else Defense(opponent, player);
      Defense(opponent, player);
    }
  }
}
