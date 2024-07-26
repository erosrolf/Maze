#include "button.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>

#include "SFML/Window/Event.hpp"
#include "label.h"

namespace s21 {
Button* Button::lastPressed = nullptr;

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,
               const sf::Color& background_color, const std::string& label,
               int font_size, bool is_pressed)
    : Label(position, size, background_color, label, font_size),
      is_pressed_(is_pressed) {}

void Button::handleEvent(const sf::Event& event,
                         const sf::RenderWindow& window) {
  sf::Vector2i mouse_pos_i = sf::Mouse::getPosition(window);
  sf::Vector2f mouse_pos_f = window.mapPixelToCoords(mouse_pos_i);
  if (event.type == sf::Event::MouseButtonPressed) {
    if (isMouseOver(mouse_pos_f)) {
      lastPressed = this;
      is_pressed_ = true;
      if (mouse_press_command_) {
        mouse_press_command_->execute();
      }
    }
  } else if (event.type == sf::Event::MouseButtonReleased) {
    if (is_pressed_ && lastPressed == this) {
      is_pressed_ = false;
      mouse_released_command_->execute();
    }
  }
}

void Button::draw(sf::RenderTarget& target) const {
  if (is_pressed_) {
    drawFraming(target);
  }
  Label::draw(target);
}

bool Button::isMouseOver(const sf::Vector2f& mouse_pos) const {
  sf::FloatRect bounds(position_.x, position_.y, size_.x, size_.y);
  return bounds.contains(mouse_pos);
}

void Button::setMousePressCommand(std::unique_ptr<Command> command) {
  mouse_press_command_ = std::move(command);
}
void Button::setMouseReleasedCommand(std::unique_ptr<Command> command) {
  mouse_released_command_ = std::move(command);
}

}  // namespace s21