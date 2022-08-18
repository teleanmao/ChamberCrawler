#include <iostream>
#include <string>
#include <memory>
#include <fstream>

using namespace std;
#include "Floor.h"
#include "Player.h"
#include "Race.h"
#include "Enemy.h"
#include "global.h"

int floorsCompleted = 0;
int whereToStart = 0;

string action;
bool stairReached;
char raceInput;
const string MAP_FILE = "cc3kfloor.txt";
bool gameOver=false;

void printInfo(Player* curPlayer) {
  cout << "Race: " << curPlayer->getRace() << " Gold: " << curPlayer->getGold();
  for (int i = 0; i < 50; i++) {
    cout << " ";
  }
  cout << "Floor " << floorsCompleted << endl;
  cout << "HP: " << curPlayer->getHp() << endl;
  cout << "Atk: " << curPlayer->getAtk() << endl;
  cout << "Def: " << curPlayer->getDef() << endl;
  cout << "Action: " << action << endl;
  action = "";
}

Floor* nextFloor(Floor* currentFloor,Player* curPlayer) {

  Floor* temp = currentFloor;


  currentFloor = new Floor(MAP_FILE,curPlayer);
  delete temp;

  return currentFloor;

}

void printCommand() {
  cout << "Enter a valid command: " << endl;
  cout << "Change direction: no, so, ea, we, ne, se, sw, nw" << endl;
  cout << "Use potion: u <direction>" << endl;
  cout << "Attack enemy: a <direction>" << endl;
  cout << "Stop/Allow enemy movement: f" << endl;
  cout << "Restart the game: r" << endl;
  cout << "Quit: q" << endl;
}

char createPlayer() {
  while (true) {
    char input;

    // Choosing a player
    cout << "Choose a race for the player:" << endl;
    cout << "Shade: 125 HP, 25 ATK, 25 DEF" << endl;
    cout << "\tEffect: Score increases by 50%" << endl;
    cout << "Drow: 150 HP, 25 ATK, 15 DEF" << endl;
    cout << "\tEffect: All potions are magnified by 1.5" << endl;
    cout << "Vampire: 50 HP, 25 ATK, 25 DEF" << endl;
    cout << "\tEffect: Gains 5 HP every successful attack "
    << "(loses 5 HP from Dwarfs) and no maximum HP" << endl;
    cout << "Troll: 120 HP, 25 ATK, 15 DEF" << endl;
    cout << "\tEffect: Regains 5 HP every turn; HP is capped at 120 HP" << endl;
    cout << "Goblin: 110 HP, 15 ATK, 20 DEF" << endl;
    cout << "\tEffect: Steals 5 gold from every slain enemy" << endl;
    cout << "Type: s for shade, d for drow, v for vampire, "
    << "t for troll, and g for goblin" << endl;
    cin >> input;
    raceInput = input;

    // Creating player
    if (input == 's' || input == 'd' || input == 'v'
    || input == 't' || input == 'g') {
      return input;
    } else {
      cout << "Please make a valid selection." << endl;
    }
  }
}

void usePotion(Player* curPlayer, Floor* currentFloor) {
  string dir;
  cin >> dir;

  if (dir == "no" || dir == "ea" || dir == "so" || dir == "we" || dir == "ne" || dir == "se" || dir == "sw" || dir == "nw") {
    curPlayer->usePot(dir, currentFloor);
  } else {
    cout << "Invalid direction" << endl;
  }

}

void attackEnemy(Player* curPlayer, Floor* currentFloor) {
  string dir;
  cin >> dir;

  if (dir == "no" || dir == "ea" || dir == "so" || dir == "we" || dir == "ne" || dir == "se" || dir == "sw" || dir == "nw") {
    curPlayer->attack(dir, currentFloor);
  } else {
    cout << "Invalid direction" << endl;
  }
}

void restart(Player* curPlayer, Floor* currentFloor) {
  delete currentFloor;
  delete curPlayer;
  Merchant::hostile = false;
}

int playerCommand(Player* curPlayer, Floor* currentFloor) {
  string input;
  while (!(curPlayer->getDoneTurn())) {
    printCommand();
    cin >> input;
    if (input == "no" || input == "so" || input == "ea" || input == "we" ||
    input == "ne" || input == "se" || input == "sw" || input == "nw") {//move player

      curPlayer->move(input, currentFloor);
      return 0;
    } else if (input == "u") { // use potion
      usePotion(curPlayer, currentFloor);
      currentFloor->floorAfterTurn(curPlayer);
      return 0;
    } else if (input == "a") { // attack enemy
      attackEnemy(curPlayer, currentFloor);
      currentFloor->floorAfterTurn(curPlayer);
      return 0;
    } else if (input == "r") { // restart game
      restart(curPlayer, currentFloor);
      return 1;
    } else if (input == "q") { // quit
      return 2;
    } else if (input == "f") {
      return 3;
    } else {
      cout << "Please enter valid input" << endl;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  bool exit = false;
  gameOver = false;
  bool stopEnemyMovement = false;
  string input;
  cout << "Welcome to ChamberCrawler3000!" << endl;

  // Start new game
  while (true) {
    gameOver = false;
    exit = false;
    stopEnemyMovement = false;
    auto curPlayer = new Player(createPlayer());
    auto currentFloor = new Floor(MAP_FILE,curPlayer);

    cout << endl;
    currentFloor->floorAfterTurn(curPlayer);
    printInfo(curPlayer);
    cout << "Player has been spawned" << endl;

    while (true) {
      currentFloor->startTurn(curPlayer);
      int command = playerCommand(curPlayer, currentFloor);
      if (command == 0) {
        //do nothing here

      } else if (command == 1) {
        restart(curPlayer, currentFloor);
        break;
      } else if (command == 2) {
        exit = true;
        break;
      } else if (command == 3) {
        stopEnemyMovement = !stopEnemyMovement;
      }
      while (currentFloor->lookForEnemy(curPlayer->row, curPlayer->col) != nullptr) //checks for surounding enemies and makes them attack if possible
      {
        Enemy *attackingEnemy = currentFloor->lookForEnemy(curPlayer->row, curPlayer->col);
        attackingEnemy->attack(curPlayer);
      }
      //Stop enemies from moving
      if (!stopEnemyMovement) {
        currentFloor->enemyMovePhase();

      }


      if (stairReached) {
        currentFloor=nextFloor(currentFloor,curPlayer);
      }


      if (gameOver) {
        cout << action << endl;
        while (true) {
          cout << "Play again? (Y/N)" << endl;
          cin >> input;
          if (input == "N") {
            cout << "Thanks for playing!" << endl;
            exit = true;
            break;
          } else if (input == "Y") {
            break;
          } else {

            cout << "Please enter a valid commmand." << endl;
          }
        }

      }

      currentFloor->floorAfterTurn(curPlayer);

      printInfo(curPlayer);
    }
    if (exit) {
      break;
    }
  }
  return 0;
}
