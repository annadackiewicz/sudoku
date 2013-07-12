#ifndef _SUDOKU_BOARD_HPP_
#define _SUDOKU_BOARD_HPP_

#include "Field.hpp"
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Board {
 public:
  // Constructing a completly empty board.
  Board();
  // Constructing a board based on given string.
  // The string has to be filled with digits and spaces, between rows there is
  // an additional space.
  Board(string _board);
  ~Board();

  // Puts a given number on the field if this is possible (if the field hasn't
  // been taken already).
  void putNumberOnField(int x, int y, short _num);
  // Gets the number that is on the fields, if the field is empty then gets 0.
  short getNumberFromField(int x, int y);
  // For all fields on the board the function analyses sets of possibilities of
  // numbers from its' row, column and square and puts the conjunction of those
  // sets.
  void setPossibilities();
  // Gives the number of possibilities on the board's field with given
  // coordinates. 
  int getNumberOfPossibilities(int x, int y);

  // Prints numbers on the board.
  void printBoard();
  // Print the board with number of possibilities instead of the filled numbers.
  void printNumOfPossibilities();

  // Prints all the possibilities for unfilled fields on the board.
  void printPossibilities();

  // Checking if the given board is the same as this one.
  bool isTheSameBoard(Board* b);

  // Check if full board is filled.
  bool isSolved();

  bool solve();

  // Check if the board is a correct -- the numbers in rows columns and squares
  // are used only once.
  bool isCorrect();

 private:
  // The board of sudoku based on Field class.
  vector<vector<Field> > board;

  // Number of still empty fields in the board.
  int number_of_empty;

  // Gives a set of possibilities for a given field based on the row that field
  // is in. Analyses already filled fields in that row and excludes those
  // numbers from that set.
  set<short> getPossibilitiesFromRow(int x, int y);
  // As above but on the fields' column.
  set<short> getPossibilitiesFromColumn(int x, int y);
  // As above but on the fields' square.
  set<short> getPossibilitiesFromSquare(int x, int y);

  // Gets a queue of new fields that have been filled, analyses the fields from
  // its row, column and square deleting the number from the possible numbers of
  // other fields and adding fields with only one possible solution to the end
  // of the queue.
  // Returns:
  //  true if any new field has been filled.
  bool goThroughFieldsQueue(queue<pair<int, int> > fields);

  // Goes through the board, trying to detect the field in row, column or square
  // that can hold a number that other can't (only possible place for this
  // number).
  //
  bool putNumbersIntoOnlyPossiblePlaces();

  // Analyses the f field on the board by taking possibilities from its' row
  // column and square.
  // Returns:
  //  true   if any new field has been filled.
  bool eraseFromPossibilitiesInRowColumnAndSquare(
      queue<pair<int, int> >* fields, pair<int, int> f);

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
