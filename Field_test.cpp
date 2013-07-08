#include "Field.hpp"

#include <iostream>

using namespace std;

class Field_test {
 public:
  bool test();
 private:
  bool test_Field();
  bool test_isEmpty();
  bool test_getNum();
  bool test_putNum();
  bool test_isPossible();
};

bool Field_test::test() {
  return (test_Field() && test_isEmpty() && test_getNum() && test_putNum() &&
      test_isPossible());
}

bool Field_test::test_Field() {
  Field* f0 = new Field();
  short num = 1;
  Field* f1 = new Field(num);
  bool success = true;
  if (f0->getNum() != 0) {
    success = false;
  }
  if (f1->getNum() != num) {
    success = false;
  }
  delete f0;
  delete f1;
  return success;
}

bool Field_test::test_getNum() {
  short num = 3;
  Field f = Field(3);
  if (f.getNum() != num) {
    return false;
  }
  return true;
}

bool Field_test::test_isEmpty() {
  short num = 0;
  Field f = Field(num);
  if (!f.isEmpty()) {
    return false;
  }
  num = 1;
  f = Field(num);
  if (f.isEmpty()) {
    return false;
  }
  return true;
}

bool Field_test::test_putNum() {
  short num = 0;
  Field f = Field(num);
  num = 1;
  if (!f.putNum(num)) {
    return false;
  }
  num = 2;
  if (f.putNum(num)) {
    return false;
  }
  num = 10;
  if (f.putNum(num)) {
    return false;
  }
  return true;
}

bool Field_test::test_isPossible() {
  short num = 0;
  short poss = 1;
  Field f = Field(num);
  if (!f.isPossible(poss)) {
    return false;
  }
  num = 3;
  f = Field(num);
  if (f.isPossible(poss)) {
    return false;
  }
  return true;
}

int main() {
  Field_test t;
  if (!t.test()) {
    cout << "Error!!!\n";
  } else {
    cout << "Everything seems to be working correctly\n";
  }
  return 0;
}
