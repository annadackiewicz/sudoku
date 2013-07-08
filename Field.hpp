#ifndef _SUDOKU_FIELD_HPP_
#define _SUDOKU_FIELD_HPP_

#include <set>

class Field {
 public:
  Field();
  Field(short _num);
  ~Field();

  bool isEmpty();
  short getNum();
  bool putNum(short _num);
  bool isPossible(short _num);

 private:
  short num;
  std::set<short> possible;
};


#endif // _SUDOKU_FIELD_HPP_
