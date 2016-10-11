#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iostream>
#include <cmath>

#include <SFML/Graphics/Color.hpp>

#include <core/floatcolor.hpp>
#include <core/util.hpp>

const float PRECISION = 1e-6;

TEST_CASE("FloatColor summation", "[floatcolor]") {
    const auto actualColor = FloatColor(10.0f, 20.0f, 30.0f) + FloatColor(1.0f, 2.0f, 3.0f);
    const auto expectedColor = FloatColor(11.0f, 22.0f, 33.0f);
    REQUIRE ( std::fabs(actualColor.r - expectedColor.r) < PRECISION );
    REQUIRE ( std::fabs(actualColor.g - expectedColor.g) < PRECISION );
    REQUIRE ( std::fabs(actualColor.b - expectedColor.b) < PRECISION );
}

TEST_CASE("FloatColor subtraction", "[floatcolor]") {
    const auto actualColor = FloatColor(10.0f, 20.0f, 30.0f) - FloatColor(1.0f, 2.0f, 3.0f);
    const auto expectedColor = FloatColor(9.0f, 18.0f, 27.0f);
    REQUIRE ( std::fabs(actualColor.r - expectedColor.r) < PRECISION );
    REQUIRE ( std::fabs(actualColor.g - expectedColor.g) < PRECISION );
    REQUIRE ( std::fabs(actualColor.b - expectedColor.b) < PRECISION );
}

TEST_CASE("FloatColor factor multiplication", "[floatcolor]") {
    const auto actualColor = FloatColor(10.0f, 20.0f, 30.0f) * 3.0f;
    const auto expectedColor = FloatColor(30.0f, 60.0f, 90.0f);
    REQUIRE ( std::fabs(actualColor.r - expectedColor.r) < PRECISION );
    REQUIRE ( std::fabs(actualColor.g - expectedColor.g) < PRECISION );
    REQUIRE ( std::fabs(actualColor.b - expectedColor.b) < PRECISION );
}

TEST_CASE("FloatColor add operation", "[floatcolor]") {
    const auto deltaColor = FloatColor(1.0f, 2.0f, 3.0f);
    const auto expectedColor = FloatColor(11.0f, 22.0f, 33.0f);
    auto actualColor = FloatColor(10.0f, 20.0f, 30.0f);
    actualColor += deltaColor;
    REQUIRE ( std::fabs(actualColor.r - expectedColor.r) < PRECISION );
    REQUIRE ( std::fabs(actualColor.g - expectedColor.g) < PRECISION );
    REQUIRE ( std::fabs(actualColor.b - expectedColor.b) < PRECISION );
}

TEST_CASE("", "[float]") {
    const auto expectedColor = sf::Color(101, 201, 56);
    const auto uncompressedColor = uncompressColor(expectedColor);
    const auto actualColor = compressColor(uncompressedColor);

    INFO( (int) actualColor.r << ' '
          << (int) actualColor.g << ' '
          << (int) actualColor.b );

    REQUIRE ( std::fabs(actualColor.r - expectedColor.r) < PRECISION + 1.0f );
    REQUIRE ( std::fabs(actualColor.g - expectedColor.g) < PRECISION + 1.0f );
    REQUIRE ( std::fabs(actualColor.b - expectedColor.b) < PRECISION + 1.0f );
}
