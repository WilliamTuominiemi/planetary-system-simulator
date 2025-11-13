#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief value to multiply the view zoom with, according to scrollwheel event
 */
float zoom(sf::Event event);

/**
 * @brief offset vector in which direction the view is to be moved
 */
sf::Vector2f move(sf::Event event);