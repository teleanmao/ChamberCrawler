#ifndef __TREASURE_H__
#define __TREASURE_H__
#include "item.h"
#include "Player.h"
#include "Floor.h"
#include <string>

class Player;
class Floor;

class Treasure : public Item {
  int value;
  bool pick;
public:
  Treasure(int row, int col, std::string type, std::string name);
  ~Treasure();
  bool pickAble();
  void isGone();
  void useGold(Player*, Floor*);

};

#endif
