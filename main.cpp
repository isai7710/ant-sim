#include "World.h"
#include <SFML/Graphics.hpp>

const float ASPECT_RATIO = 16.f / 9.f;
const unsigned int WINDOW_WIDTH = 900;
const unsigned int WINDOW_HEIGHT = WINDOW_WIDTH / ASPECT_RATIO;
const unsigned int WORLD_WIDTH = 700;
const unsigned int WORLD_HEIGHT = 500;

int main() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Ant Simulator");
  window.setFramerateLimit(60);

  World world(WORLD_WIDTH, WORLD_HEIGHT);
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      // Check for mouse click
      world.handleEvents(event);
    }

    float deltaTime = clock.restart().asSeconds();

    if (!world.isSimulationPaused()) {
      world.update(deltaTime);
    }

    window.clear(sf::Color::White);
    world.draw(window);
    window.display();
  }

  return 0;
}
