#include "Field.hpp"

#include <iostream>
#include "Utils.hpp"

using namespace std;

Field::Field() : num (0) {
  for (short i = min_num + 1; i <= max_num; ++i) {
    possible.insert(i);
  }
}

Field::Field(short _num) {
  if (_num >= 1 && _num <= 9) {
    num = _num;
  } else {
    for (short i = min_num + 1; i <= max_num; ++i) {
      possible.insert(i);
    }
    num = 0;
  }
}

Field::~Field() {
}

bool Field::isEmpty() {
  if (!num) {
    return true;
  }
  return false;
}

short Field::getNum() {
  return num;
}

bool Field::putNum(short _num) {
  if (!num) {
    if (_num >= min_num && _num <= max_num) {
      if (_num > 0) {
        possible.clear();
      }
      num = _num;  
      return true;
    }
  }
  return false;
}

bool Field::isPossible(short _num) {
  if (possible.find(_num) != possible.end()) {
    return true;
  }
  return false;
}

bool Field::putPossibilities(set<short> _poss) {
  possible = _poss;
  if (possible.size() < 1) {
    return false;
  }
  if (possible.size() == 1) {
    return putNum((*possible.begin()));
  }
  return true;
}

int Field::getNumberOfPossibilities() {
  return possible.size();
}

void Field::printPossibilities() {
  cout << "   ";
  for (set<short>::iterator it = possible.begin(); it != possible.end(); ++it) {
    cout << *(it) << " ";
  }
  cout << "\n";
}

// TODO: add test for   bool Field::eraseFromPossibilities(short _num)
bool Field::eraseFromPossibilities(short _num) {
  int pre_size = possible.size();
  possible.erase(_num);
  if (possible.size() == 1 && pre_size == 2) {
    num = *(possible.begin());
    possible.clear();
    return true;
  }
  return false;
}
