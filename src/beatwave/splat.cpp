#include <SFML/Graphics.hpp>
#include <beatwave/splat.hpp>

Splat::Splat(size_t dropCount)
{
    for (size_t i = 0; i < dropCount; ++i) {
        m_drops.emplace_back(sf::Color::Red);
    }
}
