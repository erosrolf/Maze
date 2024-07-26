#include "abstract_grid.h"

#include <fstream>
#include <iostream>

using namespace s21;

bool AbstractGrid::readMatrixFromFile(std::ifstream& file, Matrix& matrix,
                                      int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int value;
      if (!(file >> value)) {
        std::cerr << "Error reading value from filen";
        return false;
      }
      matrix[i][j] = static_cast<bool>(value);
    }
  }
  return true;
}
