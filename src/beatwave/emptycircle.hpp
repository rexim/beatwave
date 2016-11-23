#ifndef BEATWAVE_EMPTYCIRCLE_HPP_
#define BEATWAVE_EMPTYCIRCLE_HPP_

#include <core/animatedgroup.hpp>

class EmptyCircle: public AnimatedGroup<float, sf::Vector2f, sf::Color, float>
{
public:
    enum Property
    {
        Radius = 0,
        Position,
        Color,
        Thickness
    };

    using AnimatedGroup::AnimatedGroup;

    void render(sf::RenderTarget *renderTarget) const
    {
        auto radius = value<Radius>();

        sf::CircleShape circle(radius);
        circle.setOutlineColor(value<Color>());
        circle.setOutlineThickness(value<Thickness>());
        circle.setFillColor(sf::Color::Transparent);
        circle.setPosition(value<Position>() - sf::Vector2f(radius, radius));
        renderTarget->draw(circle);
    }

};

#endif  // BEATWAVE_EMPTYCIRCLE_HPP_
