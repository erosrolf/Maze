#ifndef MAZE_VIEW_FONT_MANAGER_H_
#define MAZE_VIEW_FONT_MANAGER_H_

#include <SFML/Graphics.hpp>

#include "../constants.h"

class FontManager {
 public:
  static void loadFont() {
    if (!kFont.loadFromFile(s21::kFontPath)) {
      exit(1);
    }
  }

  static sf::Font& getFont() { return kFont; }

 private:
  static sf::Font kFont;
};

#endif

// FontManager.cpp