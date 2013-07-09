#include "Field.hpp"

#include "Utils.hpp"

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

void Field::putPossibilities(set<short> _poss) {
  possible = _poss;
}

int Field::getNumberOfPossibilities() {
  return possible.size();
}
