#ifndef MAZE_CORE_CAVE_H_
#define MAZE_CORE_CAVE_H_

#include <iostream>

#include "abstract_grid.h"

namespace s21 {

/**
 * @brief class Cave
 * parent class - AbstractGrid
 * reading a cave from a file and write in data_, generating a cave
 */

class Cave : public AbstractGrid {
 public:
  enum class GenerationResult { kStable, kMutation, kInvalidParams };
  using Matrix = std::vector<std::vector<bool>>;

  Cave() {}
  Cave(int rows, int cols) : data_(rows, std::vector<bool>(cols, false)) {}
  Cave(Matrix& other_data) : data_(other_data) {}
  ~Cave() {}

  Matrix getData() const;
  int getRows() const noexcept;
  int getCols() const noexcept;
  bool initFromFile(const std::string& filename);
  int numberOfNeighbors(int row, int col, const Matrix& matrix);
  GenerationResult stepOfGeneration(int birth_limit, int death_limit);
  // int cycleOfGeneration(int birth_limit, int death_limit);

 private:
  Matrix data_;  ///< cave
};
}  // namespace s21

#endif  // MAZE_CORE_CAVE_H_