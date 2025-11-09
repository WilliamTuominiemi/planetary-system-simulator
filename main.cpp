#include <SFML/Graphics.hpp>

int main() {
    int windowWidth = 800;
    int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Planetary system");
    window.setFramerateLimit(60);


    float starRadius = 50.f;
    sf::CircleShape star(starRadius);
    star.setOrigin(starRadius, starRadius);
    star.setPosition(windowWidth / 2.f, windowHeight / 2.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(star);
        window.display();
    }

    return 0;
}