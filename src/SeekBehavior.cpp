#include "SeekBehavior.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

SeekBehavior::SeekBehavior(sf::Vector2f &target) : targetPosition(target) {}

sf::Vector2f SeekBehavior::calculateSteering(const sf::Vector2f &currentPos,
                                             const sf::Vector2f &currentVel,
                                             float deltaTime) {
  // Recall from classical physics, if we want to change an object's velocity
  // from v1 to v2 over a time Δt, we would need to give it an acceleration 'a'
  // where:
  // a = k * Δv/Δt = k * (v2-v1)/Δt
  // our Δv = v2-v1 is defined below and helps us get the direction of the
  // steering acceleration:
  sf::Vector2f desiredVelocity =
      normalize(targetPosition - currentPos) * MAX_VELOCITY;
  // we can tune how fast or slow we want the acceleration to change the
  // velocity with the tuning constant k
  // however, let's allow MAX_ACCELERATION to encapsulate the k/Δt term
  // because calculating Δt at every step is an expensive and volatile
  // operation, so it's better we simply have a constant:
  // - Higher MAX_ACCELERATION: sharper turns, faster velocity changes
  // - Lower MAX_ACCELERATION: gradual turns, smoother acceleration/deceleration
  sf::Vector2f steeringAcceleration =
      (desiredVelocity - currentVel) * MAX_ACCELERATION;

  return steeringAcceleration;
}

sf::Vector2f SeekBehavior::normalize(const sf::Vector2f &v) {
  float length = std::sqrt(v.x * v.x + v.y * v.y);
  if (length != 0) {
    return v / length;
  }
  return v;
}
