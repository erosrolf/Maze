#include "composite.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>

#include "ui_component.h"

namespace s21 {

void UIComposite::addComponent(UIComponent* component) {
  children_.push_back(component);
}

void UIComposite::removeComponent(UIComponent* component) {
  children_.erase(std::remove(children_.begin(), children_.end(), component),
                  children_.end());
}

void UIComposite::draw(sf::RenderTarget& target) const {
  for (UIComponent* child : children_) {
    child->draw(target);
  }
}

void UIComposite::handleEvent(const sf::Event& event,
                              const sf::RenderWindow& window) {
  for (UIComponent* child : children_) {
    child->handleEvent(event, window);
  }
}

void UIComposite::setPosition(const sf::Vector2f& position) {
  position_ = position;
}

const sf::Vector2f& UIComposite::getPosition() { return position_; }

}  // namespace s21