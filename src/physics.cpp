#include "physics.hpp"

sf::Vector2f direction(sf::Vector2f from, sf::Vector2f to)
{
    sf::Vector2f delta = to - from;
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (dist == 0.f) return {0.f, 0.f};
    return delta * (1.f / dist);
}

sf::Vector2f orbitDirection(sf::Vector2f dir)
{
    return { dir.y, -dir.x };
}