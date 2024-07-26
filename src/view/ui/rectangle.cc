#include "rectangle.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "../../constants.h"
#include "ui_component.h"

namespace s21 {
UIRectangle::UIRectangle(const sf::Vector2f& position, const sf::Vector2f& size,
                         const sf::Color& background_color)
    : UIComponent(position),
      size_(size),
      background_color_(background_color),
      framing_color_(kBeigeColor) {}

void UIRectangle::draw(sf::RenderTarget& target) const {
  sf::RectangleShape button_shape(size_);
  button_shape.setFillColor(background_color_);
  button_shape.setPosition(position_);
  target.draw(button_shape);
}

void UIRectangle::handleEvent(const sf::Event& event,
                              const sf::RenderWindow& window) {
  sf::Vector2i mouse_pos_i = sf::Mouse::getPosition(window);
  sf::Vector2f mouse_pos_f = window.mapPixelToCoords(mouse_pos_i);
}

void UIRectangle::setSize(const sf::Vector2f& size) { size_ = size; }

const sf::Vector2f& UIRectangle::getSize() const { return size_; }

void UIRectangle::setBackgroundColor(const sf::Color& color) {
  background_color_ = color;
}
const sf::Color& UIRectangle::getBackgroundColor() const {
  return background_color_;
}

void UIRectangle::setFramingColor(const sf::Color& color) {
  framing_color_ = color;
}
const sf::Color& UIRectangle::getFramingColor() const { return framing_color_; }

bool UIRectangle::isMouseInside(sf::Vector2f mouse_pos) {
  return (mouse_pos.x >= position_.x && mouse_pos.x <= position_.x + size_.x &&
          mouse_pos.y >= position_.y && mouse_pos.y <= position_.y + size_.y);
}

void UIRectangle::drawFraming(sf::RenderTarget& target) const {
  UIRectangle frame(getPosition() - sf::Vector2f{2, 2},
                    getSize() + sf::Vector2f{4, 4}, framing_color_);
  frame.draw(target);
}

}  // namespace s21