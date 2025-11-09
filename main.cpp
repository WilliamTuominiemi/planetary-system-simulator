#include "src/physics.hpp"
#include <SFML/Graphics.hpp>

int main() {
    int windowWidth = 800;
    int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Planetary system");
    window.setFramerateLimit(60);


    float starRadius = 50.f;
    sf::Vector2f starPosition(windowWidth / 2.f, windowHeight / 2.f);
    sf::CircleShape star(starRadius);
    star.setOrigin(starRadius, starRadius);
    star.setPosition(starPosition);

    float planetRadius = 10.f;
    float planetOrbitSpeed = 5.f;
    sf::Vector2f planetPosition(windowWidth / 2.f, windowHeight / 4.f);
    sf::CircleShape planet(planetRadius);
    planet.setOrigin(planetRadius, planetRadius);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(star);

        planet.setPosition(planetPosition); 
        window.draw(planet);

        sf::Vector2f gravity = direction(planetPosition, starPosition);
        sf::Vector2f orbitVelocity = orbitDirection(gravity * planetOrbitSpeed);
        planetPosition -= orbitVelocity;

        window.display();
    }

    return 0;
}