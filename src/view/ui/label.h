#ifndef MAZE_VIEW_UI_LABEL_H_
#define MAZE_VIEW_UI_LABEL_H_

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

#include "../../core/commands/command.h"
#include "rectangle.h"
#include "ui_component.h"

namespace s21 {
class Label : public UIRectangle {
 public:
  Label(const sf::Vector2f& position = {0, 0},
        const sf::Vector2f& size = {100, 40},
        const sf::Color& background_color = sf::Color::White,
        const std::string& label = "", int font_size = 12);

  void draw(sf::RenderTarget& target) const override;

  void handleEvent(const sf::Event& event,
                   const sf::RenderWindow& window) override;

  void setLable(const std::string& label);
  const std::string& getLabel() const;

 protected:
  std::string label_;
  sf::Font label_font_;
  int font_size_;
};
}  // namespace s21

#endif  // MAZE_VIEW_UI_LABEL_H_