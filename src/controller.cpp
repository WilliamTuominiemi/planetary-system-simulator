#include "controller.hpp"
float zoom(sf::Event event)
{
    if (event.mouseWheelScroll.delta == 1)
    {
        return .95;
    }
    else
    {
        return 1.05;
    }
}

sf::Vector2f move(sf::Event event)
{
    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
    {
        return {0.f, -1.f};
    }
    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
    {
        return {1.f, 0.f};
    }
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
    {
        return {0.f, 1.f};
    }
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
    {
        return {-1.f, 0.f};
    }
    return {0.f, 0.f};
}