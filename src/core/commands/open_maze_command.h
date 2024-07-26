#ifndef MAZE_CORE_COMMANDS_OPENMAZECOMMAND_H_
#define MAZE_CORE_COMMANDS_OPENMAZECOMMAND_H_

#include <iostream>
#include <memory>

#include "../maze.h"
#include "command.h"
#include "tinyfiledialogs.h"

namespace s21 {

class OpenMazeCommand : public Command {
 public:
  OpenMazeCommand(Maze* maze) : maze_(maze) {}

  void execute() override {
    if (maze_) {
      const char* filter_patterns[0];
      const char* file_path = tinyfd_openFileDialog(
          "Open Image", "resources", 0, filter_patterns, "Text files", 0);

      if (file_path) {
        maze_->clear();
        maze_->initFromFile(file_path);
        maze_->printData();
      } else {
        std::cout << "No file was selected or dialog was canceled."
                  << std::endl;
      }
    }
  }

 private:
  Maze* maze_;
};
}  // namespace s21

#endif  // MAZE_CORE_COMMANDS_OPENMAZECOMMAND_H_