#include "physics.hpp"

const float G = 1000.0f; // gravitational constant

float squaredDistance(sf::Vector2f delta)
{
    return delta.x * delta.x + delta.y * delta.y;
}

float distance(float dSquared)
{
    return std::sqrt(dSquared);
}

sf::Vector2f positionDelta(sf::Vector2f from, sf::Vector2f to)
{
    return to - from;
}

sf::Vector2f direction(sf::Vector2f from, sf::Vector2f to)
{
    sf::Vector2f delta = to - from;
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (dist == 0.f)
        return {0.f, 0.f};
    return delta * (1.f / dist);
}

sf::Vector2f orbitDirection(sf::Vector2f dir)
{
    return {-dir.y, dir.x};
}

sf::Vector2f gravity(
    sf::Vector2f smallerPosition,
    sf::Vector2f biggerPosition,
    float smallerMass,
    float biggerMass)
{
    sf::Vector2f delta = positionDelta(smallerPosition, biggerPosition);
    float dSquared = squaredDistance(delta);
    float dist = distance(dSquared);

    if (dist < 20.f)
        return {0.f, 0.f};

    float force = G * biggerMass / dSquared;

    sf::Vector2f acceleration = (delta / dist) * force;

    return acceleration;
}

sf::Vector2f orbitalVelocity(
    sf::Vector2f smallerPosition,
    sf::Vector2f biggerPosition,
    float biggerMass)
{
    sf::Vector2f delta = positionDelta(biggerPosition, smallerPosition);
    float dSquared = squaredDistance(delta);
    float dist = distance(dSquared);

    if (dist < 20.f)
        return {0.f, 0.f};

    sf::Vector2f dir = direction(biggerPosition, smallerPosition);
    sf::Vector2f orbitalDir = orbitDirection(dir);

    float orbitalSpeed = std::sqrt(G * biggerMass / dist);

    return orbitalDir * orbitalSpeed;
}