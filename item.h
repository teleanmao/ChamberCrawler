#ifndef _ITEMS_H_
#define _ITEMS_H_
#include <string>

class Player;
class Floor;
class Item {
protected:
  int row;
  int col;
  std::string type;
  std::string name;
  bool used = false;
public:
  Item(int row, int col, std::string type, std::string name);
  virtual ~Item() = 0;
  virtual int getRow();
  virtual int getCol();
  virtual void isGone();
  virtual std::string getType();
  virtual std::string getName();
  virtual bool pickAble();
  virtual void useGold(Player*,Floor*);
  virtual void usePotion(Player*);
  virtual bool getReveal();

};



#endif
