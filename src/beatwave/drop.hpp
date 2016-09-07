#ifndef DROP_HPP_
#define DROP_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <core/animated.hpp>
#include <beatwave/circle.hpp>

namespace sf {
    class RenderTarget;
}

class Drop: public Circle
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

#endif  // DROP_HPP_
