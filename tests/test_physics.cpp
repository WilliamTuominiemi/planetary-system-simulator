#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/physics.hpp"
#include <cmath>

TEST_CASE("squaredDistance calculates correct squared distance", "[squaredDistance]")
{
    SECTION("horizontal distance")
    {
        sf::Vector2f delta = {3.f, 0.f};
        REQUIRE(squaredDistance(delta) == Approx(9.f));
    }

    SECTION("vertical distance")
    {
        sf::Vector2f delta = {0.f, 4.f};
        REQUIRE(squaredDistance(delta) == Approx(16.f));
    }

    SECTION("diagonal distance (3-4-5 triangle)")
    {
        sf::Vector2f delta = {3.f, 4.f};
        REQUIRE(squaredDistance(delta) == Approx(25.f));
    }

    SECTION("negative components")
    {
        sf::Vector2f delta = {-3.f, -4.f};
        REQUIRE(squaredDistance(delta) == Approx(25.f));
    }

    SECTION("zero distance")
    {
        sf::Vector2f delta = {0.f, 0.f};
        REQUIRE(squaredDistance(delta) == Approx(0.f));
    }
}

TEST_CASE("distance calculates correct distance from squared distance", "[distance]")
{
    SECTION("perfect square")
    {
        REQUIRE(distance(25.f) == Approx(5.f));
    }

    SECTION("non-perfect square")
    {
        REQUIRE(distance(2.f) == Approx(std::sqrt(2.f)));
    }

    SECTION("zero")
    {
        REQUIRE(distance(0.f) == Approx(0.f));
    }

    SECTION("large value")
    {
        REQUIRE(distance(10000.f) == Approx(100.f));
    }
}

TEST_CASE("positionDelta calculates correct delta vector", "[positionDelta]")
{
    SECTION("positive delta")
    {
        sf::Vector2f result = positionDelta({0.f, 0.f}, {5.f, 3.f});
        REQUIRE(result.x == Approx(5.f));
        REQUIRE(result.y == Approx(3.f));
    }

    SECTION("negative delta")
    {
        sf::Vector2f result = positionDelta({5.f, 3.f}, {0.f, 0.f});
        REQUIRE(result.x == Approx(-5.f));
        REQUIRE(result.y == Approx(-3.f));
    }

    SECTION("mixed components")
    {
        sf::Vector2f result = positionDelta({2.f, 5.f}, {7.f, 1.f});
        REQUIRE(result.x == Approx(5.f));
        REQUIRE(result.y == Approx(-4.f));
    }

    SECTION("same position")
    {
        sf::Vector2f result = positionDelta({3.f, 3.f}, {3.f, 3.f});
        REQUIRE(result.x == Approx(0.f));
        REQUIRE(result.y == Approx(0.f));
    }
}

TEST_CASE("direction returns normalized vector", "[direction]")
{
    SECTION("horizontal direction right")
    {
        sf::Vector2f result = direction({0.f, 0.f}, {3.f, 0.f});
        REQUIRE(result.x == Approx(1.f));
        REQUIRE(result.y == Approx(0.f));
    }

    SECTION("horizontal direction left")
    {
        sf::Vector2f result = direction({3.f, 0.f}, {0.f, 0.f});
        REQUIRE(result.x == Approx(-1.f));
        REQUIRE(result.y == Approx(0.f));
    }

    SECTION("vertical direction up")
    {
        sf::Vector2f result = direction({0.f, 0.f}, {0.f, 4.f});
        REQUIRE(result.x == Approx(0.f));
        REQUIRE(result.y == Approx(1.f));
    }

    SECTION("vertical direction down")
    {
        sf::Vector2f result = direction({0.f, 4.f}, {0.f, 0.f});
        REQUIRE(result.x == Approx(0.f));
        REQUIRE(result.y == Approx(-1.f));
    }

    SECTION("diagonal direction")
    {
        sf::Vector2f result = direction({0.f, 0.f}, {1.f, 1.f});
        float expected = 1.f / std::sqrt(2.f);
        REQUIRE(result.x == Approx(expected));
        REQUIRE(result.y == Approx(expected));
    }

    SECTION("diagonal direction with different scale")
    {
        sf::Vector2f result = direction({0.f, 0.f}, {10.f, 10.f});
        float expected = 1.f / std::sqrt(2.f);
        REQUIRE(result.x == Approx(expected));
        REQUIRE(result.y == Approx(expected));
    }

    SECTION("3-4-5 triangle")
    {
        sf::Vector2f result = direction({0.f, 0.f}, {3.f, 4.f});
        REQUIRE(result.x == Approx(0.6f));
        REQUIRE(result.y == Approx(0.8f));
    }

    SECTION("zero distance returns zero vector")
    {
        sf::Vector2f result = direction({5.f, 5.f}, {5.f, 5.f});
        REQUIRE(result.x == 0.f);
        REQUIRE(result.y == 0.f);
    }

    SECTION("result is unit length")
    {
        sf::Vector2f result = direction({1.f, 2.f}, {4.f, 6.f});
        float magnitude = std::sqrt(result.x * result.x + result.y * result.y);
        REQUIRE(magnitude == Approx(1.f));
    }
}

TEST_CASE("orbitDirection returns perpendicular vector", "[orbitDirection]")
{
    SECTION("rotates right vector 90 degrees counterclockwise")
    {
        sf::Vector2f result = orbitDirection({1.f, 0.f});
        REQUIRE(result.x == Approx(0.f));
        REQUIRE(result.y == Approx(1.f));
    }

    SECTION("rotates up vector 90 degrees counterclockwise")
    {
        sf::Vector2f result = orbitDirection({0.f, 1.f});
        REQUIRE(result.x == Approx(-1.f));
        REQUIRE(result.y == Approx(0.f));
    }

    SECTION("rotates down vector 90 degrees counterclockwise")
    {
        sf::Vector2f result = orbitDirection({0.f, -1.f});
        REQUIRE(result.x == Approx(1.f));
        REQUIRE(result.y == Approx(0.f));
    }

    SECTION("rotates left vector 90 degrees counterclockwise")
    {
        sf::Vector2f result = orbitDirection({-1.f, 0.f});
        REQUIRE(result.x == Approx(0.f));
        REQUIRE(result.y == Approx(-1.f));
    }

    SECTION("maintains magnitude")
    {
        sf::Vector2f input = {3.f, 4.f};
        sf::Vector2f result = orbitDirection(input);

        float inputMag = std::sqrt(input.x * input.x + input.y * input.y);
        float resultMag = std::sqrt(result.x * result.x + result.y * result.y);

        REQUIRE(resultMag == Approx(inputMag));
    }

    SECTION("maintains magnitude for different scales")
    {
        sf::Vector2f input = {10.f, 0.f};
        sf::Vector2f result = orbitDirection(input);

        float inputMag = std::sqrt(input.x * input.x + input.y * input.y);
        float resultMag = std::sqrt(result.x * result.x + result.y * result.y);

        REQUIRE(resultMag == Approx(inputMag));
    }

    SECTION("perpendicular to original")
    {
        sf::Vector2f input = {1.f, 1.f};
        sf::Vector2f result = orbitDirection(input);

        // Dot product should be zero for perpendicular vectors
        float dot = input.x * result.x + input.y * result.y;
        REQUIRE(dot == Approx(0.f));
    }

    SECTION("perpendicular to arbitrary vector")
    {
        sf::Vector2f input = {3.f, -7.f};
        sf::Vector2f result = orbitDirection(input);

        float dot = input.x * result.x + input.y * result.y;
        REQUIRE(dot == Approx(0.f));
    }

    SECTION("zero vector")
    {
        sf::Vector2f result = orbitDirection({0.f, 0.f});
        REQUIRE(result.x == Approx(0.f));
        REQUIRE(result.y == Approx(0.f));
    }
}

TEST_CASE("gravity calculates correct acceleration", "[gravity]")
{
    const float G = 1000.0f;

    SECTION("horizontal separation")
    {
        sf::Vector2f smaller = {0.f, 0.f};
        sf::Vector2f bigger = {100.f, 0.f};
        sf::Vector2f accel = gravity(smaller, bigger, 1.f, 1000.f);

        // Force should point toward the bigger object (positive x direction)
        REQUIRE(accel.x > 0.f);
        REQUIRE(accel.y == Approx(0.f));

        // Check magnitude: F = G*M/r^2 = 1000*1000/10000 = 100
        float magnitude = std::sqrt(accel.x * accel.x + accel.y * accel.y);
        REQUIRE(magnitude == Approx(100.f));
    }

    SECTION("vertical separation")
    {
        sf::Vector2f smaller = {0.f, 0.f};
        sf::Vector2f bigger = {0.f, 50.f};
        sf::Vector2f accel = gravity(smaller, bigger, 1.f, 500.f);

        // Force should point toward the bigger object (positive y direction)
        REQUIRE(accel.x == Approx(0.f));
        REQUIRE(accel.y > 0.f);

        // Check magnitude: F = G*M/r^2 = 1000*500/2500 = 200
        float magnitude = std::sqrt(accel.x * accel.x + accel.y * accel.y);
        REQUIRE(magnitude == Approx(200.f));
    }

    SECTION("diagonal separation")
    {
        sf::Vector2f smaller = {0.f, 0.f};
        sf::Vector2f bigger = {30.f, 40.f}; // distance = 50
        sf::Vector2f accel = gravity(smaller, bigger, 1.f, 2500.f);

        // Force should point toward bigger object
        REQUIRE(accel.x > 0.f);
        REQUIRE(accel.y > 0.f);

        // Check magnitude: F = G*M/r^2 = 1000*2500/2500 = 1000
        float magnitude = std::sqrt(accel.x * accel.x + accel.y * accel.y);
        REQUIRE(magnitude == Approx(1000.f));

        // Check direction components (3-4-5 triangle ratio)
        REQUIRE(accel.x == Approx(600.f)); // 1000 * 0.6
        REQUIRE(accel.y == Approx(800.f)); // 1000 * 0.8
    }

    SECTION("reversed positions")
    {
        sf::Vector2f smaller = {100.f, 0.f};
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f accel = gravity(smaller, bigger, 1.f, 1000.f);

        // Force should point toward the bigger object (negative x direction)
        REQUIRE(accel.x < 0.f);
        REQUIRE(accel.y == Approx(0.f));
    }

    SECTION("smaller mass doesn't affect acceleration")
    {
        sf::Vector2f pos1 = {0.f, 0.f};
        sf::Vector2f pos2 = {100.f, 0.f};

        sf::Vector2f accel1 = gravity(pos1, pos2, 1.f, 1000.f);
        sf::Vector2f accel2 = gravity(pos1, pos2, 100.f, 1000.f);

        // Acceleration should be the same regardless of smaller mass
        REQUIRE(accel1.x == Approx(accel2.x));
        REQUIRE(accel1.y == Approx(accel2.y));
    }

    SECTION("inverse square law")
    {
        sf::Vector2f smaller = {0.f, 0.f};
        sf::Vector2f bigger1 = {100.f, 0.f};
        sf::Vector2f bigger2 = {200.f, 0.f};

        sf::Vector2f accel1 = gravity(smaller, bigger1, 1.f, 1000.f);
        sf::Vector2f accel2 = gravity(smaller, bigger2, 1.f, 1000.f);

        float mag1 = std::sqrt(accel1.x * accel1.x + accel1.y * accel1.y);
        float mag2 = std::sqrt(accel2.x * accel2.x + accel2.y * accel2.y);

        // At double the distance, force should be 1/4
        REQUIRE(mag2 == Approx(mag1 / 4.f));
    }

    SECTION("minimum distance safety check")
    {
        sf::Vector2f smaller = {0.f, 0.f};
        sf::Vector2f bigger = {10.f, 0.f}; // distance < 20
        sf::Vector2f accel = gravity(smaller, bigger, 1.f, 1000.f);

        REQUIRE(accel.x == 0.f);
        REQUIRE(accel.y == 0.f);
    }

    SECTION("just above minimum distance")
    {
        sf::Vector2f smaller = {0.f, 0.f};
        sf::Vector2f bigger = {21.f, 0.f}; // distance > 20
        sf::Vector2f accel = gravity(smaller, bigger, 1.f, 1000.f);

        // Should have non-zero acceleration
        REQUIRE(accel.x > 0.f);
    }
}

TEST_CASE("orbitalVelocity calculates correct velocity", "[orbitalVelocity]")
{
    const float G = 1000.0f;

    SECTION("horizontal separation gives vertical velocity")
    {
        sf::Vector2f smaller = {100.f, 0.f};
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f velocity = orbitalVelocity(smaller, bigger, 1000.f);

        // Velocity should be perpendicular to separation
        REQUIRE(velocity.x == Approx(0.f));
        REQUIRE(velocity.y != Approx(0.f));

        // Check magnitude: v = sqrt(G*M/r) = sqrt(1000*1000/100) = sqrt(10000) = 100
        float magnitude = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        REQUIRE(magnitude == Approx(100.f));
    }

    SECTION("vertical separation gives horizontal velocity")
    {
        sf::Vector2f smaller = {0.f, 100.f};
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f velocity = orbitalVelocity(smaller, bigger, 1000.f);

        // Velocity should be perpendicular to separation
        REQUIRE(velocity.x != Approx(0.f));
        REQUIRE(velocity.y == Approx(0.f));
    }

    SECTION("velocity is perpendicular to position vector")
    {
        sf::Vector2f smaller = {30.f, 40.f};
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f velocity = orbitalVelocity(smaller, bigger, 2500.f);

        sf::Vector2f separation = smaller - bigger;
        float dot = separation.x * velocity.x + separation.y * velocity.y;
        REQUIRE(dot == Approx(0.f));
    }

    SECTION("orbital speed scales with sqrt(mass)")
    {
        sf::Vector2f smaller = {100.f, 0.f};
        sf::Vector2f bigger = {0.f, 0.f};

        sf::Vector2f vel1 = orbitalVelocity(smaller, bigger, 1000.f);
        sf::Vector2f vel2 = orbitalVelocity(smaller, bigger, 4000.f);

        float mag1 = std::sqrt(vel1.x * vel1.x + vel1.y * vel1.y);
        float mag2 = std::sqrt(vel2.x * vel2.x + vel2.y * vel2.y);

        // 4x mass should give 2x velocity
        REQUIRE(mag2 == Approx(mag1 * 2.f));
    }

    SECTION("orbital speed scales with sqrt(1/distance)")
    {
        sf::Vector2f smaller1 = {100.f, 0.f};
        sf::Vector2f smaller2 = {400.f, 0.f};
        sf::Vector2f bigger = {0.f, 0.f};

        sf::Vector2f vel1 = orbitalVelocity(smaller1, bigger, 1000.f);
        sf::Vector2f vel2 = orbitalVelocity(smaller2, bigger, 1000.f);

        float mag1 = std::sqrt(vel1.x * vel1.x + vel1.y * vel1.y);
        float mag2 = std::sqrt(vel2.x * vel2.x + vel2.y * vel2.y);

        // 4x distance should give 0.5x velocity
        REQUIRE(mag2 == Approx(mag1 * 0.5f));
    }

    SECTION("minimum distance safety check")
    {
        sf::Vector2f smaller = {10.f, 0.f};
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f velocity = orbitalVelocity(smaller, bigger, 1000.f);

        REQUIRE(velocity.x == 0.f);
        REQUIRE(velocity.y == 0.f);
    }

    SECTION("just above minimum distance")
    {
        sf::Vector2f smaller = {21.f, 0.f};
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f velocity = orbitalVelocity(smaller, bigger, 1000.f);

        // Should have non-zero velocity
        float magnitude = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        REQUIRE(magnitude > 0.f);
    }

    SECTION("orbit direction is clockwise")
    {
        // Object to the right should get positive y velocity
        sf::Vector2f smaller = {100.f, 0.f};
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f velocity = orbitalVelocity(smaller, bigger, 1000.f);

        REQUIRE(velocity.x == Approx(0.f));
        REQUIRE(velocity.y > 0.f); // Positive y = downward in screen space = clockwise orbit
    }

    SECTION("orbit direction verification - top position")
    {
        // Object above center (negative y in math coords) should get positive x velocity (rightward = clockwise)
        sf::Vector2f smaller = {0.f, -100.f}; // Above in mathematical coords
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f velocity = orbitalVelocity(smaller, bigger, 1000.f);

        REQUIRE(velocity.x > 0.f);
        REQUIRE(velocity.y == Approx(0.f));
    }

    SECTION("orbit direction verification - left position")
    {
        // Object to the left should get negative y velocity
        sf::Vector2f smaller = {-100.f, 0.f};
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f velocity = orbitalVelocity(smaller, bigger, 1000.f);

        REQUIRE(velocity.x == Approx(0.f));
        REQUIRE(velocity.y < 0.f);
    }

    SECTION("orbit direction verification - bottom position")
    {
        // Object below center should get negative x velocity
        sf::Vector2f smaller = {0.f, 100.f};
        sf::Vector2f bigger = {0.f, 0.f};
        sf::Vector2f velocity = orbitalVelocity(smaller, bigger, 1000.f);

        REQUIRE(velocity.x < 0.f);
        REQUIRE(velocity.y == Approx(0.f));
    }
}
