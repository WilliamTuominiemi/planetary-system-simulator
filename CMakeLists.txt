cmake_minimum_required(VERSION 3.10)
project(planetary-system-simulator)

set(CMAKE_CXX_STANDARD 17)

# SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Main
add_executable(simulation
    src/physics.cpp
    src/controller.cpp
    src/celestial.cpp
    main.cpp
)
target_include_directories(simulation PRIVATE src)
target_link_libraries(simulation sfml-graphics sfml-window sfml-system)

# Tests
add_executable(test_runner
    src/physics.cpp
    src/controller.cpp
    tests/test_physics.cpp
    tests/test_controller.cpp
)
target_include_directories(test_runner PRIVATE src)
target_link_libraries(test_runner sfml-graphics sfml-window sfml-system)