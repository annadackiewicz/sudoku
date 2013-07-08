#ifndef _SUDOKU_FIELD_HPP_
#define _SUDOKU_FIELD_HPP_

class Field {
 public:
  Field();
  Field(short _num);
  ~Field();

  bool isEmpty();
  short getNum();
  bool putNum(short _num);

 private:
  short num;
};


#endif // _SUDOKU_FIELD_HPP_
