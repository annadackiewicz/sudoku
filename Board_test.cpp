#include "Board.hpp"

#include <iostream>
#include "Utils.hpp"

using namespace std;

class Board_test {
 public:
  bool test();
 private:
  bool test_Board();
};

bool Board_test::test() {
  return (test_Board());
}

bool Board_test::test_Board() {
  Board* f0 = new Board();
  for (int i = 0; i < board_x_size; ++i) {
    for (int j = 0; j < board_y_size; ++j) {
      if (f0->getNumberFromField(i, j) != 0) {
        delete f0;
        return false;
      }
    }
  }
  delete f0;
  string _board_correct = "123456789 234567891 345678912 456789123 567891234 678912345 789123456 891234567 912345678";
  Board* f1 = new Board(_board_correct);
  for (int i = 0; i < board_x_size; ++i) {
    for (int j = 0; j < board_y_size; ++j) {
      if (f1->getNumberFromField(i, j) != ((i + j) % 9) + 1) {
        delete f1;
        return false;
      }
    }
  }
  delete f1;
  string _board_error = "123456789 12345689 123456789 123456789 12345689 123456789 123456789 123456789 123456789 ";
  Board* f2 = new Board(_board_error);
  for (int i = 0; i < board_x_size; ++i) {
    for (int j = 0; j < board_y_size; ++j) {
      if (f2->getNumberFromField(i, j) != 0) {
        delete f2;
        return false;
      }
    }
  }
  delete f2;
  return true;
}

int main() {
  Board_test t;
  if (!t.test()) {
    cout << "Error!!!\n";
  } else {
    cout << "Everything seems to be working correctly\n";
  }
  return 0;
}
