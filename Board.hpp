#ifndef _SUDOKU_BOARD_HPP_
#define _SUDOKU_BOARD_HPP_

#include "Field.hpp"
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Board {
 public:
  Board();
  Board(string _board);
  ~Board();

  void putNumberOnField(int x, int y, short _num);
  short getNumberFromField(int x, int y);
  void setPossibilities();
  int getNumberOfPossibilities(int x, int y);

  void printBoard();
  void printNumOfPossibilities();

  void printPossibilities();

  bool isTheSameBoard(Board* b);

 private:
  vector<vector<Field> > board;

  int number_of_empty;

  set<short> getPossibilitiesFromSquare(int x, int y);
  set<short> getPossibilitiesFromRow(int x, int y);
  set<short> getPossibilitiesFromColumn(int x, int y);

  void goThroughFieldsQueue(queue<pair<int, int> > fields);
};

#endif // _SUDOKU_BOARD_HPP_
