#ifndef BEATWAVE_FILLEDCIRCLE_HPP_
#define BEATWAVE_FILLEDCIRCLE_HPP_

#include <core/animatedgroup.hpp>

namespace {
    class RenderTarget;
}

class FilledCircle: public AnimatedGroup<float,
                                         sf::Vector2f,
                                         sf::Color>
{
public:
    enum Property
    {
        Radius = 0,
        Position,
        Color
    };

    using AnimatedGroup::AnimatedGroup;

    void render(sf::RenderTarget *renderTarget) const;
};

#endif  // BEATWAVE_FILLEDCIRCLE_HPP_
