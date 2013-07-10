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

  // Gets a queue of new fields that have been filled, analyses the fields from
  // its row, column and square deleting the number from the possible numbers of
  // other fields and adding fields with only one possible solution to the end
  // of the queue.
  void goThroughFieldsQueue(queue<pair<int, int> > fields);

  // Goes through the board, trying to detect the field in row, column or square
  // that can hold a number that other can't (only possible place for this
  // number).
  queue<pair<int, int> > putNumbersIntoOnlyPossiblePlaces();

  // Check if there exist a number in this field that can't be put anywhere
  // beside this place in the whole row. 
  bool checkRowForOnlyPossiblePlace(pair<int, int> f_coord);
  // As above but in column.
  bool checkColumnForOnlyPossiblePlace(pair<int, int> f_coord);
  // As above but in square.
  bool checkSquareForOnlyPossiblePlace(pair<int, int> f_coord);

  friend class Board_test;
};

#endif // _SUDOKU_BOARD_HPP_
