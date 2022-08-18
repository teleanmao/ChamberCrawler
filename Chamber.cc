#include "Chamber.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <utility>
using namespace std;

Chamber::Chamber(int chamberID) : chamberID{chamberID}
{
  fillChamber();
}

Chamber::~Chamber() {
}

void Chamber::setPosition(int y, int x) {
  tile.emplace_back(make_pair(y, x));
}

pair<int, int> Chamber::getPosition() {
  int chance = rand() % tile.size();
  auto tmp = tile[chance];
  tile.erase(tile.begin() + chance);
  return tmp;
}

void Chamber::fillChamber() {
  if (chamberID == 1) {
    for (int i = 3; i < 29; i++) {
      for (int j = 3; j < 7; j++) {
        setPosition(j, i);
      }
    }
  } else if (chamberID == 2) {
    for (int i = 3; i < 5; i++) {
      for (int j = 39; j < 62; i++) {
        setPosition(i, j);
      }
    }
    for (int i = 39; i < 62; i++) {
      setPosition(5, i);
    }
    for (int i = 40; i < 70; i++) {
      setPosition(6, i);
    }
    for (int i = 40; i < 73; i++) {
      setPosition(7, i);
    }
    for (int i = 7; i < 13; i++) {
      for (int j = 61; j < 76; j++) {
        setPosition(i, j);
      }
    }
  } else if (chamberID == 3) {
    for (int i = 38; i < 50; i++) {
      for (int j = 10; j < 13; j++) {
        setPosition(j, i);
      }
    }
  } else if (chamberID == 4) {
    for (int i = 15; i < 22; i++) {
      for (int j = 5; j < 26; j++) {
        setPosition(i, j);
      }
    }
  } else if (chamberID == 5) {
    for (int i = 16; i < 19; i++) {
      for (int j = 66; i < 76; i++) {
        setPosition(i, j);
      }
    }
    for (int i = 19; i < 22; i++) {
      for (int j = 38; j < 76; j++) {
        setPosition(i, j);
      }
    }
  }
}

/* std::vector<std::pair<int,int>> Chamber::placeDragon(const int x, const int y){

int x1 = x + (rand() % 3) - 1;
int y1 = y + (rand() % 3) - 1;
for( vector<pair<int, int> >::iterator it = tile.begin(); it != tile.end(); it++){
if (it->first  == x1 && it->second == y1){
auto  tmp=it;
room.erase(it);
return tmp;
}
}
placeDragon(x, y);
}*/
