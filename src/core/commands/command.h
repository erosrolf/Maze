#ifndef MAZE_CORE_COMMANDS_COMMAND_H_
#define MAZE_CORE_COMMANDS_COMMAND_H_

#include <functional>

namespace s21 {
class Command {
 public:
  Command() : action_(nullptr) {}
  Command(std::function<void()> action) : action_(action) {}
  virtual ~Command() = default;

  virtual void execute() {
    if (action_) {
      action_();
    }
  }

 private:
  std::function<void()> action_;
};
}  // namespace s21
#endif  // MAZE_CORE_COMMANDS_COMMAND_H_