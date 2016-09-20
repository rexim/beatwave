#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <core/animated.hpp>

#include <beatwave/splat.hpp>
#include <beatwave/circle.hpp>

class Player
{
public:
    Player(const sf::Vector2f &position = sf::Vector2f(0.0f, 0.0f));

    void tick(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget) const;
    void step(const sf::Color &flashColor,
              const sf::Vector2f direction);
    void centerView(sf::RenderTarget *renderTarget) const;
    void reset();

    void kill();

    bool fits(const sf::FloatRect &rect) const;

private:
    Circle m_circle;
    Splat m_splat;
    bool m_dead;
};

#endif  // PLAYER_HPP_
