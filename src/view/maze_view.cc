#include "maze_view.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstddef>
#include <utility>

#include "ui/label.h"
#include "ui/rectangle.h"

namespace s21 {
MazeView::MazeView(const sf::Vector2f& position, const sf::Vector2f& size,
                   const sf::Color& background_color,
                   const sf::Color& walls_color, Maze* maze)
    : UIRectangle(position, size, background_color),
      walls_color_(walls_color),
      maze_(maze),
      path_state_(PathState::kWaitingStart),
      path_start_(),
      path_end_() {}

void MazeView::draw(sf::RenderTarget& target) const {
  drawFraming(target);
  UIRectangle::draw(target);
  if (maze_->checkIsValidMaze()) {
    drawVerticalWalls(target, horizontalDashLenght(), verticalDashLenght());
    drawHorizontalWalls(target, horizontalDashLenght(), verticalDashLenght());
    switch (path_state_) {
      case PathState::kRenderPath:
        drawSolutionPath(target);
        drawPoint(target, path_end_.row, path_end_.col);
      case PathState::kWaitingEnd:
        drawPoint(target, path_start_.row, path_start_.col);
        break;
      default:
        break;
    }
  }
}

void MazeView::handleEvent(const sf::Event& event,
                           const sf::RenderWindow& window) {
  if (maze_->getPathSolution().empty() &&
      path_state_ == PathState::kRenderPath) {
    path_state_ = PathState::kWaitingStart;
  }
  if (event.type == sf::Event::MouseButtonPressed) {
    sf::Vector2i mouse_pos_i = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos_f = window.mapPixelToCoords(mouse_pos_i);
    if (mazeBoundingBox().contains(mouse_pos_f) && maze_->checkIsValidMaze()) {
      switch (path_state_) {
        case PathState::kWaitingStart:
          path_start_.row = mouseToMazePosition(mouse_pos_i).x;
          path_start_.col = mouseToMazePosition(mouse_pos_i).y;
          std::cout << path_start_.row << ' ' << path_start_.col << '\n';
          path_state_ = PathState::kWaitingEnd;
          break;
        case PathState::kWaitingEnd:
          path_end_.row = mouseToMazePosition(mouse_pos_i).x;
          path_end_.col = mouseToMazePosition(mouse_pos_i).y;
          std::cout << path_end_.row << ' ' << path_end_.col << '\n';
          path_state_ = PathState::kRenderPath;
          maze_->solutionMaze(path_start_, path_end_);
          for (int i = 0; i < maze_->getPathSolution().size(); ++i) {
            std::cout << maze_->getPathSolution()[i].row << '.'
                      << maze_->getPathSolution()[i].col << '\n';
          }
          break;
        case PathState::kRenderPath:
          path_state_ = PathState::kClearPath;
        case PathState::kClearPath:
          path_state_ = PathState::kWaitingStart;
          break;
      }
    }
  }
}  // namespace s21

void MazeView::drawHorizontalWalls(sf::RenderTarget& target, float width,
                                   float height) const {
  static sf::RectangleShape horizontal_dash;
  horizontal_dash.setSize({horizontalDashLenght(), 2});
  horizontal_dash.setFillColor(walls_color_);
  for (int row = 0; row < maze_->getRows(); ++row) {
    for (int col = 0; col < maze_->getCols(); ++col) {
      if (row == 0) {
        horizontal_dash.setPosition(width * col + position_.x - 1,
                                    height * row + position_.y - 1);
        target.draw(horizontal_dash);
      }
      if (maze_->getHorizontal()[row][col]) {
        horizontal_dash.setPosition(width * col + position_.x - 1,
                                    height * row + position_.y + height - 1);
        target.draw(horizontal_dash);
      }
    }
  }
}

void MazeView::drawVerticalWalls(sf::RenderTarget& target, float width,
                                 float height) const {
  static sf::RectangleShape vertical_dash;
  vertical_dash.setSize({2, verticalDashLenght()});
  vertical_dash.setFillColor(walls_color_);
  for (int row = 0; row < maze_->getRows(); ++row) {
    for (int col = 0; col < maze_->getCols(); ++col) {
      if (col == 0) {
        vertical_dash.setPosition(width * col + position_.x - 1,
                                  height * row + position_.y - 1);
        target.draw(vertical_dash);
      }
      if (maze_->getVirtical()[row][col]) {
        vertical_dash.setPosition(width * col + position_.x + width - 1,
                                  height * row + position_.y - 1);
        target.draw(vertical_dash);
      }
    }
  }
}

void MazeView::drawPoint(sf::RenderTarget& target, int row, int col) const {
  sf::CircleShape circle(horizontalDashLenght() / 5);
  circle.setPosition({static_cast<float>(col) * horizontalDashLenght() +
                          horizontalDashLenght() / 2,
                      static_cast<float>(row) * verticalDashLenght() +
                          verticalDashLenght() / 2});
  circle.setFillColor(kBeigeColor);
  target.draw(circle);
}

void MazeView::drawSolutionPath(sf::RenderTarget& target) const {
  float width = horizontalDashLenght();
  float height = verticalDashLenght();
  if (maze_->getPathSolution().empty()) {
    return;
  }
  sf::VertexArray line(sf::LinesStrip, maze_->getPathSolution().size());

  for (size_t i = 0; i < maze_->getPathSolution().size(); ++i) {
    float x = maze_->getPathSolution()[i].col * width + width / 2 + position_.x;
    float y =
        maze_->getPathSolution()[i].row * height + height / 2 + position_.y;
    line[i].position = sf::Vector2f(x, y);
    line[i].color = kBeigeColor;
  }
  target.draw(line);
}

const float MazeView::horizontalDashLenght() const {
  return maze_->getCols() > maze_->getRows() ? size_.x / maze_->getCols()
                                             : size_.x / maze_->getRows();
}

const float MazeView::verticalDashLenght() const {
  return maze_->getCols() > maze_->getRows() ? size_.x / maze_->getCols()
                                             : size_.x / maze_->getRows();
}

float MazeView::mazeAspectRatio() const {
  float aspect_ratio = 1.0;
  if (maze_->checkIsValidMaze()) {
    aspect_ratio =
        (maze_->getRows() < maze_->getCols())
            ? static_cast<float>(maze_->getCols()) / maze_->getRows()
            : static_cast<float>(maze_->getRows()) / maze_->getCols();
  }
  return aspect_ratio;
}

sf::FloatRect MazeView::mazeBoundingBox() const {
  sf::FloatRect bounding_box(position_.x, position_.y, 0, 0);
  if (maze_->getRows() < maze_->getCols()) {
    bounding_box.width = size_.x;
    bounding_box.height = size_.y / mazeAspectRatio();
  } else {
    bounding_box.width = size_.x / mazeAspectRatio();
    bounding_box.height = size_.y;
  }
  return bounding_box;
}

sf::Vector2i MazeView::mouseToMazePosition(
    const sf::Vector2i& mouse_pos_i) const {
  return sf::Vector2i{
      static_cast<int>((mouse_pos_i.y - position_.y) / verticalDashLenght()),
      static_cast<int>((mouse_pos_i.x - position_.x) / horizontalDashLenght())};
}

}  // namespace s21