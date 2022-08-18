#include <iostream>
#include <string>
#include "treasure.h"

Treasure::Treasure(int row, int col, std::string type, std::string name) :
Item{row, col, type, name}
{
  pick = true;
  if (name == "small") {
    value = 1;
  } else if (name == "normal") {
    value = 2;

  } else if (name == "merchant") {
    value = 4;
  } else if (name == "dragon") {
    value = 6;
    pick = false;
  }
}

Treasure::~Treasure() {
}

bool Treasure::pickAble() {
  return pick;
}

void Treasure::isGone() {
  if (name == "dragon") {
    pick = true;
  }
}

void Treasure::useGold(Player* curPlayer, Floor *currentFloor) {
  curPlayer->setGold(curPlayer->getGold() + value);
  if (getType()=="Treasure")
  {
    currentFloor->removeItem(row, col);
  }
  action += "You picked up some gold! ";
}
