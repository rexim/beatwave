#ifndef BEATWAVE_EMPTYCIRCLE_HPP_
#define BEATWAVE_EMPTYCIRCLE_HPP_

#include <core/animatedgroup.hpp>

namespace sf {
    class RenderTarget;
}

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

    void render(sf::RenderTarget *renderTarget) const;
};

#endif  // BEATWAVE_EMPTYCIRCLE_HPP_
