#include "WanderBehavior.h"
#include <cmath>
#include <ctime>

WanderBehavior::WanderBehavior() : rng(std::time(nullptr)) {
  // Create a random number generator
  std::random_device rd;
  std::mt19937 gen(rd());

  // Generate random angle between 0 and 2pi
  std::uniform_real_distribution<float> angleDist(0, 2 * M_PI);
  float randomAngle = angleDist(gen);

  // Give wanderTarget vector a magnitude of wander circle's radius with random
  // direction
  wanderTarget.x = std::cos(randomAngle) * wanderRadius;
  wanderTarget.y = std::sin(randomAngle) * wanderRadius;
}

sf::Vector2f WanderBehavior::calculateSteering(const sf::Vector2f &currentPos,
                                               const sf::Vector2f &currentVel,
                                               float deltaTime) {
  // 1. Add a small random random unit vector times wanderJitter to the wander
  // target's position
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

  // 5. Return the steeringAcceleration
  // we could also scale the vector to a max acceleration constant
  // return normalize(steeringAcceleration) * MAX_ACCELERATION or clamp it as
  // well with return clamp(steeringAcceleration)
  return steeringAcceleration;
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
