#ifndef _POTION_H_
#define _POTION_H_

#include "item.h"
#include "Player.h"

class Player;

class Potion : public Item {
  int value;
  bool known;
public:
  Potion(int row, int col, std::string type, std::string name);
  ~Potion();
  int getValue();
  bool getReveal();
  void setReveal();
  void usePotion(Player*);
};



#endif
