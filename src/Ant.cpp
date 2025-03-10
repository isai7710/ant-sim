#include "Ant.h"
#include "Pheromone.h"
#include "Vector2Utils.h"
#include "WanderBehavior.h"
#include "World.h"
#include <random>

Ant::Ant(unsigned int windowWidth, unsigned int windowHeight,
         sf::Vector2f spawnPos)
    : windowWidth(windowWidth), windowHeight(windowHeight),
      movementBehavior(std::make_unique<WanderBehavior>()) {

  sf::Color antBrown(139, 69, 19, 255);
  triangle.setPointCount(3);
  triangle.setPoint(0, sf::Vector2f(0, -2 * ANT_SIZE));    // Top vertex
  triangle.setPoint(1, sf::Vector2f(-ANT_SIZE, ANT_SIZE)); // Bottom-left vertex
  triangle.setPoint(2, sf::Vector2f(ANT_SIZE, ANT_SIZE)); // Bottom-right vertex
  triangle.setFillColor(antBrown);

  setPosition(spawnPos);

  // Create a random number generator
  std::random_device rd;
  std::mt19937 gen(rd());

  // Generate random angle between 0 and 2π
  std::uniform_real_distribution<float> angleDist(0, 2 * M_PI);
  float randomAngle = angleDist(gen);

  // Generate a random speed between 50-100% of MAX_SPEED
  std::uniform_real_distribution<float> speedDist(0.5f * MAX_SPEED, MAX_SPEED);
  float randomSpeed = speedDist(gen);

  // Set the initial velocity of the ant using the random angle and speed
  velocity.x = std::cos(randomAngle) * randomSpeed;
  velocity.y = std::sin(randomAngle) * randomSpeed;
}

void Ant::update(World &world, float deltaTime) {
  if (movementBehavior) {
    sf::Vector2f steeringAcceleration =
        movementBehavior->calculateSteering(position, velocity, deltaTime);

    // integrate acceleration to change the ants velocity accordingly
    velocity += steeringAcceleration * deltaTime;

    // Clamp ant's velocity to MAX_SPEED to ensure it doesn't go over
    velocity = Vector2Utils::clamp(velocity, MAX_SPEED);
  }

  // Update position member and handle collisions
  position += velocity * deltaTime;
  handleBoundaryCollision();

  // Update shape position and orientation
  triangle.setPosition(position);
  float angle = std::atan2(velocity.y, velocity.x);
  triangle.setRotation(angle * 180 / M_PI + 90);

  // deposit pheromone in this new position
  depositPheromone(world);
}

void Ant::depositPheromone(World &world) {
  if (clock.getElapsedTime().asSeconds() > DEPOSIT_INTERVAL) {
    PheromoneType type = movementBehavior->getPheromoneType();
    world.addPheromone(Pheromone(position, type));
    clock.restart();
  }
}

void Ant::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(triangle, states);
}

void Ant::handleBoundaryCollision() {
  if (position.x > windowWidth || position.x < 0) {
    velocity.x *= -1;
    position.x = std::clamp(position.x, 0.f, static_cast<float>(windowWidth));
  }
  if (position.y > windowHeight || position.y < 0) {
    velocity.y *= -1;
    position.y = std::clamp(position.y, 0.f, static_cast<float>(windowHeight));
  }
}
