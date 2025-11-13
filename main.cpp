#include "src/physics.hpp"
#include "src/controller.hpp"
#include "src/celestial.hpp"
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

    float starMass = 5000.f;
    float starRadius = 40.f;
    sf::Vector2f starPosition(windowWidth / 2.f, windowHeight / 2.f);
    Celestial star(starMass, starRadius, starPosition, sf::Color::Yellow);

    float planetRadius = 10.f;
    float planetMass = 250.f;
    sf::Vector2f planetPosition(windowWidth / 2.f, windowHeight / 4.f);
    Celestial planet(planetMass, planetRadius, planetPosition, sf::Color::Blue);
    planet.accelerate(orbitalVelocity(planetPosition, starPosition, starMass));

    float moonRadius = 5.f;
    float moonMass = 1.f;
    sf::Vector2f moonOffset = {0, planetRadius * 3};
    sf::Vector2f moonPosition = planetPosition + moonOffset;
    Celestial moon(moonMass, moonRadius, moonPosition, sf::Color::White);
    moon.accelerate(planet.getVelocity() + orbitalVelocity(moonPosition, planetPosition, planetMass));

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

        planetPosition = planet.getPosition();
        moonPosition = moon.getPosition();

        sf::Vector2f planetAcceleration = gravity(planetPosition, starPosition, 1.f, starMass);
        planet.accelerate(planetAcceleration * dt);
        planet.move(dt);

        sf::Vector2f moonAcceleration = gravity(moonPosition, planet.getPosition(), moonMass, planetMass);

        moon.accelerate(planetAcceleration * dt);
        moon.accelerate(moonAcceleration * dt);
        moon.move(dt);

        planet.setShapePosition();
        moon.setShapePosition();

        window.clear();

        window.draw(star.getShape());
        window.draw(planet.getShape());
        window.draw(moon.getShape());

        window.display();
    }

    return 0;
}