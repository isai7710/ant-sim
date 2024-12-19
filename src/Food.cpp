#include "Food.h"

Food::Food() {
  shape.setSize(sf::Vector2f(4.f, 4.f));
  shape.setFillColor(sf::Color::Green);
}

void Food::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(shape, states);
}

void Food::setPosition(const sf::Vector2f &pos) { shape.setPosition(pos); }

sf::Vector2f Food::getPosition() const { return shape.getPosition(); }
