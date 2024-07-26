#ifndef MAZE_CORE_COMMANDS_GENERATE_MAZE_COMMAND_H_
#define MAZE_CORE_COMMANDS_GENERATE_MAZE_COMMAND_H_

#include "../../view/ui/line_edit_number.h"
#include "../maze.h"
#include "command.h"

namespace s21 {
class GenerateMazeCommand : public Command {
 public:
  GenerateMazeCommand(Maze* maze, LineEditNumber* row_numbers,
                      LineEditNumber* col_numbers_)
      : maze_(maze), row_numbers_(row_numbers), col_numbers_(col_numbers_) {}
  void execute() override {
    maze_->clear();
    maze_->generateMaze(row_numbers_->getValue(), col_numbers_->getValue());
    std::cout << "rows " << row_numbers_->getValue() << " cols "
              << col_numbers_->getValue() << '\n';
  }

 private:
  Maze* maze_;
  LineEditNumber* row_numbers_;
  LineEditNumber* col_numbers_;
};
}  // namespace s21

#endif  // MAZE_CORE_COMMANDS_GENERATE_MAZE_COMMAND_H_