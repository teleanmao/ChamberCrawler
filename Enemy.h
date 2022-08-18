#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Player.h"
#include "item.h"
#include "treasure.h"
#include "Floor.h"
#include <string>
#include "global.h"

class Player;

class Enemy {
  bool isAlive;
  int locationY;
  int locationX;

protected:
  int damageCalc(Player*);
  int hp;
  int atk;
  int def;
  std::string type;

public:
  bool hasMoved = false;
  Enemy(int y, int x);
  void refreshTurn();
  void attack(Player*);
  void move(Floor*);
  std::string getType();
  int getLocationX();
  int getLocationY();
  int getDef();
  int getHp();
  void setHp(int);
  void dies(Floor *, Player *);
  virtual void notifyTreasure();
  virtual int goldDrop();
  virtual void setHoard(Item*);
  virtual bool isHostile();
  virtual ~Enemy();
};

class NormalEnemy : public Enemy {
public:
  NormalEnemy(int y, int x);
  virtual int goldDrop();
  ~NormalEnemy();
};

class Human : public Enemy {
public:
  Human(int y, int x);
  ~Human();
};

class Merchant : public Enemy {
public:
  static bool hostile;
  bool isHostile();
  void makeHostile();
  Merchant(int y, int x);
  ~Merchant();
};

class Dragon : public Enemy {
  Item* hoard;
public:
  void notifyTreasure();
  Dragon(int y, int x, Item *i);
  void setHoard(Treasure*);
  ~Dragon();
  void move (Floor*);
};

class Dwarf : public NormalEnemy {
public:
  Dwarf(int y, int x);
  ~Dwarf();
};

class Elf : public NormalEnemy {
public:
  Elf(int y, int x);
  void attack(Player*);
  ~Elf();
};

class Orcs : public NormalEnemy {
public:
  Orcs(int y, int x);
  ~Orcs();
};

class Halfling : public NormalEnemy {
public:
  Halfling(int y, int x);
  ~Halfling();
};

#endif
