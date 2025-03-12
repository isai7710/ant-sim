#include "World.h"
#include "SeekBehavior.h"
#include "UI.h"
#include "Vector2Utils.h"
#include "WanderBehavior.h"
#include <cmath>
#include <memory>
#include <random>

World::World(unsigned int width, unsigned int height)
    : width(width), height(height),
      centerPoint(sf::Vector2f(width / 2.f, height / 2.f)),
      addAntButton(sf::Vector2f(width + 10.f, 0.f), sf::Vector2f(80.f, 40.f),
                   10.f, 5.f, 64, "Add Ant"),
      pausePlayButton(sf::Vector2f(width + 10.f, 50.f),
                      sf::Vector2f(80.f, 40.f), 10.f, 5.f, 64, "||") {
  ants.reserve(NUM_ANTS);
  setupWorld();
}

void World::update(float deltaTime) {
  for (auto &ant : ants) {
    ant.update(*this, deltaTime);
  }
  for (auto p = pheromones.begin(); p != pheromones.end();) {
    p->update(deltaTime);
    if (p->strength <= p->MIN_STRENGTH) {
      p = pheromones.erase(p);
    } else {
      ++p;
    }
  }
  if (hasTarget) {
    for (auto &ant : ants) {
      if (Vector2Utils::squaredDistance(targetPosition, ant.getPosition()) <
          TARGET_REACH_DISTANCE_SQUARED) {
        clearTarget();
      }
    }
  }
}

void World::draw(sf::RenderWindow &window) {
  window.draw(home);
  for (const auto &ant : ants) {
    window.draw(ant);
  }
  for (const auto &food : foodItems) {
    window.draw(food);
  }
  for (const auto &pheromone : pheromones) {
    window.draw(pheromone);
  }
  if (hasTarget) {
    window.draw(target);
  }
  window.draw(bounds);
  window.draw(addAntButton);
  window.draw(pausePlayButton);
}

void World::handleEvents(const sf::Event &event) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
    if (addAntButton.contains(mousePos)) {
      addAnt();
    } else if (pausePlayButton.contains(mousePos)) {
      isPaused = !isPaused;
    } else if (mousePos.x < width && mousePos.y < height) {
      updateTarget({mousePos.x, mousePos.y});
    }
  }
}

void World::updateTarget(sf::Vector2f position) {
  if (targetPosition == position) {
    clearTarget();
    return;
  }

  targetPosition = position;
  target.setPosition(targetPosition.x - target.getRadius(),
                     targetPosition.y - target.getRadius());
  target.setFillColor(sf::Color::Green);
  hasTarget = true;

  for (auto &ant : ants) {
    auto seekBehavior = std::make_unique<SeekBehavior>(targetPosition);
    ant.setBehavior(std::move(seekBehavior));
  }
}

void World::setupWorld() {
  // ----- WORLD BOUNDS ------
  sf::Vector2f size{static_cast<float>(width), static_cast<float>(height)};
  RoundedRectangleGenerator const outer_generator{size, RADIUS, QUALITY};
  sf::Vector2f inner_offset{5.f, 5.f};
  sf::Vector2f inner_size = size - 2.0f * inner_offset;
  RoundedRectangleGenerator const inner_generator{inner_size,
                                                  RADIUS - THICKNESS, QUALITY};

  for (uint32_t i = 0; i < QUALITY; i++) {
    bounds[2 * i + 0].position = inner_offset + inner_generator.getPoint(i);
    bounds[2 * i + 0].color = sf::Color::Black;
    bounds[2 * i + 1].position = outer_generator.getPoint(i);
    bounds[2 * i + 1].color = sf::Color::Black;
  }

  bounds[2 * QUALITY + 0].position = inner_offset + inner_generator.getPoint(0);
  bounds[2 * QUALITY + 0].color = sf::Color::Black;
  bounds[2 * QUALITY + 1].position = outer_generator.getPoint(0);
  bounds[2 * QUALITY + 1].color = sf::Color::Black;

  // ----- HOME -----
  home.setPosition(centerPoint);

  // ----- ANTS -----
  for (std::size_t i = 0; i < NUM_ANTS; i++) {
    ants.emplace_back(width - 2 * THICKNESS, height - 2 * THICKNESS,
                      centerPoint);
  }

  // ----- FOOD -----
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> disX(0.f, static_cast<float>(width));
  std::uniform_real_distribution<float> disY(0.f, static_cast<float>(height));
  std::uniform_real_distribution<float> disOffset(-FOOD_DIST, FOOD_DIST);

  for (std::size_t i = 0; i < NUM_FOOD_CLUMPS; i++) {
    float centerX = disX(gen);
    float centerY = disY(gen);

    // Keep food away from home
    while (std::abs(centerX - static_cast<float>(width) / 2) < 50 &&
           std::abs(centerY - static_cast<float>(height) / 2) < 50) {
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

void World::addAnt() { ants.emplace_back(width, height, centerPoint); }
void World::addPheromone(const Pheromone &pheromone) {
  pheromones.push_back(pheromone);
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
