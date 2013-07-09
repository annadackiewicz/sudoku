#ifndef _SUDOKU_FIELD_HPP_
#define _SUDOKU_FIELD_HPP_

#include <set>

class Field {
 public:
  Field();
  Field(short _num);
  ~Field();

  // Gives information if the field is empty (the number it holds is 0).
  bool isEmpty();
  // Gives the number the field holds. If empty then gives 0.
  short getNum();
  // Putts the given _num into the field.
  //  true if given number was correct and the field hasn't been taken already.
  bool putNum(short _num);
  // Gives information if the given number _num is in set of possible numbers.
  bool isPossible(short _num);
  
  // Changes the set of possible to the given _poss.
  bool putPossibilities(std::set<short> _poss);
  // Returns the number of possible numbers from the set.
  int getNumberOfPossibilities();

  // Prints all the possible numbers from the set.
  void printPossibilities();

  // Removes _num from possibilities.
  //  true if resulted in putting a number into the place.
  bool eraseFromPossibilities(short _num);

 private:
  // The number the field holds.
  short num;
  // Already taken field has empty set of possible numbers.
  std::set<short> possible;
};


#endif // _SUDOKU_FIELD_HPP_
