#include "src/physics.hpp"
#include "src/controller.hpp"
#include "src/celestial.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

std::vector<sf::CircleShape> accelerateSatellites(Celestial &celestial, const sf::Vector2f &celestialAcceleration, float dt)
{
    std::vector<sf::CircleShape> satelliteShapes;

    for (Celestial &satellite : celestial.getSatellites())
    {
        sf::Vector2f satelliteAcceleration = gravity(satellite.getPosition(), celestial.getPosition(), satellite.getMass(), celestial.getMass());

        satellite.accelerate(celestialAcceleration * dt);
        satellite.accelerate(satelliteAcceleration * dt);
        satellite.move(dt);
        satellite.setShapePosition();

        std::vector<sf::CircleShape> childShapes = accelerateSatellites(satellite, satelliteAcceleration, dt);
        satelliteShapes.insert(satelliteShapes.end(), childShapes.begin(), childShapes.end());
        satelliteShapes.push_back(satellite.getShape());
    }

    return satelliteShapes;
}

int main()
{
    int windowWidth = 800;
    int windowHeight = 800;
    float windowMoveSpeed = 5.f;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Planetary system");
    window.setFramerateLimit(60);
    sf::Clock clock;
    float dt = 0.016f;
    float lastTime = 0.f;

    sf::View view = window.getDefaultView();
    window.setView(view);

    float starMass = 5000.f;
    float starRadius = 40.f;
    sf::Vector2f starPosition(windowWidth / 2.f, windowHeight / 2.f);
    sf::Color starColor(255, 239, 209);
    Celestial star(starMass, starRadius, starPosition, starColor);

    float planetRadius = 10.f;
    float planetMass = 250.f;
    sf::Vector2f planetPosition(windowWidth / 2.f, windowHeight / 4.f);
    sf::Color planetColor(115, 193, 222);
    Celestial planet(planetMass, planetRadius, planetPosition, planetColor);
    planet.accelerate(orbitalVelocity(planetPosition, starPosition, starMass));

    float moonRadius = 5.f;
    float moonMass = 1.f;
    sf::Vector2f moonOffset = {0, planetRadius * 3};
    sf::Vector2f moonPosition = planetPosition + moonOffset;
    sf::Color moonColor(155, 161, 163);
    Celestial moon(moonMass, moonRadius, moonPosition, moonColor);
    moon.accelerate(planet.getVelocity() + orbitalVelocity(moonPosition, planetPosition, planetMass));

    planet.setSatellite(moon);
    star.setSatellite(planet);

    while (window.isOpen())
    {
        float currentTime = clock.getElapsedTime().asSeconds();
        float dt = currentTime - lastTime;
        lastTime = currentTime;
        if (dt > 0.1f)
            dt = 0.1f;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                view.zoom(zoom(event));
                window.setView(view);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                view.move(move(event) * windowMoveSpeed);
                window.setView(view);
            }
        }

        std::vector<sf::CircleShape> shapes = accelerateSatellites(star, sf::Vector2f{0, 0}, dt);

        window.clear();

        window.draw(star.getShape());

        for (sf::CircleShape shape : shapes)
        {
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}
