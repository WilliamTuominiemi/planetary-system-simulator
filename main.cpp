#include "src/physics.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    int windowWidth = 800;
    int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Planetary system");
    window.setFramerateLimit(60);
    sf::Clock clock;
    float dt = 0.016f;
    float lastTime = 0.f;

    sf::View view = window.getDefaultView();
    window.setView(view);

    float starRadius = 50.f;
    float starMass = 5000.f;
    sf::Vector2f starPosition(windowWidth / 2.f, windowHeight / 2.f);
    sf::CircleShape star(starRadius);
    star.setOrigin(starRadius, starRadius);
    star.setPosition(starPosition);

    float planetRadius = 10.f;
    float planetMass = 1.f;
    sf::Vector2f planetPosition(windowWidth / 2.f, windowHeight / 4.f);
    sf::CircleShape planet(planetRadius);
    planet.setOrigin(planetRadius, planetRadius);
    sf::Vector2f planetVelocity = orbitalVelocity(planetPosition, starPosition, starMass);

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
                if (event.mouseWheelScroll.delta == 1)
                {
                    view.zoom(0.95);
                }
                else
                {
                    view.zoom(1.1);
                }
                window.setView(view);
            }
        }

        sf::Vector2f acceleration = gravity(planetPosition, starPosition, 1.f, starMass);
        planetVelocity += acceleration * dt;
        planetPosition += planetVelocity * dt;

        window.clear();

        window.draw(star);
        planet.setPosition(planetPosition);
        window.draw(planet);

        window.display();
    }

    return 0;
}