#ifndef SPLAT_HPP_
#define SPLAT_HPP_

#include <vector>
#include <random>
#include <beatwave/drop.hpp>

namespace sf {
    class RenderTarget;
}

class Splat
{
public:
    Splat(size_t dropCount);

    void render(sf::RenderTarget *renderTarget) const;
    void tick(int32_t deltaTime);
    void splat(const sf::Vector2f &center,
               float radius);

private:
    std::vector<Drop> m_drops;
    std::random_device m_rd;
};

#endif  // SPLAT_HPP_
