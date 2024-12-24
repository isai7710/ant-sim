#pragma once
#include "IMovementBehavior.h"
#include <SFML/System/Vector2.hpp>
#include <random>

class WanderBehavior : public IMovementBehavior {
public:
  WanderBehavior();

  sf::Vector2f calculateSteering(const sf::Vector2f &currentPos,
                                 const sf::Vector2f &currentVel,
                                 float deltaTime) override;

  void setWanderRadius(float radius) { wanderRadius = radius; };
  void setWanderDistance(float distance) { wanderDistance = distance; }
  void setWanderJitter(float jitter) { wanderJitter = jitter; };

private:
  sf::Vector2f wanderTarget; // Point on the wander circle
  std::mt19937 rng;          // Random number generator

  // Wander behavior parameters
  float wanderRadius = 50.0f;   // Radius of wander circle
  float wanderDistance = 75.0f; // Distance of wander circle from ant
  float wanderJitter = 30.0f;   // Maximum random displacement

  static constexpr float MAX_ACCELERATION = 70.f;
  // Utility functions
  sf::Vector2f getRandomUnitVector();
  sf::Vector2f normalize(const sf::Vector2f &v);
};
