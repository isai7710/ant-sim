#include "UI.h"

RoundedButton::RoundedButton(const sf::Vector2f &p, const sf::Vector2f &size,
                             float radius, float thickness, uint32_t quality,
                             std::string text)
    : position{p}, size{size}, vertices(sf::TriangleStrip, 2 * quality + 2) {
  RoundedRectangleGenerator const outer_generator{size, radius, quality};
  sf::Vector2f inner_offset{thickness, thickness};
  sf::Vector2f inner_size = size - 2.0f * inner_offset;
  RoundedRectangleGenerator const inner_generator{inner_size,
                                                  radius - thickness, quality};

  for (uint32_t i = 0; i < quality; i++) {
    vertices[2 * i + 0].position =
        p + inner_offset + inner_generator.getPoint(i);
    vertices[2 * i + 0].color = color;
    vertices[2 * i + 1].position = p + outer_generator.getPoint(i);
    vertices[2 * i + 1].color = color;
  }

  vertices[2 * quality + 0].position =
      p + inner_offset + inner_generator.getPoint(0);
  vertices[2 * quality + 0].color = color;
  vertices[2 * quality + 1].position = p + outer_generator.getPoint(0);
  vertices[2 * quality + 1].color = color;

  if (!font.loadFromFile("../assets/font/rainyhearts.ttf")) {
    throw std::runtime_error("Failed to load font");
  }

  buttonText.setFont(font);
  buttonText.setString(text);
  buttonText.setCharacterSize(20);
  buttonText.setFillColor(sf::Color(34, 139, 34));

  // Center text on button
  centerText();
};
