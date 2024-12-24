#include "WanderBehavior.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <ctime>

WanderBehavior::WanderBehavior() : rng(std::time(nullptr)) {
  wanderTarget = sf::Vector2f(wanderRadius, 0);
}

sf::Vector2f WanderBehavior::calculateSteering(const sf::Vector2f &currentPos,
                                               const sf::Vector2f &currentVel,
                                               float deltaTime) {
  // 1. Add a small random random unit vector times wanderJitter to the target's
  // position
  wanderTarget += getRandomUnitVector() * wanderJitter;

  // 2. Reproject this new target onto the wander circle
  wanderTarget = normalize(wanderTarget) * wanderRadius;

  // 3. Calculate ant's current and normalized direction vector and multiply by
  // wanderDistance to get the vector to the center of the wander circle
  sf::Vector2f currentDirection = normalize(currentVel);
  sf::Vector2f antToWanderCircleCenter = currentDirection * wanderDistance;

  // 4. Steering acceleration (force) according to Craig Reynold's wander
  // steering algorithm is then just:
  sf::Vector2f steeringAcceleration = antToWanderCircleCenter + wanderTarget;

  // 5. Return the scaled steeringAcceleration
  return normalize(steeringAcceleration) * MAX_ACCELERATION;
}

sf::Vector2f WanderBehavior::getRandomUnitVector() {
  // Generate random direction vector
  std::uniform_real_distribution<float> angleDist(0, 2 * M_PI);
  return sf::Vector2f(std::cos(angleDist(rng)), std::sin(angleDist(rng)));
}

sf::Vector2f WanderBehavior::normalize(const sf::Vector2f &v) {
  float length = std::sqrt(v.x * v.x + v.y * v.y);
  if (length != 0) {
    return v / length;
  }
  return v;
}
