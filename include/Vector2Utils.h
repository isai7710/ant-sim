#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

class Vector2Utils {
public:
  static float squaredMagnitude(const sf::Vector2f &v) {
    return v.x * v.x + v.y * v.y;
  }
  static float magnitude(const sf::Vector2f &v) {
    return std::sqrt(squaredMagnitude(v));
  }
  static sf::Vector2f normalize(const sf::Vector2f &v) {
    return v / magnitude(v);
  }
  static sf::Vector2f clamp(const sf::Vector2f &v, float maxLength) {
    float sqrMag = squaredMagnitude(v);
    if (sqrMag > maxLength * maxLength) {
      float scale = maxLength / std::sqrt(sqrMag);
      return v * scale;
    }
    return v;
  }

  static float squaredDistance(const sf::Vector2f &a, const sf::Vector2f &b) {
    sf::Vector2f diff = b - a;
    return squaredMagnitude(diff);
  }

  static float distance(const sf::Vector2f &a, const sf::Vector2f &b) {
    return magnitude(b - a);
  }
};
