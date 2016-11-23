#ifndef BEATWAVE_PLAYER_HPP_
#define BEATWAVE_PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <core/animated.hpp>

#include <beatwave/splat.hpp>
#include <beatwave/filledcircle.hpp>

namespace sf
{
    class Sound;
}

class Player
{
public:
    Player(const sf::Vector2f &position = sf::Vector2f(0.0f, 0.0f));

    void tick(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget) const;
    void step(const sf::Color &flashColor,
              const sf::Vector2f direction,
              sf::Sound *sound);
    void centerView(sf::RenderTarget *renderTarget) const;
    void reset();
    void correctPosition(const sf::Vector2f &position);

    void kill();

    bool fits(const sf::FloatRect &rect) const;
    bool intersectsCircle(const sf::Vector2f &center,
                          float radius);
    bool isDead() const;

private:
    FilledCircle m_circle;
    Splat m_splat;
    bool m_dead;
};

#endif  // BEATWAVE_PLAYER_HPP_
