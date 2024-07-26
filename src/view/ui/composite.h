#ifndef MAZE_VIEW_UI_COMPOSITE_H_
#define MAZE_VIEW_UI_COMPOSITE_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "ui_component.h"

namespace s21 {
class UIComposite : public UIComponent {
 public:
  virtual ~UIComposite() {
    for (UIComponent* child : children_) {
      delete child;
    }
  }

  void addComponent(UIComponent* component);
  void removeComponent(UIComponent* component);

  void draw(sf::RenderTarget& target) const override;
  void handleEvent(const sf::Event& event,
                   const sf::RenderWindow& window) override;

  void setPosition(const sf::Vector2f& position);
  const sf::Vector2f& getPosition();

 private:
  std::vector<UIComponent*> children_;
  sf::Vector2f position_;
};
}  // namespace s21

#endif  // MAZE_VIEW_UI_COMPOSITE_H_