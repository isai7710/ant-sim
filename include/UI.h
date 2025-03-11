#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

struct CircleGenerator {
  static float constexpr pi{3.1415927f}; // pi as a compile-time constant
  float const radius = 0.0f;             // Circle's radius
  uint32_t const quality = 0; // Number of segments (more = smoother circle)
  float const da = 0.0f;      // Angle step (delta angle per segment)

  // Constructor initializes radius, quality, and angle increment
  CircleGenerator(float radius_, uint32_t quality_)
      : radius{radius_}, quality{quality_},
        da{(2.0f * pi) / static_cast<float>(quality)} // Compute angle step
  {}

  // Function to get the i-th point around the circle
  sf::Vector2f getPoint(uint32_t i) const {
    float const angle{da * static_cast<float>(i)}; // Compute angle
    return {radius * sf::Vector2f{std::cos(angle),
                                  std::sin(angle)}}; // Convert to (x, y)
  }
};

struct RoundedRectangleGenerator {
  sf::Vector2f const size;
  sf::Vector2f const
      centers[4]; // center vectors of each of the 4 archs of the rectangle
  uint32_t const arc_quality;
  CircleGenerator const generator;

  // Constructor initializes radius, quality, and angle increment
  RoundedRectangleGenerator(sf::Vector2f size_, float radius, uint32_t quality)
      : size{size_},
        centers{
            {size.x - radius,
             size.y - radius},         // bottom right arch center point
            {radius, size.y - radius}, // bottom left arch center point
            {radius, radius},          // top left arch center point
            {size.x - radius, radius}  // top right arch center point
        },
        // arc_quality determines how many points each arch will have, must be
        // divided evenly by 4 so each arc has equal number of points
        arc_quality{quality / 4}, generator{radius, quality - 4} {}

  // Function to get the i-th point of the perimeter of the rounded rectangle
  sf::Vector2f getPoint(uint32_t i) const {
    uint32_t const corner_idx{i / arc_quality};
    return centers[corner_idx] + generator.getPoint(i - corner_idx);
  }
};

class RoundedButton : public sf::Drawable {
public:
  // Constructor that takes position, size, text, and colors
  RoundedButton(const sf::Vector2f &p, const sf::Vector2f &size, float radius,
                float thickness, uint32_t quality, std::string text);

  // Check if a point (like mouse position) is inside the button
  bool contains(const sf::Vector2f &point) const {
    return vertices.getBounds().contains(point);
  }

private:
  void centerText() {
    // Center the text on the button
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(position.x + (size.x - textBounds.width) / 2.0f,
                           position.y + (size.y - textBounds.height) / 2.0f -
                               textBounds.top);
  }

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    target.draw(vertices, states);
    target.draw(buttonText, states);
  }

  sf::Vector2f position;
  sf::Vector2f size;
  sf::VertexArray vertices;
  sf::Color color{sf::Color(34, 139, 34)};
  sf::Text buttonText;
  sf::Font font;
};
