#ifndef MAZE_VIEW_UI_BUTTON_UIRECTANGLE_H_
#define MAZE_VIEW_UI_BUTTON_UIRECTANGLE_H_

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "../../constants.h"
#include "ui_component.h"

namespace s21 {
class UIRectangle : public UIComponent {
 public:
  UIRectangle(const sf::Vector2f& position = {0, 0},
              const sf::Vector2f& size = {20, 20},
              const sf::Color& background_color = sf::Color::White);

  void draw(sf::RenderTarget& target) const override;

  void handleEvent(const sf::Event& event,
                   const sf::RenderWindow& window) override;

  void setSize(const sf::Vector2f& size);
  const sf::Vector2f& getSize() const;

  void setBackgroundColor(const sf::Color& color);
  const sf::Color& getBackgroundColor() const;

  void setFramingColor(const sf::Color& color);
  const sf::Color& getFramingColor() const;

  bool isMouseInside(sf::Vector2f mouse_pos);

 protected:
  virtual void drawFraming(sf::RenderTarget& target) const;

  sf::Vector2f size_;
  sf::Color background_color_;
  sf::Color framing_color_;
};
}  // namespace s21

#endif  // MAZE_VIEW_UI_BUTTON_UIRECTANGLE_H_