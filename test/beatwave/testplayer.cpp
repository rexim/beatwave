#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <beatwave/config.hpp>
#include <beatwave/player.hpp>

TEST_CASE("Player should provide a way to tell if it intersects a circle", "[player]") {
    Player player(sf::Vector2f(0.0f, 0.0f));

    REQUIRE( player.intersectsCircle(sf::Vector2f(config::PLAYER_INIT_RADIUS + 10.0, 0.0), 20.0) );
    REQUIRE( !player.intersectsCircle(sf::Vector2f(config::PLAYER_INIT_RADIUS + 10.0, 0.0), 5.0) );
}
