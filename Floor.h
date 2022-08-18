#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Chamber.h"
#include "Enemy.h"
#include "factory.h"
#include "item.h"
#include "potion.h"
#include "treasure.h"
#include "Player.h"
#include "Race.h"
#include "global.h"
class Factory;
class Enemy;

class Floor {
  std::string mapSeed;
  Chamber** chamberList;
  int** wallFloor;
  Item*** itemFloor;
  bool** itemThereFloor;
  Enemy*** enemyFloor;
  bool** enemyThereFloor;
  std::vector<Item*> dragonHoards;
  int floorCount = 1;
  Player* curPlayer;
  friend class Enemy;

public:
  Floor();
  Floor(std::string,Player*);
  ~Floor();

  Item* lookForHoard(int, int);
  Enemy* lookForEnemy(int, int);
  Item* lookForPotion(int, int);

  int getWallAt(int, int);
  bool isItemAt(int, int);
  Item* getItemAt(int, int);
  bool isEnemyAt(int, int);
  Enemy* getEnemyAt(int, int);
  void removeItem(int, int);
  void removeEnemy(int, int);

  void placeDragon(Factory, Item*);
  void dropTreasureAt(int, int, Treasure*);
  void floorAfterTurn(Player *);
  void enemyMovePhase();
  void startTurn(Player*);
};

#endif
