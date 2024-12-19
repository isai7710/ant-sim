#pragma once
#include <SFML/Graphics.hpp>

class Food : public sf::Drawable {
public:
  Food();
  void setPosition(const sf::Vector2f &pos);
  sf::Vector2f getPosition() const;

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
  sf::RectangleShape shape;
};
