#include "Ant.h"
#include <random>

Ant::Ant(unsigned int windowWidth, unsigned int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight) {
  shape.setSize(sf::Vector2f(5.f, 5.f));
  shape.setFillColor(sf::Color::Black);

  // Initialize ant with a random direction
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
  desiredDirection = sf::Vector2f(dis(gen), dis(gen));
  float length = std::sqrt(desiredDirection.x * desiredDirection.x +
                           desiredDirection.y * desiredDirection.y);
  desiredDirection /= length;
}

void Ant::update(float deltaTime) { randomMove(deltaTime); }

void Ant::setPosition(const sf::Vector2f &pos) {
  position = sf::Vector2f(pos.x, pos.y);
  shape.setPosition(pos);
}

sf::Vector2f Ant::getPosition() const {
  return sf::Vector2f(position.x, position.y);
}

void Ant::setFoundFood(bool found) { foundFood = found; }

bool Ant::hasFoundFood() const { return foundFood; }

void Ant::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(shape, states);
}

void Ant::randomMove(float deltaTime) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

  float randomDirX = dis(gen);
  float randomDirY = dis(gen);

  sf::Vector2f randomDir(dis(gen), dis(gen));
  desiredDirection +=
      sf::Vector2f(randomDir.x * wanderStrength, randomDir.y * wanderStrength);
  // normalize
  float length = std::sqrt(desiredDirection.x * desiredDirection.x +
                           desiredDirection.y * desiredDirection.y);
  desiredDirection /= length;

  sf::Vector2f desiredVelocity = desiredDirection * maxSpeed;
  sf::Vector2f desiredSteeringForce = desiredVelocity - velocity;
  sf::Vector2f acceleration = clampVector(desiredSteeringForce, steerStrength);

  velocity = clampVector(velocity + acceleration * deltaTime, maxSpeed);
  position += velocity * deltaTime;

  // Boundary checking with window dimensions
  if (position.x > windowWidth || position.x < 0) {
    velocity.x *= -1;
    position.x = std::max(0.0f, std::min((float)windowWidth, position.x));
    desiredDirection.x *= -1; // Change desired direction too
  }
  if (position.y > windowHeight || position.y < 0) {
    velocity.y *= -1;
    position.y = std::max(0.0f, std::min((float)windowHeight, position.y));
    desiredDirection.y *= -1; // Change desired direction too
  }

  shape.setPosition(position);
}

/*
void Ant::moveHome(float deltaTime) {
  Vector2D homeDirection(-position.x, -position.y);
  homeDirection.normalize();

  Vector2D desiredVelocity = homeDirection * maxSpeed;
  Vector2D desiredSteeringForce = desiredVelocity - velocity;
  Vector2D acceleration = clampVector(desiredSteeringForce, steerStrength);

  velocity = clampVector(velocity + acceleration * deltaTime, maxSpeed);
  position = Vector2D(position.x + velocity.x * deltaTime,
                      position.y + velocity.y * deltaTime);
}
*/

sf::Vector2f Ant::clampVector(const sf::Vector2f &v, float maxValue) {
  float length = std::sqrt(v.x * v.x + v.y * v.y);
  if (length > maxValue) {
    return v * (maxValue / length);
  }
  return v;
}
