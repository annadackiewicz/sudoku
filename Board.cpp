#include "Board.hpp"

#include <iostream>
#include <map>
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
  number_of_empty = board_x_size * board_y_size;
}

Board::Board(string _board) {
  number_of_empty = board_x_size * board_y_size;
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
        } else {
          --number_of_empty;
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
    --number_of_empty;
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
  queue<pair<int, int> > fields;
  for (short i = 0; i < board_x_size; ++i) {
    for (short j = 0; j < board_y_size; ++j) {
      if (!board[i][j].isEmpty()){
        continue;
      }
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
      if (poss.size() == 1) {
        --number_of_empty;
        fields.push(make_pair<int, int>(i, j));
      }
    }
  }
  goThroughFieldsQueue(fields);
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

set<short> Board::getPossibilitiesFromColumn(int x, int y) {
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

set<short> Board::getPossibilitiesFromSquare(int x, int y) {
  set<short> poss;
  for (short i = min_num+1; i <= max_num; ++i) {
    poss.insert(i);
  }
  short sq_x = (short)(x/3) * square_x_size;
  short sq_y = (short)(y/3) * square_y_size;
  for (short i = sq_x; i < sq_x + square_x_size; ++i) {
    for (short j = sq_y; j < sq_y + square_y_size; ++j) {
      if (i == x && j == y) {
        continue;
      } 
      if (!board[i][j].isEmpty()) {
        poss.erase(board[i][j].getNum());
      }
    }
  }
  return poss;
}

int Board::getNumberOfPossibilities(int x, int y) {
  return board[x][y].getNumberOfPossibilities();
}

void Board::printBoard() {
  for (int i = 0; i < board_x_size; ++i) {
    for (int j = 0; j < board_y_size; ++j) {
      if (board[i][j].getNum() > min_num) {
        cout << board[i][j].getNum() << " ";
      } else {
        cout << "  ";
      }
    }
    cout << "\n";
  }
}

void Board::printNumOfPossibilities() {
  for (int i = 0; i < board_x_size; ++i) {
    for (int j = 0; j < board_y_size; ++j) {
      if (board[i][j].getNumberOfPossibilities() < 2) {
        cout << "  ";
      } else {
        cout << board[i][j].getNumberOfPossibilities() << " ";
      }
    }
    cout << "\n";
  }
}

void Board::printPossibilities() {
  for (int i = 0; i < board_x_size; ++i) {
    for (int j = 0; j < board_y_size; ++j) {
      if (board[i][j].isEmpty()) {
        cout << " " << i << " " << j << "\n";
        board[i][j].printPossibilities();
      }
    }
  }
}

// TODO: add test for   void Fields::goThroughFieldsQueue(queue<pair<int, int> > fields)
bool Board::goThroughFieldsQueue(queue<pair<int, int> > fields) {
  bool any_new = false;
  while (!fields.empty()) {
    if (eraseFromPossibilitiesInRowColumnAndSquare(&fields, fields.front())) {
      any_new = true;
    }
    fields.pop();
  }
  return any_new;
}

bool Board::eraseFromPossibilitiesInRowColumnAndSquare(
    queue<pair<int, int> >* fields, pair<int, int> f) {
  bool any_new = false;
  short num = board[f.first][f.second].getNum();
  // Check row till this one.
  for (int i = 0; i < board_x_size; ++i) {
    if (i == f.first) {
      continue;
    }
    if (board[i][f.second].eraseFromPossibilities(num)) {
      --number_of_empty;
      fields->push(make_pair<int, int>(i, f.second));
      any_new = true;
    }
  }
  // Check column till this one.
  for (int i = 0; i < board_y_size; ++i) {
    if (i == f.second) {
      continue;
    }
    if (board[f.first][i].eraseFromPossibilities(num)) {
      --number_of_empty;
      fields->push(make_pair<int, int>(f.first, i));
      any_new = true;
    }
  }
  // Check the square till this one..
  int sq_x = (int)(f.first / 3) * square_x_size;
  int sq_y = (int)(f.second / 3) * square_y_size;
  for (int i = sq_x; i < sq_x + square_x_size; ++i) {
    for (int j = sq_y; j < sq_y + square_y_size; ++j) {
      if (i == f.first && j == f.second) {
        continue;
      }
      if (board[i][j].eraseFromPossibilities(num)) {
        --number_of_empty;
        fields->push(make_pair<int, int>(i, j));
        any_new = true;
      }
    }
  }
  return any_new;
}

bool Board::isTheSameBoard(Board* b) {
  for (int i = 0; i < board_x_size; ++i) {
    for (int j = 0; j < board_y_size; ++j) {
      if (board[i][j].getNum() != b->board[i][j].getNum()) {
        return false;
      }
    }
  }
  return true;
}

bool Board::putNumbersIntoOnlyPossiblePlaces() {
  queue<pair<int, int> > fields_to_check;
  for (int i = 0; i < board_x_size; ++i) {
    for (int j = 0; j < board_y_size; ++j) {
      if (board[i][j].isEmpty()) {
        fields_to_check.push(make_pair<int, int>(i, j));
      }
    }
  }
  queue<pair<int, int> > rest_of_fields;
  bool any_new = false;
  bool any_new_this_time = false;
  while (!fields_to_check.empty()) {
    queue<pair<int, int> > newly_filled_fields;
    if (checkRowForOnlyPossiblePlace(fields_to_check.front()) ||
        checkColumnForOnlyPossiblePlace(fields_to_check.front()) ||
        checkSquareForOnlyPossiblePlace(fields_to_check.front())) {
      //--number_of_empty;
      newly_filled_fields.push(fields_to_check.front());
      goThroughFieldsQueue(newly_filled_fields);
      any_new = true;
      any_new_this_time = true;
    } else {
      rest_of_fields.push(fields_to_check.front());
    }
    fields_to_check.pop();
    if (fields_to_check.empty() && any_new_this_time) {
      fields_to_check = rest_of_fields;
      any_new_this_time = false;
    }
  }
  return any_new;
}

bool Board::checkRowForOnlyPossiblePlace(pair<int, int> f_coords) {
  for (int i = min_num + 1; i <= max_num; ++i) {
    bool is_somewhere_else_possible = false;
    if (!board[f_coords.first][f_coords.second].isPossible(i)) {
      continue;
    }
    for (int j = 0; j < board_x_size; ++j) {
      if (j == f_coords.second) {
        continue;
      }
      if (board[f_coords.first][j].isPossible(i)) {
        is_somewhere_else_possible = true;
        break;
      }
    }
    if (!is_somewhere_else_possible) {
      board[f_coords.first][f_coords.second].putNum(i);
      --number_of_empty;
      return true;
    }
  }
  return false;
}

bool Board::checkColumnForOnlyPossiblePlace(pair<int, int> f_coords) {
  for (int i = min_num + 1; i <= max_num; ++i) {
    bool is_somewhere_else_possible = false;
    if (!board[f_coords.first][f_coords.second].isPossible(i)) {
      continue;
    }
    for (int j = 0; j < board_y_size; ++j) {
      if (j == f_coords.first) {
        continue;
      }
      if (board[j][f_coords.second].isPossible(i)) {
        is_somewhere_else_possible = true;
        break;
      }
    }
    if (!is_somewhere_else_possible) {
      board[f_coords.first][f_coords.second].putNum(i);
      --number_of_empty;
      return true;
    }
  }
  return false;
}

bool Board::checkSquareForOnlyPossiblePlace(pair<int, int> f_coords) {
  for (int i = min_num + 1; i <= max_num; ++i) {
    bool is_somewhere_else_possible = false;
    if (!board[f_coords.first][f_coords.second].isPossible(i)) {
      continue;
    }
    int sq_x = (int)(f_coords.first / 3) * square_x_size;
    int sq_y = (int)(f_coords.second / 3) * square_y_size;
    for (int j = sq_x; j < sq_x + square_x_size; ++j) {
      for (int k = sq_y; k <= sq_y + square_y_size; ++k) {
        if (j == f_coords.first) {
          continue;
        }
        if (board[j][k].isPossible(i)) {
          is_somewhere_else_possible = true;
          break;
        }
      }
      if (is_somewhere_else_possible) {
        break;
      }
    }
    if (!is_somewhere_else_possible) {
      board[f_coords.first][f_coords.second].putNum(i);
      --number_of_empty;
      return true;
    }
  }
  return false;
}

bool Board::isSolved() {
  if (number_of_empty > 0) {
    return false;
  }
  return true;
}

bool Board::solve() {
  setPossibilities();
  if (number_of_empty) {
    while (number_of_empty) {
      cout << number_of_empty << "\n";
      if (!putNumbersIntoOnlyPossiblePlaces()) {
        break;
      }
    }
  }
  cout << "end: " << number_of_empty << "\n";
  printBoard();
  if (number_of_empty) {
    return false;
  }
  return true;
}
