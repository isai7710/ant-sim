#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class IMovementBehavior {
public:
  virtual ~IMovementBehavior() = default;
  virtual sf::Vector2f calculateSteering(const sf::Vector2f &currentPos,
                                         const sf::Vector2f &currentVel,
                                         float deltaTime) = 0;
};
