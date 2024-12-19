#pragma once
#include <SFML/Graphics.hpp>

class Home : public sf::Drawable {
public:
  Home();
  void setPosition(const sf::Vector2f &pos);

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
  sf::RectangleShape shape;
};
