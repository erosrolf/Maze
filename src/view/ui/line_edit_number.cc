#include "line_edit_number.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../constants.h"
#include "../font_manager.h"
#include "rectangle.h"

namespace s21 {

LineEditNumber::LineEditNumber(const sf::Vector2f& position,
                               const sf::Vector2f& size,
                               const sf::Color& background_color,
                               const sf::Color& text_color,
                               unsigned int font_size, long max_value)
    : UIRectangle(position, size, background_color),
      text_color_(text_color),
      font_(FontManager::getFont()),
      is_focused_(false),
      max_value_(max_value) {
  text_.setFont(font_);
  text_.setCharacterSize(font_size);
  text_.setFillColor(text_color);
  updateTextPosition();
}

void LineEditNumber::draw(sf::RenderTarget& target) const {
  if (is_focused_) {
    drawFraming(target);
  }
  UIRectangle::draw(target);
  target.draw(text_);
}

void LineEditNumber::handleEvent(const sf::Event& event,
                                 const sf::RenderWindow& window) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mouse_pos(static_cast<float>(event.mouseButton.x),
                             static_cast<float>(event.mouseButton.y));
      is_focused_ = isMouseInside(mouse_pos);
    }
  } else if (event.type == sf::Event::TextEntered && is_focused_) {
    if (event.text.unicode == 8) {
      removeLastSimbol();
    } else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
      setText(getText() + static_cast<char>(event.text.unicode));
    }
    removeFirstZero();
    constraintCheck();
  }
}

void LineEditNumber::setText(const sf::String& text) {
  text_.setString(text);
  updateTextPosition();
}

const sf::String& LineEditNumber::getText() const { return text_.getString(); }

int LineEditNumber::getValue() const {
  if (getText().isEmpty()) {
    return 0;
  } else {
    return std::stoi(static_cast<std::string>(getText()));
  }
}

void LineEditNumber::setMaxValue(long max_value) { max_value_ = max_value; }

void LineEditNumber::updateTextPosition() {
  sf::FloatRect text_bounds = text_.getLocalBounds();
  float y_pos =
      position_.y + (size_.y - text_bounds.height) / 2 - text_bounds.top;
  text_.setPosition(position_.x + 5, y_pos);  // 5 pixels padding from the left
}

void LineEditNumber::removeLastSimbol() {
  sf::String text = getText();
  if (!text.isEmpty()) {
    setText(text.substring(0, text.getSize() - 1));
  }
}

void LineEditNumber::removeFirstZero() {
  sf::String text = getText();
  if (text.getSize() > 1 && (*getText().begin() == '0')) {
    setText(text.substring(1, text.getSize()));
  }
}

void LineEditNumber::constraintCheck() {
  if (getText().isEmpty()) {
    return;
  }
  int number = std::stoi(static_cast<std::string>(getText()));
  if (number > max_value_) {
    removeLastSimbol();
  }
}

}  // namespace s21