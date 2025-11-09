#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

/**
 * @brief returns unit vector from one position to another
 */
sf::Vector2f direction(sf::Vector2f from, sf::Vector2f to);

/**
 * returns a perpendicular vector to input vector, used for simulating orbit
 */
sf::Vector2f orbitDirection(sf::Vector2f dir);

