#pragma once
#include "Ant.h"
#include "Food.h"
#include "Home.h"
#include <SFML/Graphics.hpp>
#include <vector>

class World {
public:
  World(unsigned int width, unsigned int height);
  void update(float deltaTime);
  void draw(sf::RenderWindow &window);

private:
  void setupHome(); // set up Home object's position in window
  void setupAnts(); // set up Ants vector with number of ants
  void setupFood(); // set up food clumps and food crumbs per clump

  std::vector<Ant> ants;
  std::vector<Food> foodItems;
  Home home;

  unsigned int width;
  unsigned int height;
  static constexpr int numAnts = 10;
  static constexpr int numFoodClumps = 3;
  static constexpr int numFoodCrumbsPerClump = 30;
};
