#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <core/animated.hpp>

#include <beatwave/splat.hpp>

class Player
{
public:
    Player(const sf::Vector2f &position = sf::Vector2f(0.0f, 0.0f),
           float radius = 0.0f,
           const sf::Color &color = sf::Color::Black);

    void tick(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget) const;
    void step(const sf::Color &flashColor,
              const sf::Vector2f direction);
    void centerView(sf::RenderTarget *renderTarget) const;
    void reset();

    void kill();

    sf::Vector2f getPosition()
    {
        return position.value();
    }

    bool isDead() const
    {
        return dead;
    }

private:
    Animated<sf::Vector2f> position;
    Animated<float> radius;
    Animated<sf::Color> color;

    Splat splat;
    bool dead;
};

#endif  // PLAYER_HPP_
