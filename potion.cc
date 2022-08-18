#include <iostream>
#include <string>
#include "potion.h"
using namespace std;


Potion::Potion(int row, int col, std::string type, std::string name) :
Item{row, col, type, name}
{
  if (name == "RH") {
    value = 10;
  } else if (name == "BA") {
    value = 5;
  } else if (name == "BD") {
    value = 5;
  } else if (name == "PH") {
    value = -10;
  } else if (name == "WA") {
    value = -5;
  } else if (name == "WD") {
    value = -5;
  }
  known = false;
}

Potion::~Potion() {
}

int Potion::getValue() {
  return value;
}

bool Potion::getReveal() {
  return known;
}

void Potion::setReveal() {
  known = true;
}

void Potion::usePotion(Player *curPlayer) {
  if (name == "RH" || name == "PH") {
    curPlayer->setHp(curPlayer->getHp() + value*(curPlayer->getPotFx()));
  } else if (name == "BA" || name == "WA") {
    curPlayer->changeAtk(value*(curPlayer->getPotFx()));
  } else if (name == "BD" || name == "WD") {
    curPlayer->changeDef(value*(curPlayer->getPotFx()));
  }
}
