#pragma once
#include "Ant.h"
#include "Food.h"
#include "Home.h"
#include "Pheromone.h"
#include "UI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System.hpp>
#include <vector>

class World {
public:
  explicit World(unsigned int width, unsigned int height);
  void update(float deltaTime);
  void draw(sf::RenderWindow &window);
  void handleEvents(const sf::Event &event);
  void updateTarget(sf::Vector2f position);
  void addPheromone(const Pheromone &pheromone);
  bool isSimulationPaused() const { return isPaused; }

private:
  void setupWorld();
  void addAnt();
  void clearTarget();

  static constexpr float RADIUS = 10.f;
  static constexpr float THICKNESS = 5.f;
  static constexpr std::size_t QUALITY = 64;

  sf::VertexArray bounds{sf::TriangleStrip, 2 * QUALITY + 2};

  Home home;
  std::vector<Ant> ants;
  std::vector<Food> foodItems;
  std::vector<Pheromone> pheromones;

  RoundedButton addAntButton;
  RoundedButton pausePlayButton;
  sf::Font font;

  bool isPaused = false;

  sf::CircleShape target{5.0f};
  sf::Vector2f targetPosition;
  bool hasTarget = false;

  sf::Vector2f centerPoint;
  const unsigned int width;
  const unsigned int height;

  static constexpr std::size_t NUM_ANTS = 3;
  static constexpr std::size_t NUM_FOOD_CLUMPS = 3;
  static constexpr std::size_t NUM_FOOD_CRUMBS_PER_CLUMP = 30;
  static constexpr float FOOD_DIST = 20.f;
  static constexpr float TARGET_REACH_DISTANCE = 2.0f;
  static constexpr float TARGET_REACH_DISTANCE_SQUARED =
      TARGET_REACH_DISTANCE * TARGET_REACH_DISTANCE;
};
