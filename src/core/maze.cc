#include "maze.h"

#include <time.h>

#include <fstream>
#include <iostream>
#include <random>
#include <stack>

using namespace s21;

void Maze::clear() {
  vertical_.clear();
  horizontal_.clear();
  path_solution_.clear();
}

int Maze::getRows() const noexcept { return vertical_.size(); }

int Maze::getCols() const noexcept {
  if (vertical_.size() == 0) {
    return 0;
  }
  return vertical_[0].size();
}

const Maze::Matrix &Maze::getHorizontal() const { return horizontal_; }
const Maze::Matrix &Maze::getVirtical() const { return vertical_; }

const std::vector<s21::Maze::Coordinate> &Maze::getPathSolution() const {
  return path_solution_;
}

bool Maze::checkIsValidMaze() const {
  return (vertical_.size() > 0 && vertical_[0].size() > 0) &&
         (horizontal_.size() > 0 && horizontal_[0].size() > 0);
}

bool Maze::randomDecision() const {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 9);
  return dist(gen) % 2 == 1;
}

bool Maze::initFromFile(const std::string &filename) {
  int is_read = true;
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Unable to open filen" << std::endl;
    return false;
  }
  int rows, cols;
  file >> rows >> cols;
  vertical_.resize(rows, std::vector<bool>(cols));
  horizontal_.resize(rows, std::vector<bool>(cols));

  if (!readMatrixFromFile(file, vertical_, rows, cols)) is_read = false;
  if (!readMatrixFromFile(file, horizontal_, rows, cols)) is_read = false;
  if (!is_read) clear();
  return is_read;
}

void Maze::generateMaze(int rows, int cols) {
  std::vector<int> numbers(cols);
  vertical_.resize(rows, std::vector<bool>(cols));
  horizontal_.resize(rows, std::vector<bool>(cols));

  int iter_nums = 0;
  for (; iter_nums < cols; iter_nums++) numbers[iter_nums] = iter_nums;
  for (int i = 0; i < rows; i++) {
    generateVertical(numbers, i, cols);
    generateHorizontal(numbers, i, cols);
    preprocessingBeforeNextGeneration(numbers, iter_nums, i);
  }
}

void Maze::generateVertical(std::vector<int> &numbers, int rows, int cols) {
  for (int j = 0; j < cols; j++) {
    if (randomDecision()) {
      vertical_[rows][j] = true;
    } else {
      if (j < cols - 1) {
        if (numbers[j] == numbers[j + 1])
          vertical_[rows][j] = true;
        else {
          unionOfSets(numbers, j, cols);
        }
      } else
        vertical_[rows][j] = true;
    }
  }
}

void Maze::unionOfSets(std::vector<int> &numbers, int index_cur, int cols) {
  if (index_cur < cols - 1) {
    int num_right = numbers[index_cur + 1];
    for (int index = 0; index < cols; index++) {
      if (numbers[index] == num_right) numbers[index] = numbers[index_cur];
    }
  }
}

void Maze::generateHorizontal(std::vector<int> &numbers, int rows, int cols) {
  for (int j = 0; j < cols; j++) {
    if (randomDecision()) {
      if (checkSecondEmptyBorder(numbers, rows, j)) {
        horizontal_[rows][j] = true;
      }
    }
  }
}

bool Maze::checkSecondEmptyBorder(std::vector<int> numbers, int rows,
                                  int cols_in) {
  bool result_check = false;
  if (cols_in < (int)(horizontal_[0].size() - 1) &&
      numbers[cols_in] == numbers[cols_in + 1]) {
    result_check = true;
  } else {
    int i_back = cols_in - 1;
    while (i_back >= 0 && !result_check &&
           numbers[cols_in] == numbers[i_back]) {
      if (horizontal_[rows][i_back] == false) result_check = true;
      i_back--;
    }
  }
  return result_check;
}

void Maze::preprocessingBeforeNextGeneration(std::vector<int> &numbers,
                                             int &iter_nums, int rows) {
  if (rows < (getRows() - 1)) {
    for (int j = 0; j < getCols(); j++) {
      if (horizontal_[rows][j]) numbers[j] = iter_nums++;
    }
  } else {
    for (int j = 0; j < getCols(); j++) {
      horizontal_[rows][j] = true;
      if (j < getCols() - 1) {
        if (numbers[j] != numbers[j + 1]) vertical_[rows][j] = false;
        unionOfSets(numbers, j, getCols());
      }
    }
  }
}

bool Maze::checkIsValidCoordinate(Coordinate A, Coordinate B) const {
  return (A.row < getRows() && B.row < getRows() && A.col < getCols() &&
          B.col < getCols());
}

bool Maze::solutionMaze(Coordinate A, Coordinate B) {
  bool is_exit = true;
  if (!checkIsValidMaze() || !checkIsValidCoordinate(A, B))
    is_exit = false;
  else {
    Coordinate cur_cell{A.row, A.col};
    Matrix visit_matrix(getRows(), std::vector<bool>(getCols()));
    visit_matrix[cur_cell.row][cur_cell.col] = true;

    std::stack<Coordinate> stack_cell;
    while (is_exit && !(cur_cell.row == B.row && cur_cell.col == B.col)) {
      std::vector<Coordinate> neighbors;
      if (checkIsUnvisitedNeighbors(visit_matrix, cur_cell, neighbors)) {
        stack_cell.push((Coordinate){cur_cell.row, cur_cell.col});
        choiseRandUnvisitedNeighbor(visit_matrix, cur_cell, neighbors);
      } else if (!stack_cell.empty()) {
        cur_cell = stack_cell.top();
        stack_cell.pop();
      } else
        is_exit = false;
    }

    if (is_exit) {
      stack_cell.push((Coordinate){cur_cell.row, cur_cell.col});
      writeSolutionMatrix(stack_cell);
    }
  }
  return is_exit;
}

bool Maze::checkIsUnvisitedNeighbors(Matrix visit_matrix, Coordinate cur_cell,
                                     std::vector<Coordinate> &neighbors) {
  int max_rows = getRows();
  int max_cols = getCols();
  int row = cur_cell.row;
  int col = cur_cell.col;
  if (col < max_cols - 1 && !vertical_[row][col] &&
      !visit_matrix[row][col + 1]) {
    neighbors.push_back((Coordinate){row, col + 1});
  } else if (col > 0 && !vertical_[row][col - 1] &&
             !visit_matrix[row][col - 1]) {
    neighbors.push_back((Coordinate){row, col - 1});
  } else if (row < max_rows - 1 && !horizontal_[row][col] &&
             !visit_matrix[row + 1][col]) {
    neighbors.push_back((Coordinate){row + 1, col});
  } else if (row > 0 && !horizontal_[row - 1][col] &&
             !visit_matrix[row - 1][col]) {
    neighbors.push_back((Coordinate){row - 1, col});
  }
  return !neighbors.empty();
}

bool Maze::choiseRandUnvisitedNeighbor(Matrix &visit_matrix,
                                       Coordinate &cur_cell,
                                       std::vector<Coordinate> neighbors) {
  bool is_set_next_cell = false;
  while (!is_set_next_cell) {
    for (Coordinate cell : neighbors) {
      if (!is_set_next_cell && randomDecision()) {
        is_set_next_cell = true;
        cur_cell.row = cell.row;
        cur_cell.col = cell.col;
      }
    }
  }
  visit_matrix[cur_cell.row][cur_cell.col] = true;
  return is_set_next_cell;
}

void Maze::writeSolutionMatrix(std::stack<Coordinate> stack_cell) {
  int size = 0;
  while (!stack_cell.empty()) {
    Coordinate cur_cell = stack_cell.top();
    path_solution_.resize(++size);
    path_solution_[size - 1].row = cur_cell.row;
    path_solution_[size - 1].col = cur_cell.col;
    stack_cell.pop();
  }
}

void Maze::printData() const {
  if (checkIsValidMaze()) {
    for (int rows = 0; rows < getRows(); rows++) {
      if (rows == 0) {
        for (int i = 0; i < getCols(); i++) std::cout << " _";
        std::cout << '\n';
      }

      for (int cols = 0; cols < getCols(); cols++) {
        if (cols == 0) std::cout << "|";
        if (horizontal_[rows][cols])
          std::cout << "_";
        else
          std::cout << " ";
        if (vertical_[rows][cols])
          std::cout << "|";
        else
          std::cout << " ";
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }
}
