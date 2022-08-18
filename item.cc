
#include <iostream>

#include <string>
#include "item.h"
using namespace std;

Item::Item(int row, int col, string type, string name) :
row{row}, col{col}, type{type}, name{name}
{
}

Item::~Item() {
}

int Item::getRow() {
  return row;
}

int Item::getCol() {
  return col;
}

string Item::getType() {
  return type;
}

string Item::getName() {
  return name;
}

void Item::isGone(){}

bool Item::pickAble(){return true;}

void Item::useGold(Player*, Floor*){}

void Item::usePotion(Player*){}

bool Item::getReveal(){return false;}
