#include "World.h"
#include <SFML/Graphics.hpp>

int main() {
  const unsigned int WINDOW_WIDTH = 500;
  const unsigned int WINDOW_HEIGHT = 500;

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Ant Simulator");
  window.setFramerateLimit(60);

  World world(WINDOW_WIDTH, WINDOW_HEIGHT);
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      // Check for mouse click
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        world.updateTarget({static_cast<float>(event.mouseButton.x),
                            static_cast<float>(event.mouseButton.y)});
      }
    }

    float deltaTime = clock.restart().asSeconds();

    world.update(deltaTime);

    window.clear(sf::Color::Black);
    world.draw(window);
    window.display();
  }

  return 0;
}
