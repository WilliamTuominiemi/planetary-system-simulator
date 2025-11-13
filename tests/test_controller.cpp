#include <SFML/Graphics.hpp>
#include "catch.hpp"
#include "../src/controller.hpp"
#include <cmath>

namespace Catch
{
    template <>
    struct StringMaker<sf::Vector2f>
    {
        static std::string convert(sf::Vector2f const &value)
        {
            return "(" + std::to_string(value.x) + ", " + std::to_string(value.y) + ")";
        }
    };
}

TEST_CASE("zoom gives the right values", "[zoom]")
{
    SECTION("in")
    {
        sf::Event event;
        event.type = sf::Event::MouseWheelScrolled;
        event.mouseWheelScroll.wheel = sf::Mouse::VerticalWheel;
        event.mouseWheelScroll.delta = 1;

        REQUIRE(zoom(event) == 0.95f);
    }
    SECTION("out")
    {
        sf::Event event;
        event.type = sf::Event::MouseWheelScrolled;
        event.mouseWheelScroll.wheel = sf::Mouse::VerticalWheel;
        event.mouseWheelScroll.delta = -1;

        REQUIRE(zoom(event) == 1.05f);
    }
}

TEST_CASE("move gives the right vectors", "[move]")
{
    SECTION("up")
    {
        sf::Event event;
        event.type = sf::Event::KeyPressed;
        event.key.code = sf::Keyboard::W;

        sf::Vector2f up = {0.f, -1.f};

        REQUIRE(move(event) == up);

        event.key.code = sf::Keyboard::Up;
        REQUIRE(move(event) == up);
    }
    SECTION("right")
    {
        sf::Event event;
        event.type = sf::Event::KeyPressed;
        event.key.code = sf::Keyboard::D;

        sf::Vector2f right = {1.f, 0.f};

        REQUIRE(move(event) == right);

        event.key.code = sf::Keyboard::Right;
        REQUIRE(move(event) == right);
    }
    SECTION("down")
    {
        sf::Event event;
        event.type = sf::Event::KeyPressed;
        event.key.code = sf::Keyboard::S;

        sf::Vector2f down = {0.f, 1.f};

        REQUIRE(move(event) == down);

        event.key.code = sf::Keyboard::Down;
        REQUIRE(move(event) == down);
    }
    SECTION("left")
    {
        sf::Event event;
        event.type = sf::Event::KeyPressed;
        event.key.code = sf::Keyboard::A;

        sf::Vector2f left = {-1.f, 0.f};

        REQUIRE(move(event) == left);

        event.key.code = sf::Keyboard::Left;
        REQUIRE(move(event) == left);
    }
    SECTION("other")
    {
        sf::Event event;
        event.type = sf::Event::KeyPressed;
        event.key.code = sf::Keyboard::Q;

        REQUIRE(move(event) == sf::Vector2f{0.f, 0.f});
    }
}