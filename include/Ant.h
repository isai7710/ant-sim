#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Ant : public sf::Drawable {
public:
  Ant(unsigned int windowWidth, unsigned int windowHeight);
  void update(float deltaTime);
  void setPosition(const sf::Vector2f &pos);
  sf::Vector2f getPosition() const;
  void setFoundFood(bool found);
  bool hasFoundFood() const;

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
  void randomMove(float deltaTime);
  // void moveHome(float deltaTime);
  sf::Vector2f clampVector(const sf::Vector2f &v, float maxValue);

  sf::RectangleShape shape;

  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f desiredDirection;

  unsigned int windowWidth;
  unsigned int windowHeight;

  bool foundFood{false};

  float maxSpeed{50.0f};
  float steerStrength{2.0f};
  float wanderStrength{0.5f};
};
