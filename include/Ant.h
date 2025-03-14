#pragma once
#include "IMovementBehavior.h"
#include <SFML/Graphics.hpp>
#include <memory>

class World;

class Ant : public sf::Drawable {
public:
  Ant(unsigned int windowWidth, unsigned int windowHeight,
      sf::Vector2f spawnPos);

  // Delete copy operations
  Ant(const Ant &) = delete;
  Ant &operator=(const Ant &) = delete;

  // Enable move operations
  Ant(Ant &&) = default;
  Ant &operator=(Ant &&) = default;

  void setPosition(const sf::Vector2f &p) {
    position = p;
    triangle.setPosition(p);
  };
  void setVelocity(const sf::Vector2f &v) { velocity = v; };
  void setBehavior(std::unique_ptr<IMovementBehavior> newBehavior) {
    movementBehavior = std::move(newBehavior);
  }
  void setFoundFood(bool found) { foundFood = found; }

  sf::Vector2f getPosition() const { return position; };
  sf::Vector2f getVelocity() const { return velocity; };
  bool getFoundFood() const { return foundFood; };

  void update(World &world, float deltaTime);
  void depositPheromone(World &world);

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  sf::ConvexShape triangle;

  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Clock clock;

  unsigned int windowWidth;
  unsigned int windowHeight;

  bool foundFood{false};

  void handleBoundaryCollision();

  std::unique_ptr<IMovementBehavior> movementBehavior;

  static constexpr float ANT_SIZE = 6.f;
  static constexpr float MAX_SPEED = 50.f;
  static constexpr float DIRECTION_LINE_LENGTH = 20.f;
  static constexpr float DEPOSIT_INTERVAL = 0.1f;
};
