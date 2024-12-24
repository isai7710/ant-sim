#include "World.h"
#include "SeekBehavior.h"
#include "WanderBehavior.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>

World::World(unsigned int width, unsigned int height)
    : width(width), height(height) {
  ants.reserve(NUM_ANTS);
  setupFood();
  setupHome();
  setupAnts();
}

void World::update(float deltaTime) {
  for (auto &ant : ants) {
    ant.update(deltaTime);
  }
  if (hasTarget) {
    for (auto &ant : ants) {
      sf::Vector2f error = targetPosition - ant.getPosition();
      if (std::sqrt(error.x * error.x + error.y * error.y) < 2.0f) {
        clearTarget();
      }
    }
  }
}

void World::draw(sf::RenderWindow &window) {
  window.draw(home);
  for (const auto &food : foodItems) {
    window.draw(food);
  }
  for (const auto &ant : ants) {
    window.draw(ant);
  }
  if (hasTarget) {
    window.draw(target);
  }
}

void World::updateTarget(sf::Vector2f position) {
  if (targetPosition == position) {
    clearTarget();
    return;
  } else {
    targetPosition = position;
    target.setPosition(targetPosition.x - target.getRadius(),
                       targetPosition.y - target.getRadius());
    target.setFillColor(sf::Color::Green);
    hasTarget = true;
  }
  for (auto &ant : ants) {
    auto seekBehavior = std::make_unique<SeekBehavior>(targetPosition);
    ant.setBehavior(std::move(seekBehavior));
  }
}

sf::Vector2f World::getTargetPosition() { return targetPosition; }

void World::setupAnts() {
  for (std::size_t i = 0; i < NUM_ANTS; i++) {
    Ant ant(width, height);
    ant.setPosition(sf::Vector2f(width / 2.f, height / 2.f));
    auto wanderBehavior = std::make_unique<WanderBehavior>();
    ant.setBehavior(std::move(wanderBehavior));
    ants.push_back(std::move(ant));
  }
}

void World::setupHome() {
  home.setPosition(sf::Vector2f(width / 2.f, height / 2.f));
}

void World::setupFood() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> disX(0.f, static_cast<float>(width));
  std::uniform_real_distribution<float> disY(0.f, static_cast<float>(height));
  std::uniform_real_distribution<float> disOffset(-20.f, 20.f);

  for (std::size_t i = 0; i < NUM_FOOD_CLUMPS; i++) {
    float centerX = disX(gen);
    float centerY = disY(gen);

    // Keep food away from home
    while (std::abs(centerX - width / 2) < 50 &&
           std::abs(centerY - height / 2) < 50) {
      centerX = disX(gen);
      centerY = disY(gen);
    }

    for (std::size_t j = 0; j < NUM_FOOD_CRUMBS_PER_CLUMP; j++) {
      Food food;
      float offsetX = disOffset(gen);
      float offsetY = disOffset(gen);
      food.setPosition(sf::Vector2f(
          std::max(0.f, std::min(static_cast<float>(width), centerX + offsetX)),
          std::max(0.f,
                   std::min(static_cast<float>(height), centerY + offsetY))));
      foodItems.push_back(food);
    }
  }
}

void World::clearTarget() {
  hasTarget = false;
  targetPosition = {0.0f, 0.0f};
  target.setFillColor(sf::Color::Transparent);
  for (auto &ant : ants) {
    auto wanderBehavior = std::make_unique<WanderBehavior>();
    ant.setBehavior(std::move(wanderBehavior));
  }
}
