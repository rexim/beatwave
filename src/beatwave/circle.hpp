#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include <core/animatedgroup.hpp>

namespace sf {
    class RenderTarget;
}

class Circle: public AnimatedGroup<float,        // radius
                                   sf::Vector2f, // center
                                   sf::Color,    // fill color
                                   sf::Color,    // outline color
                                   float>        // outline thickness
{
public:
    enum Property
    {
        Radius = 0,
        Position,
        FillColor,
        OutlineColor,
        OutlineThickness
    };

    Circle(float radius,
           const sf::Vector2f &position,
           const sf::Color &fillColor,
           const sf::Color &outlineColor = sf::Color::Black,
           float outlineThickness = 0.0f);

    void render(sf::RenderTarget *renderTarget) const;
};

#endif  // CIRCLE_HPP_
