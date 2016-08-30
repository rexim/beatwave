#ifndef DROP_HPP_
#define DROP_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <core/animated.hpp>

namespace sf {
    class RenderTarget;
}

class Drop
{
public:
    Drop(const sf::Color &color);

    void render(sf::RenderTarget *renderTarget) const;
    void tick(int32_t deltaTime);

    void drop(const sf::Vector2f &begin,
              const sf::Vector2f &end,
              double radius);

private:
    Animated<double> m_radius;
    Animated<sf::Vector2f> m_position;

    sf::Color m_color;
};

#endif  // DROP_HPP_
