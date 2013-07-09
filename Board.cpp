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

void Board::setPossibilities() {
  for (short i = 0; i < board_x_size; ++i) {
    for (short j = 0; j < board_y_size; ++j) {
      set<short> poss;
      set<short> possRow = getPossibilitiesFromRow(i, j);
      set<short> possColumn = getPossibilitiesFromColumn(i, j);
      set<short> possSquare = getPossibilitiesFromSquare(i, j);
      for (short s = min_num + 1; s <= max_num; ++s) {
        if (possRow.find(s) != possRow.end() &&
            possColumn.find(s) != possColumn.end() &&
            possSquare.find(s) != possSquare.end()) {
          poss.insert(s);
        }
      }
      board[i][j].putPossibilities(poss);
    }
  }
}

set<short> Board::getPossibilitiesFromRow(int x, int y) {
  set<short> poss;
  if (!board[x][y].isEmpty()) {
    return poss;
  }
  for (short i = min_num+1; i <= max_num; ++i) {
    poss.insert(i);
  }
  for (short i = 0; i < board_x_size; ++i) {
    if (i == x) {
      continue;
    } 
    if (!board[i][y].isEmpty()) {
      poss.erase(board[i][y].getNum());
    }
  }
  return poss;
}

set<short> Board::getPossibilitiesFromRow(int x, int y) {
  set<short> poss;
  for (short i = min_num+1; i <= max_num; ++i) {
    poss.insert(i);
  }
  for (short i = 0; i < board_y_size; ++i) {
    if (i == y) {
      continue;
    } 
    if (!board[x][i].isEmpty()) {
      poss.erase(board[x][i].getNum());
    }
  }
  return poss;
}

set<short> Board::getPossibilitiesFromColumn(int x, int y) {
  set<short> poss;
  for (short i = min_num+1; i <= max_num; ++i) {
    poss.insert(i);
  }
  short sq_x = (short)(x/3) * square_x_size;
  short sq_y = (short)(y/3) * square_y_size;
  for (short i = sq_x; i < sq_x + board_x_size; ++i) {
    for (short j = sq_y; j < sq_y + board_y_size; ++j) {
      if (i == x && j == y) {
        continue;
      } 
      if (!board[i][j].isEmpty()) {
        poss.erase(board[i][y].getNum());
      }
    }
  }
  return poss;
}

