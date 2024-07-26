#pragma once
#include <SFML/Graphics/Color.hpp>
#include <string_view>

namespace s21 {

const char* const kFontPath = "../fonts/FiraCode-Medium.ttf";
constexpr int kWindowWidth = 800;
constexpr int kWindowHeight = 520;
constexpr int kDefaultButtonWidth = 100;
constexpr int kDefaultButtonHeight = 50;
const sf::Color kDarkColor{36, 32, 33};
const sf::Color kDarkBrownColor{147, 115, 45};
const sf::Color kLightBrownColor{203, 174, 112};
const sf::Color kBeigeColor{238, 230, 207};

}  // namespace s21