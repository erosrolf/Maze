#include "main_window.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <memory>

#include "../core/commands/command.h"
#include "../core/commands/generate_maze_command.h"
#include "../core/commands/open_maze_command.h"
#include "../core/maze.h"
#include "maze_view.h"
#include "ui/button.h"
#include "ui/composite.h"
#include "ui/line_edit_number.h"
#include "ui/rectangle.h"

namespace s21 {
MainWindow::MainWindow(Maze* maze)
    : need_redraw_(true),
      window_(sf::VideoMode(kWindowWidth, kWindowHeight), "Maze"),
      maze_(maze) {
  MazeView* maze_render =
      new MazeView({10, 10}, {500, 500}, kLightBrownColor, kDarkColor, maze_);
  Button* open_file_btn =
      new Button({550, 190}, {220, 50}, kLightBrownColor, "Open file", 18);
  open_file_btn->setMouseReleasedCommand(
      std::make_unique<OpenMazeCommand>(maze_));
  Button* maze_genarate_btn =
      new Button({550, 260}, {120, 50}, kLightBrownColor, "Generate", 18);

  LineEditNumber* maze_row_line_edit = new LineEditNumber(
      {680, 260}, {40, 50}, kLightBrownColor, kDarkColor, 22, 50);

  LineEditNumber* maze_col_line_edit = new LineEditNumber(
      {730, 260}, {40, 50}, kLightBrownColor, kDarkColor, 22, 50);

  maze_genarate_btn->setMouseReleasedCommand(
      std::make_unique<GenerateMazeCommand>(maze_, maze_row_line_edit,
                                            maze_col_line_edit));

  maze_row_line_edit->setText("10");
  maze_col_line_edit->setText("10");

  root_ui_component_.addComponent(maze_render);
  root_ui_component_.addComponent(open_file_btn);
  root_ui_component_.addComponent(maze_genarate_btn);
  root_ui_component_.addComponent(maze_row_line_edit);
  root_ui_component_.addComponent(maze_col_line_edit);
}

void MainWindow::run() {
  while (window_.isOpen()) {
    sf::Event event;
    bool event_processed = false;

    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      } else if (event.type == sf::Event::MouseButtonPressed ||
                 event.type == sf::Event::MouseButtonReleased ||
                 event.type == sf::Event::KeyPressed) {
        event_processed = true;
      }
      root_ui_component_.handleEvent(event, window_);
    }

    if (event_processed || need_redraw_) {
      drawFrame(event);
    }

    if (window_.hasFocus() && !window_.isOpen()) {
      need_redraw_ = true;
    }
  }
}

void MainWindow::drawFrame(const sf::Event& event) {
  window_.clear(kDarkColor);
  root_ui_component_.draw(window_);
  window_.display();
  need_redraw_ = false;
}

}  // namespace s21