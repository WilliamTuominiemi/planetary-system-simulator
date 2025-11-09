#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/physics.hpp"

TEST_CASE("direction returns normalized vector", "[direction]") {
    SECTION("horizontal direction") {
        sf::Vector2f result = direction({0.f, 0.f}, {3.f, 0.f});
        REQUIRE(result.x == Approx(1.f));
        REQUIRE(result.y == Approx(0.f));
    }
    
    SECTION("vertical direction") {
        sf::Vector2f result = direction({0.f, 0.f}, {0.f, 4.f});
        REQUIRE(result.x == Approx(0.f));
        REQUIRE(result.y == Approx(1.f));
    }
    
    SECTION("diagonal direction") {
        sf::Vector2f result = direction({0.f, 0.f}, {1.f, 1.f});
        float expected = 1.f / std::sqrt(2.f);
        REQUIRE(result.x == Approx(expected));
        REQUIRE(result.y == Approx(expected));
    }
    
    SECTION("zero distance returns zero vector") {
        sf::Vector2f result = direction({5.f, 5.f}, {5.f, 5.f});
        REQUIRE(result.x == 0.f);
        REQUIRE(result.y == 0.f);
    }
}

TEST_CASE("orbitDirection returns perpendicular vector", "[orbitDirection]") {
    SECTION("rotates 90 degrees counterclockwise") {
        sf::Vector2f result = orbitDirection({1.f, 0.f});
        REQUIRE(result.x == Approx(0.f));
        REQUIRE(result.y == Approx(-1.f));
    }
    
    SECTION("maintains magnitude") {
        sf::Vector2f input = {3.f, 4.f};
        sf::Vector2f result = orbitDirection(input);
        
        float inputMag = std::sqrt(input.x * input.x + input.y * input.y);
        float resultMag = std::sqrt(result.x * result.x + result.y * result.y);
        
        REQUIRE(resultMag == Approx(inputMag));
    }
    
    SECTION("perpendicular to original") {
        sf::Vector2f input = {1.f, 1.f};
        sf::Vector2f result = orbitDirection(input);
        
        // Dot product should be zero for perpendicular vectors
        float dot = input.x * result.x + input.y * result.y;
        REQUIRE(dot == Approx(0.f));
    }
}