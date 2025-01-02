#ifndef PHEROMONE_H
#define PHEROMONE_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

enum class PheromoneType {
  Home, // Ant is wandering, blue pheromone leads to home
  Food  // Ant has found food and is going home, red pheromone leads to food
        // source
};

struct Pheromone : public sf::Drawable {
  sf::Vector2f position;
  sf::CircleShape pheromone{2.0f};
  PheromoneType type;
  float strength;

  static constexpr float DECAY_RATE = 0.08f;
  static constexpr float MIN_STRENGTH = 0.02f;

  Pheromone(sf::Vector2f p, PheromoneType t, float s = 1.0f)
      : position(p), type(t), strength(s) {
    pheromone.setPosition(position);
    if (type == PheromoneType::Home) {
      pheromone.setFillColor(sf::Color(0, 0, 255, 255));
    }
    if (type == PheromoneType::Food) {
      pheromone.setFillColor(sf::Color(255, 0, 0, 255));
    }
  }

  void update(float deltaTime) {
    strength -= DECAY_RATE * deltaTime;
    if (strength < MIN_STRENGTH) {
      strength = 0.0f; // cap strength to 0 to prevent negative values
    }
    updateAppearance();
  }

  void updateAppearance() {
    pheromone.setFillColor(sf::Color(
        pheromone.getFillColor().r, pheromone.getFillColor().g,
        pheromone.getFillColor().b, static_cast<sf::Uint8>(strength * 255)));
  }

private:
  // Override sf::Drawable's draw method
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    target.draw(pheromone, states);
  }
};

#endif
