#include "Board.hpp"

#include "Utils.hpp"

using namespace std;

Board::Board() {
  for (int i = 0; i < board_x_size; ++i) {
    vector<Field> f;
    board.push_back(f);
    for (int j = 0; j < board_y_size; ++j) {
      board[i].push_back(Field());
    }
  }
}

Board::Board(string _board) {
  bool board_ok = true;
  if (_board.length() !=
      board_x_size * board_y_size + board_y_size - 1) {
    board_ok = false;
  }
  int where_to_read = 0;
  for (int i = 0; i < board_x_size; ++i) {
    vector<Field> f;
    board.push_back(f);
    for (int j = 0; j < board_y_size; ++j, ++where_to_read) {
      short nr = 0;
      if (board_ok) {
        nr = _board[where_to_read] - '0';
        if (nr < 1 || nr > 9) {
          nr = 0;
        }
      }
      Field f = Field(nr);
      board[i].push_back(f);
    }
    ++where_to_read;
  }
}

Board::~Board() {
}

void Board::putNumberOnField(int x, int y, short _num) {
  if (x >= 0 && x < board_x_size && y >= 0 &&
      y < board_y_size) {
    board[x][y].putNum(_num);
  }
}

short Board::getNumberFromField(int x, int y) {
  if (x >= 0 && x < board_x_size && y >= 0 &&
      y < board_y_size) {
    return board[x][y].getNum();
  }
  return -1;
}
