#ifndef MAZE_CORE_ABSTRUCT_GIRD_H_
#define MAZE_CORE_ABSTRUCT_GIRD_H_

#include <fstream>
#include <vector>

namespace s21 {
/**
 * @brief class AbstractGrid
 * abstract class
 * reads from file size and matrix
 */

class AbstractGrid {
 public:
  using Matrix = std::vector<std::vector<bool>>;
  virtual ~AbstractGrid() {}
  bool readMatrixFromFile(std::ifstream& file, Matrix& matrix, int rows,
                          int cols);
};
}  // namespace s21
#endif  // MAZE_CORE_ABSTRUCT_GIRD_H_