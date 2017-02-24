#ifndef BEATWAVE_PLAYER_HPP_
#define BEATWAVE_PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <pugixml.hpp>

#include <core/animated.hpp>

#include <beatwave/splat.hpp>
#include <beatwave/circle.hpp>
#include <beatwave/drumset.hpp>
#include <beatwave/defaultdrumset.hpp>

namespace sf
{
    class Sound;
}

class Player
{
public:
    Player(const pugi::xml_node &node,
           std::unique_ptr<DrumSet> &&drumSet = std::unique_ptr<DrumSet>(new DefaultDrumSet()));

    Player(const sf::Vector2f &position = sf::Vector2f(0.0f, 0.0f),
           std::unique_ptr<DrumSet> &&drumSet = std::unique_ptr<DrumSet>(new DefaultDrumSet()));

    void tick(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget) const;

    void kickStep();
    void snareStep();
    void hihatStep();
    void shamanStep();

    void centerView(sf::RenderTarget *renderTarget) const;
    void reset();
    void correctPosition(const sf::Vector2f &position);

    void kill();

    bool fits(const sf::FloatRect &rect) const;
    bool intersectsCircle(const sf::Vector2f &center,
                          float radius);
    bool isDead() const;

private:
    void step(const sf::Color &flashColor,
              const sf::Vector2f direction);

private:
    Circle m_circle;
    Splat m_splat;
    bool m_dead;
    std::unique_ptr<DrumSet> m_drumSet;
};

#endif  // BEATWAVE_PLAYER_HPP_
