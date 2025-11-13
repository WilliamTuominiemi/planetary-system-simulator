#ifndef CELESTIAL_HPP
#define CELESTIAL_HPP

#include <SFML/Graphics.hpp>

class Celestial
{
private:
    float mass;
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;
    sf::Color color;

public:
    // Constructor
    Celestial();
    Celestial(float mass, float radius, sf::Vector2f position, sf::Color color);

    // Methods
    void accelerate(sf::Vector2f acceleration);
    void move(float dt);

    // Getters/Setters
    sf::CircleShape getShape();
    sf::Vector2f getVelocity();
    sf::Vector2f getPosition();

    void setShapePosition();
};

#endif
