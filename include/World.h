#pragma once
#include "Ant.h"
#include "Food.h"
#include "Home.h"
#include <SFML/Graphics.hpp>
#include <vector>

class World {
public:
  explicit World(unsigned int width, unsigned int height);
  void update(float deltaTime);
  void draw(sf::RenderWindow &window);
  void updateTarget(sf::Vector2f position);
  sf::Vector2f getTargetPosition();

private:
  void setupAnts(); // set up Ants vector with number of ants
  void setupHome(); // set up Home object's position in window
  void setupFood(); // set up food clumps and food crumbs per clump

  std::vector<Ant> ants;
  std::vector<Food> foodItems;
  Home home;

  sf::CircleShape target{5.0f};
  sf::Vector2f targetPosition;
  bool hasTarget = false;

  void clearTarget();

  const unsigned int width;
  const unsigned int height;
  static constexpr std::size_t NUM_ANTS = 3;
  static constexpr std::size_t NUM_FOOD_CLUMPS = 3;
  static constexpr std::size_t NUM_FOOD_CRUMBS_PER_CLUMP = 30;
};
