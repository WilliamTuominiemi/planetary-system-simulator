#include "celestial.hpp"

Celestial::Celestial() : mass(0.f), radius(0.f), position(0.f, 0.f), velocity(0.f, 0.f), shape(), color(sf::Color::White)
{
}

Celestial::Celestial(float mass, float radius, sf::Vector2f position, sf::Color color)
    : mass(mass), radius(radius), position(position), velocity(0.f, 0.f), shape(radius), color(color)
{
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
    shape.setFillColor(color);
}

void Celestial::accelerate(sf::Vector2f acceleration)
{
    velocity += acceleration;
}

void Celestial::move(float dt)
{
    position += velocity * dt;
}

sf::CircleShape Celestial::getShape()
{
    return shape;
}

sf::Vector2f Celestial::getVelocity()
{
    return velocity;
}

sf::Vector2f Celestial::getPosition()
{
    return position;
}

void Celestial::setShapePosition()
{
    shape.setPosition(position);
}