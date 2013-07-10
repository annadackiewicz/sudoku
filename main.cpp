#include "Board.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
  string filename;
  cout << "Filename: ";
  cin >> filename;
  ifstream myfile(filename.c_str());
  string line;
  if (myfile.is_open()) {
    while (myfile.good()) {
      getline(myfile, line);
      if (line.length() < 1) {
        continue;
      }
      Board b(line);
      b.printBoard();
      cout << "\n";
      b.setPossibilities();
      b.printBoard();
      cout << "\n\n";
    }
  } else {
    cout << "something wrong with the given file\n";
  }
  return 0;
}
