#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

/**
 * @brief squared distance from the difference between two positions
 */
float squaredDistance(sf::Vector2f delta);

/**
 * @brief distance between two positions from their squared distance
 */
float distance(float dSquared);

/**
 * @brief difference between two positions
 */
sf::Vector2f positionDelta(sf::Vector2f from, sf::Vector2f to);

/**
 * @brief returns unit vector from one position to another
 */
sf::Vector2f direction(sf::Vector2f from, sf::Vector2f to);

/**
 * @brief a perpendicular vector to input vector
 */
sf::Vector2f orbitDirection(sf::Vector2f dir);

/**
 * @brief returns the acceleration towards the bigger mass
 */
sf::Vector2f gravity(
    sf::Vector2f smallerPosition,
    sf::Vector2f biggerPosition,
    float smallerMass,
    float biggerMass);

/**
 * @brief returns the velocity of the orbiting celestial
 */
sf::Vector2f orbitalVelocity(
    sf::Vector2f smallerPosition,
    sf::Vector2f biggerPosition,
    float biggerMass);