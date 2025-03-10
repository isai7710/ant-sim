# ANT SIMULATOR

I did my best to follow object-oriented principles to encapsulate all simulation logic in clearly defined classes and provide clean interfaces for interaction with the rendering system and basic input handling.

## World class

The `main.cpp` file acts as the entry point, where an SFML window object is created along with the `world` object. The `World` class serves as the container that manages all entities in the simulation (ants, food, pheromones, etc) and is responsible for:

1. Initializing the simulation environment with proper positioning of entities
2. Managing the main game loop's update and render cycles for all objects through `deltaTime` based updates for frame-rate independence
3. Handling basic user interactions like mouse clicks for target setting
4. Coordinating `ant` behaviors through steering mechanisms
5. Managing dynamic elmeents like `pheromone` creation and decay

This allows the World class to serve as the glue between user inputs, simulation logic, and visual representation. Some key methods to note include:

### `setupWorld()`

Initializes all simulation components upon creation of the `World` class. It is called in the constructor.

### `update(float deltaTime)`

Advances the simulation by the specified time step (but does not yet draw it on the window). This update includes:

- Updates to each ant's position and behavior
- Management of pheromone decay and removal when its strength falls below threshold
- Checks if ants have reached targets made by user to clear them

### `draw(sf::RenderWindow &window)`

Uses the reference to the main window passed as an argument to draw all entities to the SFML window **after** the `world` object is updated in the main game loop.

### `handleEvents(const sf::Event &event)`

Processes user input events that are accessed or identified in the main game loop, particularly mouse clicks. Here we either

1. Add a new ant when the add button is clicked, or
2. Updates target location for ants to seek with the `updateTarget(sf::Vector2f position)` method. This method first clears the target if its position matches the current target, and then sets a new target position for the ants while changing their behavior to seek that target.

### Key members of the World class:

- `std::vector<Ant> ants`: stores the ants currently in the simulation
- `std::vector<Food> foodItems`: stores all the food crumbs in the simulation
- `std::vector<Pheromone> pheromones`: stores all the pheromones currently dropped by ants in the simulation
