#include "Home.h"

Home::Home() {
  home.setSize(sf::Vector2f(HOME_SIZE, HOME_SIZE));
  home.setFillColor(sf::Color::Black);
  home.setOutlineColor(sf::Color(139, 69, 21, 255));
  home.setOutlineThickness(2.0f);
}

void Home::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(home, states);
}

void Home::setPosition(const sf::Vector2f &pos) {
  home.setPosition(
      pos - sf::Vector2f(HOME_SIZE / 2.f,
                         HOME_SIZE /
                             2.f)); // Center the rectangle on the pos argument
}
