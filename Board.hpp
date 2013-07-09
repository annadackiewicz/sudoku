#ifndef _SUDOKU_BOARD_HPP_
#define _SUDOKU_BOARD_HPP_

#include "Field.hpp"
#include <string>
#include <vector>

//class Field;

using namespace std;

class Board {
 public:
  Board();
  Board(string _board);
  ~Board();

  void putNumberOnField(int x, int y, short _num);
  short getNumberFromField(int x, int y);

  void setPossibilities();
  set<short> getPossibilitiesFromSquare(int x, int y);
  set<short> getPossibilitiesFromRow(int x, int y);
  set<short> getPossibilitiesFromColumn(int x, int y);

 private:
  vector<vector<Field> > board;
};

#endif // _SUDOKU_BOARD_HPP_
