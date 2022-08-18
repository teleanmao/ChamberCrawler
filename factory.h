#ifndef __FACTORY_H__
#define __FACTORY_H__
#include <string>
#include <vector>
#include <utility>
#include "Chamber.h"
#include "item.h"
#include "Enemy.h"
#include "Player.h"
#include "treasure.h"
#include "potion.h"

class Enemy;
class Treasure;
class Potion;
class Player;

class Factory {
  int pcplace;
  Chamber** c;
public:
  Factory(Chamber** c);
  ~Factory();
  Potion* GeneratePotion();
  Treasure* GenerateTreasure();
  Enemy* GenerateEnemy();
  Player* GeneratePlayer();
  std::pair<int, int> GenerateStairs();
  Enemy* GenerateDragon(int x, int y, Item *dragon);
};

#endif
