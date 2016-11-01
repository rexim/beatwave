#ifndef BEATWAVE_DROP_HPP_
#define BEATWAVE_DROP_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <core/animated.hpp>
#include <beatwave/filledcircle.hpp>

namespace sf {
    class RenderTarget;
}

class Drop: public FilledCircle
{
public:
    Drop(const sf::Color &color);

    void drop(const sf::Vector2f &begin,
              const sf::Vector2f &end,
              float radius);
private:
    Animated<double> m_radius;
    Animated<sf::Vector2f> m_position;

    sf::Color m_color;
};

#endif  // BEATWAVE_DROP_HPP_
