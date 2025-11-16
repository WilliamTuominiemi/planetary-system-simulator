#ifndef CELESTIAL_HPP
#define CELESTIAL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Celestial
{
private:
    float mass;
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;
    sf::Color color;
    std::vector<Celestial> satellites;

public:
    // Constructor
    Celestial();
    Celestial(float mass, float radius, sf::Vector2f position, sf::Color color);

    // Methods
    void accelerate(sf::Vector2f acceleration, float dt);
    void move(float dt);

    // Getters/Setters
    sf::CircleShape getShape();
    sf::Vector2f getVelocity();
    sf::Vector2f getPosition();
    float getMass();
    std::vector<Celestial> &getSatellites();

    void setVelocity(sf::Vector2f newVelocity);
    void setShapePosition();
    void setSatellite(Celestial satellite);
};

#endif
