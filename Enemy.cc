#include <cstdlib>
#include <cmath>
#include "Enemy.h"

using namespace std;

Enemy::Enemy(int y, int x) : locationY{y}, locationX{x}
{
  isAlive = true;
}

Enemy::~Enemy() {
}

string Enemy::getType() {
  return type;
}

int Enemy::getLocationX() {
  return locationX;
}

int Enemy::getLocationY() {
  return locationY;
}

void Enemy::refreshTurn() {
  hasMoved = false;
}

// Helper function for attack

int Enemy::damageCalc(Player *curPlayer) {

  double damage = (100 + curPlayer->getDef());
  damage = 100/damage;
  damage *= atk;
  damage = ceil(damage);
  return damage;
}

void Enemy::attack(Player* curPlayer) {
  int randInt = rand() % 2; // 50% chance attack misses

  // attack lands
  if (randInt == 1) {
    int damage = damageCalc(curPlayer);
    //Orcs does 50% more damage to Goblins
    if (type == "Orcs" && curPlayer->getRace() == "Goblins") {
      const int INCREASE_ATTACK = 1.5;
      damage = damage * INCREASE_ATTACK;
    }

    // updating player hp
    curPlayer->setHp(curPlayer->getHp()-damage);
    if (curPlayer->getHp() <= 0) {
      damage = damage + curPlayer->getHp();
      curPlayer->setHp(0);
      isAlive = false;
    }
    action += type;
    action += " attacked!";
    // attack misses
  } else {
    action = type + " attacked and missed.";
  }
  hasMoved = true;
}

void Enemy::move(Floor* currentFloor) {

  int x_change;
  int y_change;

  while (!hasMoved) {
    y_change = 0;
    x_change = 0;
    int chance = rand() % 8;
    if (chance == 1) {
      x_change++;
    } else if (chance == 2) {
      y_change++;
    } else if (chance == 3) {
      x_change--;
    } else if (chance == 4) {
      y_change--;
    } else if (chance == 5) {
      x_change++;
      y_change++;
    } else if (chance == 6) {
      x_change++;
      y_change--;
    } else if (chance == 7) {
      x_change--;
      y_change--;
    } else if (chance == 8) {
      x_change--;
      y_change++;
    }
    int afterY = locationY + y_change;
    int afterX = locationX + x_change;
    cout << "Before checking for wall"  << endl;
    if (afterY < 0 || afterY > 24 || afterX < 0 || afterX > 78){
      continue;
    }
    // check if the location is out of bounds
    else if (currentFloor->getWallAt(afterY, afterX) == 3 &&
    !(currentFloor->enemyThereFloor[afterY][afterX]) &&
    !(currentFloor->itemThereFloor[afterY][afterX])) {
      locationX = afterX;
      locationY = afterY;
      currentFloor->enemyThereFloor[afterY][afterX] = true; /////
      hasMoved = true;
      cout << "currentEnemy has moved" << endl;

    }
    cout << "After checking for wall"  << endl;
  }
}

bool Merchant::hostile = false;

void Merchant::makeHostile() {
  hostile = true;
}

bool Merchant::isHostile() {
  return hostile;
}

Merchant::Merchant(int y, int x) : Enemy(y, x) {
  type = "Merchant";
  hp = 30;
  atk = 70;
  def = 5;
  hostile = false;
}

Human::Human(int y, int x) : Enemy(y, x) {
  type = "Human";
  hp = 140;
  atk = 20;
  def = 20;
}

Dragon::Dragon(int y, int x, Item *i) : Enemy(y, x), hoard{i}
{
  type = "Dragon";
  hp = 150;
  atk = 20;
  def = 20;
}

void Dragon::move(Floor *){
  hasMoved = true;
}

void Dragon::setHoard(Treasure* t) {
  hoard = t;
}

void Dragon::notifyTreasure() {
  hoard->isGone();
}

Dwarf::Dwarf(int y, int x) : NormalEnemy(y, x) {
  type = "Dwarf";
  hp = 100;
  atk = 20;
  def = 30;
}

Elf::Elf(int y, int x) : NormalEnemy(y, x) {
  type = "Elf";
  hp = 140;
  atk = 30;
  def = 10;
}

void Elf::attack(Player* curPlayer) {
  const int NUMTURNS = 2;
  if (curPlayer->getRace() != "Drow") {
    for (int i = 0; i < NUMTURNS; i++) {
      NormalEnemy::attack(curPlayer);
    }
  } else {
    NormalEnemy::attack(curPlayer);
  }
}

Orcs::Orcs(int y, int x) : NormalEnemy(y, x) {
  type = "Orcs";
  hp = 180;
  atk = 30;
  def = 25;
}

Halfling::Halfling(int y, int x) : NormalEnemy(y, x) {
  type = "Halfling";
  hp = 100;
  atk = 15;
  def = 20;
}

int Enemy::getDef() {
  return def;
}

int Enemy::getHp() {
  return hp;
}

void Enemy::setHp(int amount) {
  hp = amount;
}

void Enemy::dies(Floor *currentFloor, Player *curPlayer) {
  if (type == "Dragon") {
    notifyTreasure();
  } else if (type == "Human") {
    Treasure *t = new Treasure(locationY, locationX, "Treasure", "normal");
    currentFloor->dropTreasureAt(locationY, locationX, t);
    for (int y = -1; y <= 1; y++) {
      for (int x = -1; x <= 1; x++) {
        if (!currentFloor->isItemAt((locationY + y), (locationX + x)) && !currentFloor->isEnemyAt((locationY + y), locationX + x)) {
          Treasure *t1 = new Treasure((locationY + y), (locationX + x), "Treasure", "normal");
          currentFloor->dropTreasureAt(locationY + y, locationX + x, t1);
        }
      }
    }
  } else if (type == "Merchant") {
    Treasure *t = new Treasure(locationY, locationX, "Treasure", "merchant");
    currentFloor->dropTreasureAt(locationY, locationX, t);
  } else {
    curPlayer->setGold(curPlayer->getGold() + goldDrop());
  }
  currentFloor->removeEnemy(locationY,locationX);
  action += type;
  action += " died! ";
}

NormalEnemy::NormalEnemy(int y, int x) : Enemy(y, x) {
}

int NormalEnemy::goldDrop() {
  const int small = 1;
  const int normal = 2;
  int gold = rand() % 2;
  if (gold == 1) {
    return small;
  } else {
    return normal;
  }
}

NormalEnemy::~NormalEnemy() {
}

Human::~Human() {
}

Merchant::~Merchant() {
}

Dragon::~Dragon() {
}

Dwarf::~Dwarf() {
}

Elf::~Elf() {
}

Orcs::~Orcs() {
}

Halfling::~Halfling() {
}

void Enemy::notifyTreasure(){}

int Enemy::goldDrop(){return 0;}

void Enemy::setHoard(Item* i){}

bool Enemy::isHostile(){return false;}
