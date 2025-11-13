#include "src/physics.hpp"
#include "src/controller.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

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

    float starRadius = 40.f;
    float starMass = 5000.f;
    sf::Vector2f starPosition(windowWidth / 2.f, windowHeight / 2.f);
    sf::CircleShape star(starRadius);
    star.setOrigin(starRadius, starRadius);
    star.setPosition(starPosition);
    star.setFillColor(sf::Color::Yellow);

    float planetRadius = 10.f;
    float planetMass = 250.f;
    sf::Vector2f planetPosition(windowWidth / 2.f, windowHeight / 4.f);
    sf::CircleShape planet(planetRadius);
    planet.setOrigin(planetRadius, planetRadius);
    sf::Vector2f planetVelocity = orbitalVelocity(planetPosition, starPosition, starMass);
    planet.setFillColor(sf::Color::Blue);

    float moonRadius = 5.f;
    float moonMass = 1.f;
    sf::Vector2f moonOffset = {0, planetRadius * 3};
    sf::Vector2f moonPosition = planetPosition + moonOffset;
    sf::CircleShape moon(moonRadius);
    moon.setOrigin(moonRadius, moonRadius);
    sf::Vector2f moonVelocity = planetVelocity + orbitalVelocity(moonPosition, planetPosition, planetMass);

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

        sf::Vector2f planetAcceleration = gravity(planetPosition, starPosition, 1.f, starMass);
        planetVelocity += planetAcceleration * dt;
        planetPosition += planetVelocity * dt;

        sf::Vector2f moonAcceleration = gravity(moonPosition, planetPosition, moonMass, planetMass);
        moonVelocity += planetAcceleration * dt;
        moonVelocity += moonAcceleration * dt;
        moonPosition += moonVelocity * dt;

        planet.setPosition(planetPosition);
        moon.setPosition(moonPosition);

        window.clear();

        window.draw(star);
        window.draw(planet);
        window.draw(moon);

        window.display();
    }

    return 0;
}