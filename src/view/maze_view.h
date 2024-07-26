#ifndef MAZE_VIEW_MAZEVIEW_H_
#define MAZE_VIEW_MAZEVIEW_H_

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "../core/commands/command.h"
#include "../core/maze.h"
#include "ui/rectangle.h"
#include "ui/ui_component.h"

namespace s21 {
class MazeView : public UIRectangle {
 public:
  enum class PathState {
    kWaitingStart = 0,
    kWaitingEnd,
    kRenderPath,
    kClearPath,
  };

  MazeView(const sf::Vector2f& position = {0, 0},
           const sf::Vector2f& size = {500, 500},
           const sf::Color& background_color = sf::Color::White,
           const sf::Color& walls_color = sf::Color::Black,
           Maze* maze = nullptr);

  void draw(sf::RenderTarget& target) const override;
  void handleEvent(const sf::Event& event,
                   const sf::RenderWindow& window) override;
  const float horizontalDashLenght() const;
  const float verticalDashLenght() const;

 private:
  void drawHorizontalWalls(sf::RenderTarget& target, float width,
                           float height) const;
  void drawVerticalWalls(sf::RenderTarget& target, float width,
                         float height) const;
  void drawSolutionPath(sf::RenderTarget& target) const;
  void drawPoint(sf::RenderTarget& target, int row, int col) const;
  sf::FloatRect mazeBoundingBox() const;
  float mazeAspectRatio() const;
  sf::Vector2i mouseToMazePosition(const sf::Vector2i& mouse_pos_i) const;

  sf::Color walls_color_;
  Maze* maze_;
  PathState path_state_;
  Maze::Coordinate path_start_;
  Maze::Coordinate path_end_;
};
}  // namespace s21

#endif  // MAZE_VIEW_MAZEVIEW_H_