#pragma once
#include "IMovementBehavior.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

class Ant : public sf::Drawable {
public:
  Ant(unsigned int windowWidth, unsigned int windowHeight);

  // Delete copy operations
  Ant(const Ant &) = delete;
  Ant &operator=(const Ant &) = delete;

  // Enable move operations
  Ant(Ant &&) = default;
  // Ant &operator=(Ant &&) = default;

  void setPosition(const sf::Vector2f &p);
  void setVelocity(const sf::Vector2f &v);
  void setBehavior(std::unique_ptr<IMovementBehavior> newBehavior) {
    movementBehavior = std::move(newBehavior);
  }
  sf::Vector2f getPosition() const { return position; };
  sf::Vector2f getVelocity() const { return velocity; };
  void update(float deltaTime);
  void setFoundFood(bool found);
  bool hasFoundFood() const;

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
  void randomMove(float deltaTime);
  // void moveHome(float deltaTime);

  sf::ConvexShape triangle;
  sf::VertexArray directionLine;

  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f desiredDirection;

  unsigned int windowWidth;
  unsigned int windowHeight;

  bool foundFood{false};

  void updateVisuals();
  void handleBoundaryCollision();

  std::unique_ptr<IMovementBehavior> movementBehavior;

  static constexpr float ANT_SIZE = 6.f;
  static constexpr float MAX_SPEED = 50.f;
  static constexpr float DIRECTION_LINE_LENGTH = 20.f;

  sf::Vector2f clampVector(const sf::Vector2f &v, float maxValue);
  sf::Vector2f normalize(const sf::Vector2f &v);
  float magnitude(sf::Vector2f);
};
