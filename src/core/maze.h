#ifndef MAZE_CORE_MAZE_H_
#define MAZE_CORE_MAZE_H_

#include <iostream>
#include <stack>

#include "abstract_grid.h"

namespace s21 {

enum class Position { Vertical, Horizontal };

/**
 * @brief class Maze
 * parent class - AbstractGrid
 * reading a maze from a file, generating and solving a maze
 */

class Maze : public AbstractGrid {
 public:
  struct Coordinate {
    int row;
    int col;
  };

  void clear();
  int getRows() const noexcept;
  int getCols() const noexcept;
  const Matrix &getHorizontal() const;
  const Matrix &getVirtical() const;
  const std::vector<Coordinate> &getPathSolution() const;
  void printData() const;
  bool checkIsValidMaze() const;

  bool initFromFile(const std::string &filename);
  void generateMaze(int rows, int cols);
  bool solutionMaze(Coordinate A, Coordinate B);

 private:
  Matrix horizontal_;                      ///< horizontal walls
  Matrix vertical_;                        ///< vertical walls
  std::vector<Coordinate> path_solution_;  ///< solution path

  bool checkIsValidCoordinate(Coordinate A, Coordinate B) const;
  bool randomDecision() const;
  void generateVertical(std::vector<int> &numbers, int curr_rows, int cols);
  void generateHorizontal(std::vector<int> &numbers, int curr_rows, int cols);
  bool checkSecondEmptyBorder(std::vector<int> numbers, int rows, int index);
  void unionOfSets(std::vector<int> &numbers, int index_cur, int cols);
  void preprocessingBeforeNextGeneration(std::vector<int> &numbers,
                                         int &iter_nums, int curr_rows);
  bool checkIsUnvisitedNeighbors(Matrix visit_matrix, Coordinate cur_cell,
                                 std::vector<Coordinate> &neighbors);
  bool choiseRandUnvisitedNeighbor(Matrix &visit_matrix, Coordinate &cur_cell,
                                   std::vector<Coordinate> neighbors);
  void writeSolutionMatrix(std::stack<Coordinate> stack_cell);
};

}  // namespace s21
#endif
