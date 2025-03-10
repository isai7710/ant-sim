cmake_minimum_required(VERSION 3.10)
project(AntSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Source files
set(SOURCES
    main.cpp
    src/Ant.cpp
    src/Food.cpp
    src/Home.cpp
    src/World.cpp
    src/SeekBehavior.cpp
    src/WanderBehavior.cpp
)

# Header files
set(HEADERS
    include/Ant.h
    include/Food.h
    include/Home.h
    include/World.h
    include/Pheromone.h
    include/IMovementBehavior.h
    include/SeekBehavior.h
    include/WanderBehavior.h
    include/Vector2Utils.h
    include/UI.h
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
