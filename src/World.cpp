#include "World.h"
#include <random>

World::World(unsigned int width, unsigned int height)
    : width(width), height(height) {
  setupHome();
  setupFood();
  setupAnts();
}

void World::update(float deltaTime) {
  for (auto &ant : ants) {
    ant.update(deltaTime);
    /*
      // Basic collision detection with food
      if (!ant.hasFoundFood()) {
        for (const auto &food : foodItems) {
          sf::Vector2f diff = food.getPosition() - ant.getPosition();
          if (std::sqrt(diff.x * diff.x + diff.y * diff.y) < 10.f) {
            ant.setFoundFood(true);
            break;
          }
        }
      }
    */
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
}

void World::setupHome() {
  home.setPosition(sf::Vector2f(width / 2.f, height / 2.f));
}

void World::setupAnts() {
  for (int i = 0; i < numAnts; i++) {
    Ant ant(width, height);
    ant.setPosition(sf::Vector2f(width / 2.f, height / 2.f));
    ants.push_back(ant);
  }
}

void World::setupFood() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> disX(0.f, static_cast<float>(width));
  std::uniform_real_distribution<float> disY(0.f, static_cast<float>(height));
  std::uniform_real_distribution<float> disOffset(-20.f, 20.f);

  for (int i = 0; i < numFoodClumps; i++) {
    float centerX = disX(gen);
    float centerY = disY(gen);

    // Keep food away from home
    while (std::abs(centerX - width / 2) < 50 &&
           std::abs(centerY - height / 2) < 50) {
      centerX = disX(gen);
      centerY = disY(gen);
    }

    for (int j = 0; j < numFoodCrumbsPerClump; j++) {
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
