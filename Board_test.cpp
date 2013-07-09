#include "Board.hpp"

#include <iostream>
#include "Utils.hpp"

using namespace std;

class Board_test {
 public:
  bool test();
 private:
  bool test_Board();
  bool test_setPossibilities();
};

bool Board_test::test() {
  return (test_Board() && test_setPossibilities());
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

bool Board_test::test_setPossibilities() {
  string _board_1 = " 1  2   3   435   6   71    2  6 73  4  78     95  5  82 1  9    68   6   435   2   9  6 ";
  Board b1 = Board(_board_1);
  b1.printBoard();
  cout << "o\n";
  b1.setPossibilities();
  cout << "a\n";
  if (b1.getNumberOfPossibilities(2, 0) != 0) {
    b1.printNumOfPossibilities();
    b1.printPossibilities();
    cout << "1\n";
    return false;
  }
  cout << "b\n";
  if (b1.getNumberOfPossibilities(3, 0) != 1) {
    cout << "2\n";
    return false;
  }
  cout << "c\n";
  string _board_2 = "1   2 3    4 1  5    3 67 8   86  5   4 3  4 2  5 2   8  19   5 18 6    6  9 2    3 4   7";
  Board b2 = Board(_board_2);
  b2.printBoard();
  cout << "d\n";
  b2.setPossibilities();
  cout << "e\n";
  if (b2.getNumberOfPossibilities(3, 5) != 1) {
    cout << "3\n";
    return false;
  }
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
