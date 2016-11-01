#ifndef BEATWAVE_EMPTYCIRCLE_HPP_
#define BEATWAVE_EMPTYCIRCLE_HPP_

#include <core/animatedgroup.hpp>

class EmptyCircle: public AnimatedGroup<float, sf::Vector2f, sf::Color>
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
        circle.setOutlineColor(value<Color>());
        circle.setOutlineThickness(1.0f);
        circle.setFillColor(sf::Color::Transparent);
        circle.setPosition(value<Position>() - sf::Vector2f(radius, radius));
        renderTarget->draw(circle);
    }

};

#endif  // BEATWAVE_EMPTYCIRCLE_HPP_
