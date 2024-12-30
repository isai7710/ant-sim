#pragma once
#include <SFML/Graphics.hpp>

class Home : public sf::Drawable {
public:
  Home();
  void setPosition(const sf::Vector2f &pos);
  sf::Vector2f getPosition() { return home.getPosition(); };
  float getHomeSize() { return HOME_SIZE; };

private:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
  sf::RectangleShape home;
  static constexpr float HOME_SIZE = 50.f;
};
