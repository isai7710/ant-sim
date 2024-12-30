#include "Ant.h"
#include "Vector2Utils.h"
#include "WanderBehavior.h"
#include <random>

Ant::Ant(unsigned int windowWidth, unsigned int windowHeight,
         sf::Vector2f spawnPos)
    : windowWidth(windowWidth), windowHeight(windowHeight),
      directionLine(sf::Lines, 2),
      movementBehavior(std::make_unique<WanderBehavior>()) {

  sf::Color antBrown(139, 69, 19, 255);
  triangle.setPointCount(3);
  triangle.setPoint(0, sf::Vector2f(0, -2 * ANT_SIZE));    // Top vertex
  triangle.setPoint(1, sf::Vector2f(-ANT_SIZE, ANT_SIZE)); // Bottom-left vertex
  triangle.setPoint(2, sf::Vector2f(ANT_SIZE, ANT_SIZE)); // Bottom-right vertex
  triangle.setFillColor(antBrown);

  setPosition(spawnPos);

  directionLine[0].color = sf::Color::Yellow;
  directionLine[1].color = sf::Color::Yellow;

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

void Ant::setPosition(const sf::Vector2f &p) {
  position = p;
  triangle.setPosition(p);
  directionLine[0].position = position;
}

void Ant::setFoundFood(bool found) { foundFood = found; }
bool Ant::hasFoundFood() const { return foundFood; }

void Ant::update(float deltaTime) {
  if (movementBehavior) {
    sf::Vector2f steeringAcceleration =
        movementBehavior->calculateSteering(position, velocity, deltaTime);

    // integrate acceleration to change the ants velocity accordingly
    velocity += steeringAcceleration * deltaTime;

    // Clamp ant's velocity to MAX_SPEED to ensure it doesn't go over
    velocity = Vector2Utils::clamp(velocity, MAX_SPEED);
  }

  // Update position and handle collisions
  position += velocity * deltaTime;
  handleBoundaryCollision();
  updateVisuals();
}

void Ant::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(triangle, states);
  target.draw(directionLine, states);
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

void Ant::updateVisuals() {
  triangle.setPosition(position);

  float currentVelocityMagnitude = Vector2Utils::magnitude(velocity);
  if (currentVelocityMagnitude > 0) {
    sf::Vector2f normalizedVelocityDirection =
        velocity / currentVelocityMagnitude;
    float angle = std::atan2(velocity.y, velocity.x);

    triangle.setRotation(angle * 180 / M_PI + 90);
    directionLine[0].position = position;
    directionLine[1].position =
        position + normalizedVelocityDirection * DIRECTION_LINE_LENGTH;
  }
}
