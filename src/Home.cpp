#include "Home.h"

Home::Home() {
  shape.setSize(sf::Vector2f(50.f, 50.f));
  shape.setFillColor(sf::Color(139, 69, 19)); // Brown color
}

void Home::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(shape, states);
}

void Home::setPosition(const sf::Vector2f &pos) {
  shape.setPosition(pos - sf::Vector2f(25.f, 25.f)); // Center the home
}
