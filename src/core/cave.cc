#include "cave.h"

#include <fstream>

#include "gtest/gtest.h"

using namespace s21;

Cave::Matrix Cave::getData() const { return data_; }

bool Cave::initFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Unable to open filen";
    return false;
  }
  int rows, cols;
  file >> rows >> cols;
  data_.resize(rows, std::vector<bool>(cols));
  return readMatrixFromFile(file, data_, rows, cols);
}

int Cave::getRows() const noexcept { return data_.size(); }

int Cave::getCols() const noexcept {
  if (data_.size() == 0) {
    return 0;
  }
  return data_[0].size();
}

int Cave::numberOfNeighbors(int row, int col, const Matrix& matrix) {
  static const int directions[8][2] = {
      {-1, -1}, {-1, 0}, {-1, 1},  /// < top row
      {0, -1},  {0, 1},            /// < mid row
      {1, -1},  {1, 0},  {1, 1}    /// < bot row
  };
  int count = 0;
  for (const auto& dir :
       directions) {  /// < checks for a neighbor outside the matrix
    if (row + dir[0] < 0 || row + dir[0] >= static_cast<int>(matrix.size()) ||
        col + dir[1] < 0 || col + dir[1] >= static_cast<int>(matrix.size())) {
      ++count;
    } else if (matrix[row + dir[0]][col + dir[1]] ==
               true) {  /// < checks for a living neighbor inside the matrix
      ++count;
    }
  }
  return count;
}

Cave::GenerationResult Cave::stepOfGeneration(int birth_limit,
                                              int death_limit) {
  if (birth_limit < 0 || birth_limit > 7 || death_limit < 0 ||
      death_limit > 7) {
    return GenerationResult::kInvalidParams;
  }

  bool mutation = false;
  Matrix new_cave = data_;
  for (int row = 0; row < getRows(); ++row) {
    for (int col = 0; col < getCols(); ++col) {
      int count = numberOfNeighbors(row, col, data_);
      if (count > birth_limit) {
        new_cave[row][col] = true;
        mutation = true;
      } else if (count < death_limit) {
        new_cave[row][col] = false;
        mutation = true;
      }
    }
  }
  return mutation ? GenerationResult::kMutation : GenerationResult::kStable;
}

// int Cave::cycleOfGeneration(int birth_limit, int death_limit) {
//   int mutation_count = 0;
//   while (stepOfGeneration(birth_limit, death_limit) ==
//          GenerationResult::kMutation) {
//     ++mutation_count;
//   }
//   return mutation_count;
// }