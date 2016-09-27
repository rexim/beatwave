#ifndef LEVELEND_HPP_
#define LEVELEND_HPP_

#include <SFML/System/Vector2.hpp>
#include <core/animated.hpp>

namespace sf
{
    class RenderTarget;
}

class LevelEnd
{
public:
    LevelEnd(const sf::Vector2f &center);

    void tick(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget);

private:
    const sf::Vector2f m_center;
    Animated<float> m_angle;
};

#endif  // LEVELEND_HPP_
