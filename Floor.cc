#include "Floor.h"
#include <vector>
#include <utility>
using namespace std;

Floor::Floor() {

  //NOTE
  //calls and declares 5 chambers to be located with chamberList
  chamberList = new Chamber*[5];
  for (int x = 1; x <= 5; x++) {
    chamberList[x] = new Chamber(x);
  }

  wallFloor = new int*[25]; //implement these with smart pointers
  for (int y = 0; y < 25; y++) {
    wallFloor[y] = new int[79];
    for (int x = 0; x < 79; x++) {
      wallFloor[y][x] = 0;
    }
  }

  // 1 is -, 2 is |, 3 is . (floor), 4 is + (door), 5 is # (passage), 6 is space, 7 is stairs
  itemFloor = new Item**[25];
  for (int y = 0; y < 25; y++) {
    itemFloor[y] = new Item* [79];
    for (int x = 0; x < 79; x++) {
      itemFloor[y][x] = nullptr;
    }
  }
  itemThereFloor = new bool*[25];
  for (int y = 0; y < 25; y++) {
    itemThereFloor[y] = new bool[79];
    for (int x = 0; x < 79; x++) {
      itemThereFloor[y][x] = false;
    }
  }
  enemyFloor = new Enemy**[25];
  for (int y = 0; y < 25; y++) {
    enemyFloor[y] = new Enemy* [79];
    for (int x = 0; x < 79; x++) {
      enemyFloor[y][x] = nullptr;
    }
  }
  enemyThereFloor = new bool*[25];
  for (int y = 0; y < 25; y++) {
    enemyThereFloor[y] = new bool[79];
    for (int x = 0; x < 79; x++) {
      enemyThereFloor[y][x] = false;
    }
  }


  Factory currentFloorFactory(chamberList);
  Item* generatedPotion;
  Item* generatedTreasure;
  Enemy* generatedEnemy;
  int row, col;

  curPlayer = currentFloorFactory.GeneratePlayer();

  row = currentFloorFactory.GenerateStairs().second; //second is the y value, first is the x value
  col = currentFloorFactory.GenerateStairs().first;

  wallFloor[row][col] = 7;
  //NOTE generation of the wallFloor



  for (int x = 0; x < 10; x++) {
    generatedPotion = currentFloorFactory.GeneratePotion();
    row = generatedPotion->getRow();
    col = generatedPotion->getCol();
    itemThereFloor[row][col] = true;
    itemFloor[row][col] = generatedPotion;
  }

  for (int x = 0; x < 10; x++) {
    generatedTreasure = currentFloorFactory.GenerateTreasure();
    row = generatedTreasure->getRow();
    col = generatedTreasure->getCol();
    itemThereFloor[row][col] = true;
    itemFloor[row][col] = generatedTreasure;
    if (generatedTreasure->getType() == "dragon") {
      dragonHoards.push_back(generatedTreasure);
    }
  }

  for (int x = 0; x < 20; x++) {
    generatedEnemy = currentFloorFactory.GenerateEnemy();
    row = generatedEnemy->getLocationX();
    col = generatedEnemy->getLocationY();
    enemyThereFloor[row][col] = true;
    enemyFloor[row][col] = generatedEnemy;
  }
  int size = dragonHoards.size();
  for (int x = 0; x < size; x++) //places all dragons in relation to their hoards
  {
    placeDragon(currentFloorFactory, dragonHoards[x]);
  }

}

Floor::Floor(string mapFile,Player* curPlayer) {

  wallFloor = new int*[25]; //implement these with smart pointers
  for (int y = 0; y < 25; y++) {
    wallFloor[y] = new int[79];
    for (int x = 0; x < 79; x++) {
      wallFloor[y][x] = 0;
    }
  }

  // 1 is -, 2 is |, 3 is . (floor), 4 is + (door), 5 is # (passage), 6 is space, 7 is stairs
  itemFloor = new Item**[25];
  for (int y = 0; y < 25; y++) {
    itemFloor[y] = new Item* [79];
    for (int x = 0; x < 79; x++) {
      itemFloor[y][x] = nullptr;
    }
  }
  itemThereFloor = new bool*[25];
  for (int y = 0; y < 25; y++) {
    itemThereFloor[y] = new bool[79];
    for (int x = 0; x < 79; x++) {
      itemThereFloor[y][x] = false;
    }
  }
  enemyFloor = new Enemy**[25];
  for (int y = 0; y < 25; y++) {
    enemyFloor[y] = new Enemy* [79];
    for (int x = 0; x < 79; x++) {
      enemyFloor[y][x] = nullptr;
    }
  }
  enemyThereFloor = new bool*[25];
  for (int y = 0; y < 25; y++) {
    enemyThereFloor[y] = new bool[79];
    for (int x = 0; x < 79; x++) {
      enemyThereFloor[y][x] = false;
    }
  }

  mapSeed = mapFile;
  ifstream input(mapFile); //  The input file
  string line;
  for (int x = 0; x < whereToStart; x++) {
    getline(input, line);

  }

  for (int y = 0; y < 25; y++) {
    getline(input, line);

    for (int x = 0; x < 79; x++) {
      // 1 is -, 2 is |, 3 is . (floor), 4 is + (door), 5 is # (passage), 6 is space, 7 is stairs

      if (line[x] == '|') {
        wallFloor[y][x] = 1;
      } else if (line[x] == '-') {
        wallFloor[y][x] = 2;
      } else if (line[x] == '.') {
        wallFloor[y][x] = 3;
      } else if (line[x] == '+') {
        wallFloor[y][x] = 4;
      } else if (line[x] == '#') {
        wallFloor[y][x] = 5;
      } else if (line[x] == ' ') {
        wallFloor[y][x] = 6;
      } else if (line[x] == '\\') {
        wallFloor[y][x] = 7;
      } else {
        wallFloor[y][x] = 3;
        if (line[x] == '@') {
          if (whereToStart==0)
          {
            Player* temp=curPlayer;
            delete temp;
            curPlayer = new Player(raceInput);
          }
          curPlayer->setLocation(y, x);

        }
        else if (line[x] == 'H') {
          enemyThereFloor[y][x] = true;
          enemyFloor[y][x] = new Human(y, x);
        } else if (line[x] == 'W') {
          enemyThereFloor[y][x] = true;
          enemyFloor[y][x] = new Dwarf(y, x);
        } else if (line[x] == 'E') {
          enemyThereFloor[y][x] = true;
          enemyFloor[y][x] = new Elf(y, x);
        } else if (line[x] == 'O') {
          enemyThereFloor[y][x] = true;
          enemyFloor[y][x] = new Orcs(y, x);
        } else if (line[x] == 'M') {
          enemyThereFloor[y][x] = true;
          enemyFloor[y][x] = new Merchant(y, x);
        } else if (line[x] == 'D') {
          enemyThereFloor[y][x] = true;
          enemyFloor[y][x] = new Dragon(y, x, nullptr);

        } else if (line[x] == 'L') {
          enemyThereFloor[y][x] = true;
          enemyFloor[y][x] = new Halfling(y, x);
        }//end of reading in enemy cases

        else if (line[x] == '0') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Potion(y, x, "Potion", "RH");
        } else if (line[x] == '1') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Potion(y, x, "Potion", "BA");
        } else if (line[x] == '2') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Potion(y, x, "Potion", "BD");
        } else if (line[x] == '3') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Potion(y, x, "Potion", "PH");
        } else if (line[x] == '4') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Potion(y, x, "Potion", "WA");
        } else if (line[x] == '5') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Potion(y, x, "Potion", "WD");
        }//end of reading in potions cases

        else if (line[x] == '6') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Treasure(y, x, "Treasure", "small");
        } else if (line[x] == '7') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Treasure(y, x, "Treasure", "normal");
        } else if (line[x] == '8') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Treasure(y, x, "Treasure", "merchant");
        } else if (line[x] == '9') {
          itemThereFloor[y][x] = true;
          itemFloor[y][x] = new Treasure(y, x, "Treasure", "dragon");
        }
      }//end of non-wall cases
    }//end of one row of input
  }//end of reading in input
  for (int y = 0; y < 25; y++) //linking dragons with their hoards
  {
    for (int x = 0; x < 79; x++) {
      if (enemyThereFloor[y][x]) {
        Enemy* searchingDragon = enemyFloor[y][x];
        if (searchingDragon->getType() == "Dragon") {
          Item* foundHoard = lookForHoard(searchingDragon->getLocationY(), searchingDragon->getLocationX());
          searchingDragon->setHoard(foundHoard);
        }
      }
    }
  }
  whereToStart += 25;
}

Floor::~Floor() {
  for (int y = 0; y < 25; y++) {
    for (int x = 0; x < 79; x++) {
      delete itemFloor[y][x];
      delete enemyFloor[y][x];
    }

    delete wallFloor[y];
    delete itemThereFloor[y];
    delete itemFloor[y];
    delete enemyThereFloor[y];
    delete enemyFloor[y];

  }

}

Item* Floor::lookForHoard(int row, int col) {
  for (int y = row - 1; y <= row + 1; y++) {
    for (int x = col - 1; x <= col + 1; x++) {
      if (itemThereFloor[y][x]&&(itemFloor[y][x])->getName() == "dragon") {
        return itemFloor[y][x];
      }
    }
  }
  return nullptr;
}

Enemy* Floor::lookForEnemy(int row, int col) {
  for (int y = row - 1; y <= row + 1; y++) {
    for (int x = col - 1; x <= col + 1; x++) {
      if (enemyThereFloor[y][x]&&!(enemyFloor[y][x]->hasMoved))

      return enemyFloor[y][x];
    }
  }

  return nullptr;
}

Item* Floor::lookForPotion(int row, int col) {
  for (int y = row - 1; y <= row + 1; y++) {
    for (int x = col - 1; x <= col + 1; x++) {
      if (itemThereFloor[y][x]) {
        if (itemFloor[y][x]->getType() == "Potion") {
          return itemFloor[y][x];
        }
      }
    }
  }
  return nullptr;
}

int Floor::getWallAt(int row, int col) {
  return wallFloor[row][col];
}

bool Floor::isItemAt(int row, int col) {
  return itemThereFloor[row][col];
}

Item* Floor::getItemAt(int row, int col) {
  return itemFloor[row][col];
}

bool Floor::isEnemyAt(int row, int col) {
  return enemyThereFloor[row][col];
}

Enemy* Floor::getEnemyAt(int row, int col) {
  return enemyFloor[row][col];
}

void Floor::removeItem(int row, int col) {
  itemThereFloor[row][col] = false;
}

void Floor::removeEnemy(int row, int col) {
  enemyThereFloor[row][col] = false;
}

void Floor::dropTreasureAt(int row, int col, Treasure* droppedTreasure) {
  itemThereFloor[row][col] = true;
  itemFloor[row][col] = droppedTreasure;
}

void Floor::placeDragon(Factory f, Item* hoard) {
  int row = hoard->getRow();
  int col = hoard->getCol();
  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      if (!itemThereFloor[row + y][col + x]&&!enemyThereFloor[row + y][col + x]) {
        f.GenerateDragon(row + y, col + x, hoard);
        break;
      }
    }
  }
}

void Floor::floorAfterTurn(Player* curPlayer) {
  int col = 79;
  int row = 25;

  for (int y = 0; y < row; y++) {
    for (int x = 0; x < col; x++) {
      if (y == curPlayer->row && x == curPlayer->col) //check for player at (x,y)
      {
        cout << "@";
      } else if (isItemAt(y, x)) //check for item at (x,y)
      {
        Item* item = getItemAt(y, x);
        string type = item->getType();
        if (type == "Treasure") {
          cout << "G";
        } else if (type == "Potion") {
          cout << "P";
        }
      }//end of item display
      else if (isEnemyAt(y, x)) //check for enemy at (x,y);
      {
        Enemy* enemy = getEnemyAt(y, x);
        string type = enemy->getType();
        // displays the correct symbol depending on the type of enemy;
        if (type == "Human") {
          cout << "H";
        } else if (type == "Dwarf") {
          cout << "W";
        } else if (type == "Elf") {
          cout << "E";
        } else if (type == "Orcs") {
          cout << "O";
        } else if (type == "Merchant") {
          cout << "M";
        } else if (type == "Dragon") {
          cout << "D";
        } else if (type == "Halfling") {
          cout << "L";
        }
        //end of enemy type displays
      }//end of enemy display

      else //display of walls/doors/space
      {
        int type = getWallAt(y, x);

        if (type == 1) {
          cout << "|";
        } else if (type == 2) {
          cout << "-";
        } else if (type == 3) {
          cout << "."; //floor
        } else if (type == 4) {
          cout << "+"; //door
        } else if (type == 5) {
          cout << "#"; //passage between chambers
        } else if (type == 6) {
          cout << " "; //space outside of the chambers, impassable
        } else if (type == 7) {
          cout << "\\";
        }

      }//end of wall display
    }//end of one row
    cout << endl;
  }//end of floor display
}//end of floor display function

void Floor::enemyMovePhase() {
  /*
  for (int y = 0; y < 25; y++) {
  for (int x = 0; x < 79; x++) {
  if (enemyThereFloor[y][x]) {
  enemyThereFloor[y][x] = false; /////
  cout << "Found enemy, getting pointer" << endl;
  Enemy* currentEnemy = enemyFloor[y][x];
  cout << "Got enemy pointer!" << endl;

  if (!currentEnemy->hasMoved) {
  cout << "Before currentEnemy moves" << endl;

  currentEnemy->move(this);
  cout << "After currentEnemy moves"  << endl;

}
}
}
}
cout << "End of enemyMovePhase" << endl; */
}

void Floor::startTurn(Player *curPlayer)//refreshes the action availability of player and enemies
{
  curPlayer->refreshTurn();
  for (int y = 0; y < 25; y++) {
    for (int x = 0; x < 79; x++) {
      if (enemyThereFloor[y][x]) {
        enemyFloor[y][x]->refreshTurn();
      }
    }
  }
}
