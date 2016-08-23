#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/System.hpp>

#include <core/animated.hpp>

struct Player
{
    Animated<sf::Vector2f> position;
    Animated<float> radius;
    Animated<sf::Color> color;

    Player(const sf::Vector2f &position = sf::Vector2f(0.0f, 0.0f),
           float radius = 0.0f,
           const sf::Color &color = sf::Color::Black):
        position(position),
        radius(radius),
        color(color)
    {}

    void tick(sf::Int32 deltaTime) {
        position.tick(deltaTime);
        radius.tick(deltaTime);
        color.tick(deltaTime);
    }
};

#endif  // PLAYER_HPP_
