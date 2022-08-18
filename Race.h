#ifndef _RACE_H_
#define _RACE_H_

#include<string>
#include "Player.h"

class Race {
  std::string name;
  int maxHp, hp, atk, def, regen, hpSteal, goldKill;
  double potFx, scoreMultiplier;
public:
  Race(std::string name, int maxHp, int hp, int atk, int def, int regen, int hpSteal, int goldKill, double potFx, double scoreMultiplier);
  void beRace(Player*);
};

class Shade : public Race {
public:
  Shade();
};

class Drow : public Race {
public:
  Drow();
};

class Vampire : public Race {
public:
  Vampire();
};

class Troll : public Race {
public:
  Troll();
};

class Goblin : public Race {
public:
  Goblin();
};

#endif
