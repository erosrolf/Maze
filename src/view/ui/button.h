#ifndef MAZE_VIEW_UI_BUTTON_H_
#define MAZE_VIEW_UI_BUTTON_H_

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

#include "../../constants.h"
#include "../../core/commands/command.h"
#include "label.h"
#include "ui_component.h"

namespace s21 {
class Button : public Label {
 public:
  Button(const sf::Vector2f& position = {0, 0},
         const sf::Vector2f& size = {kDefaultButtonWidth, kDefaultButtonHeight},
         const sf::Color& background_color = sf::Color::White,
         const std::string& label = "Button", int font_size = 12,
         bool is_pressed = false);

  void handleEvent(const sf::Event& event,
                   const sf::RenderWindow& window) override;
  void draw(sf::RenderTarget& target) const override;
  void setMousePressCommand(std::unique_ptr<Command> command);
  void setMouseReleasedCommand(std::unique_ptr<Command> command);

  static Button* lastPressed;

 protected:
  bool isMouseOver(const sf::Vector2f& mouse_pos) const;

 private:
  std::unique_ptr<Command> mouse_press_command_;
  std::unique_ptr<Command> mouse_released_command_;
  bool is_pressed_;
};
}  // namespace s21

#endif  // MAZE_VIEW_UI_BUTTON_H_