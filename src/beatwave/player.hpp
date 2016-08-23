#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <core/animated.hpp>

class Player
{
public:
    Player(const sf::Vector2f &position,
           float radius,
           const sf::Color &color);

    void tick(sf::Int32 deltaTime);
    void render(sf::RenderTarget *renderTarget) const;
    void step(const sf::Color &flashColor,
              const sf::Vector2f direction);
    void centerView(sf::RenderTarget *renderTarget) const;
    void reset();

    void kill();

private:
    Animated<sf::Vector2f> position;
    Animated<float> radius;
    Animated<sf::Color> color;
};

#endif  // PLAYER_HPP_
