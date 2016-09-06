#ifndef CIRCLE_HPP_
#define CIRCLE_HPP_

#include <core/animatedgroup.hpp>

class Circle: public AnimatedGroup<float, sf::Vector2f, sf::Color>
{
public:
    enum Property
    {
        Radius = 0,
        Position,
        Color
    };

    using AnimatedGroup::AnimatedGroup;

    void render(sf::RenderTarget *renderTarget) const
    {
        auto radius = value<Radius>();

        sf::CircleShape circle(radius);
        circle.setFillColor(value<Color>());
        circle.setPosition(value<Position>() - sf::Vector2f(radius, radius));
        renderTarget->draw(circle);
    }
};

#endif  // CIRCLE_HPP_
