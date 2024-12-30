#pragma once
#include "Ant.h"
#include "Food.h"
#include "Home.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class World {
public:
  explicit World(unsigned int width, unsigned int height);
  void update(float deltaTime);
  void draw(sf::RenderWindow &window);
  void handleEvents(const sf::Event &event);
  void updateTarget(sf::Vector2f position);
  sf::Vector2f getTargetPosition();

private:
  void setupWorld();
  void addAnt();
  void clearTarget();

  Home home;
  std::vector<Ant> ants;
  std::vector<Food> foodItems;

  sf::RectangleShape addAntButton;
  sf::Text addAntButtonText;
  sf::Font font;

  sf::CircleShape target{5.0f};
  sf::Vector2f targetPosition;
  bool hasTarget = false;

  sf::Vector2f centerPoint;
  const unsigned int width;
  const unsigned int height;
  static constexpr std::size_t NUM_ANTS = 3;
  static constexpr std::size_t NUM_FOOD_CLUMPS = 3;
  static constexpr std::size_t NUM_FOOD_CRUMBS_PER_CLUMP = 30;
};
