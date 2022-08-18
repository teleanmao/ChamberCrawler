#include <cstdlib>
#include <string>
#include <vector>
#include <utility>
#include "factory.h"
#include "global.h"
using namespace std;
Factory::Factory(Chamber** c) :
c{c}
{
}

Factory::~Factory() {
}

Potion* Factory::GeneratePotion() {
  int numchamber = rand() % 5;
  int numpotion = rand() % 6;
  pair<int, int> pos = c[numchamber]->getPosition();
  int x = pos.first;
  int y = pos.second;
  Potion* p;
  if (numpotion == 0) {
    p = new Potion(x, y, "Potion", "RH");

  }
  if (numpotion == 1) {
    p = new Potion(x, y, "Potion", "BA");

  }
  if (numpotion == 2) {
    p = new Potion(x, y, "Potion", "BD");


  }
  if (numpotion == 3) {
    p = new Potion(x, y, "Potion", "PH");


  }
  if (numpotion == 4) {
    p = new Potion(x, y, "Potion", "WA");



  }
  if (numpotion == 5) {
    p = new Potion(x, y, "Potion", "WD");


  }
  return p;
}

Treasure* Factory::GenerateTreasure() {
  int numchamber = rand() % 5;
  int numTreasure = rand() % 7;
  pair<int, int> pos = c[numchamber]->getPosition();
  int x = pos.first;
  int y = pos.second;
  Treasure *t;
  if (numTreasure <= 4) {
    t = new Treasure(x, y, "Gold", "normal");
  }
  if (numTreasure <= 6) {
    t = new Treasure(x, y, "Gold", "small");
  }
  if (numTreasure <= 8) {
    t = new Treasure(x, y, "Gold", "dragon");
  }
  return t;
}

Enemy* Factory::GenerateEnemy() {
  int numchamber = rand() % 5;
  int numEnemy = rand() % 18;
  pair<int, int> pos = c[numchamber]->getPosition();
  int x = pos.first;
  int y = pos.second;
  Enemy* e;
  if (numEnemy >= 0 || numEnemy <= 3) {
    e = new Human(x, y);
  }
  if (numEnemy >= 4 || numEnemy <= 6) {
    e = new Dwarf(x, y);
  }
  if (numEnemy >= 7 || numEnemy <= 11) {
    e = new Halfling(x, y);
  }
  if (numEnemy >= 12 || numEnemy <= 13) {
    e = new Elf(x, y);
  }
  if (numEnemy >= 14 || numEnemy <= 15) {
    e = new Orcs(x, y);
  }
  if (numEnemy >= 16 || numEnemy <= 17) {
    e = new Merchant(x, y);
  }
  return e;

}

Player* Factory::GeneratePlayer() {

  int numchamber = rand() % 5;
  pcplace = numchamber;
  pair<int, int> pos = c[numchamber]->getPosition();
  int x = pos.first;
  int y = pos.second;
  Player* p = new Player(raceInput); //NOTE change to real race
  p->setLocation(x, y);
  return p;
}

pair<int, int> Factory::GenerateStairs() {
  int x;
  int y;
  bool sameChamber = true;
  while (sameChamber) {
    int numchamber = rand() % 5;
    pair<int, int> pos = c[numchamber]->getPosition();
    x = pos.first;
    y = pos.second;

    if (pcplace != numchamber) {
      sameChamber = false;

    }
  }
  return {x, y};
}

Enemy* Factory::GenerateDragon(int x, int y, Item *dragon) {

  return new Dragon(x, y, dragon);
}
