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

  bool test_isTheSameBoard();

  bool test_checkRowForOnlyPossiblePlace();
  bool test_checkColumnForOnlyPossiblePlace();
  bool test_checkSquareForOnlyPossiblePlace();
};

bool Board_test::test() {
  return (test_Board() && test_setPossibilities() && test_isTheSameBoard() &&
          test_checkRowForOnlyPossiblePlace() &&
          test_checkColumnForOnlyPossiblePlace() &&
          test_checkSquareForOnlyPossiblePlace());
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
/*  string _board_1 = " 1  2   3   435   6   71    2  6 73  4  78     95  5  82 1  9    68   6   435   2   9  6 ";
  Board b1 = Board(_board_1);
  b1.printBoard();
  cout << "o\n";
  b1.setPossibilities();
  cout << "a\n";
  if (b1.getNumberOfPossibilities(2, 0) != 0) {
    b1.printNumOfPossibilities();
    //b1.printPossibilities();
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
  }*/
  return true;
}

bool Board_test::test_isTheSameBoard() {
  string _board_1 = " 1  2   3   435   6   71    2  6 73  4  78     95  5  82 1  9    68   6   435   2   9  6 ";
  Board b1 = Board(_board_1);
  b1.setPossibilities();

  string _board_2 = "516427983 824359176 397168452 169735248 782614395 453982617 945276831 671843529 238591764";
  Board b2 = Board(_board_2);
  
  if (!b1.isTheSameBoard(&b2)) {
    return false;
  }
  return true;
}

bool Board_test::test_checkRowForOnlyPossiblePlace() {
  // Board with row that has two fields in two rows that can be filled.
  // (8, 3): 1, (3, 5): 6; the first after setPossibilities, the second after
  // checkRowForOnlyPossiblePlace.
  string board = "     6                        2 3 45 6   6                        1      1       1  6    ";
  Board b = Board(board);
  b.setPossibilities();
  b.checkRowForOnlyPossiblePlace(make_pair<int, int>(3, 8));
  if (b.board[3][8].getNum() != 1) {
    return false;
  }
  b.checkRowForOnlyPossiblePlace(make_pair<int, int>(5, 3));
  if (b.board[5][3].getNum() != 6) {
    return false;
  }
}

// Board with two columns that have fields of which first can be filled by
// setPossibilities and second with checkColumnForOnlyPossiblePlace.
bool Board_test::test_checkColumnForOnlyPossiblePlace() {
  string board = "   1    8    2       8           3      8 6          4  8   6    8       5        89     ";
  Board b = Board(board);
  b.setPossibilities();
  b.checkColumnForOnlyPossiblePlace(make_pair<int, int>(2, 3));
  if (b.board[2][3].getNum() != 6) {
    return false;
  }
  b.checkColumnForOnlyPossiblePlace(make_pair<int, int>(7, 7));
  if (b.board[7][7].getNum() != 8) {
    return false;
  }
  return true;
}

// Board with two squares which can be only filled by checkSquare...
bool Board_test::test_checkSquareForOnlyPossiblePlace() {
  string board = " 941 7       52  49    6 3                9                       9      9               ";
  Board b = Board(board);
  b.setPossibilities();
  b.checkSquareForOnlyPossiblePlace(make_pair<int, int>(2, 4));
  if (b.board[2][4].getNum() != 4) {
    return false;
  }
  b.checkSquareForOnlyPossiblePlace(make_pair<int, int>(8, 0));
  if (b.board[8][0].getNum() != 9) {
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
