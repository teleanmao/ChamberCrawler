#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <vector>
#include <utility>
#include "item.h"

class Chamber {
  int chamberID;
  std::vector<std::pair<int, int>> tile;

public:
  Chamber(int chamberID);
  virtual ~Chamber();
  void setPosition(int x, int y);
  std::pair<int, int> getPosition();
  void fillChamber();
  /* std::vector<std::pair<int,int>> placeDragon(const int x, const int y);*/
};

#endif
