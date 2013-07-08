#include "Field.hpp"

#include "Utils.hpp"

Field::Field() : num (0) {
}

Field::Field(short _num) : num(_num) {
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
      num = _num;  
      return true;
    }
  }
  return false;
}
