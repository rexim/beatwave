#include <cmath>

#include <SFML/Graphics.hpp>
#include <beatwave/splat.hpp>

Splat::Splat(size_t dropCount)
{
    for (size_t i = 0; i < dropCount; ++i) {
        m_drops.emplace_back(sf::Color::White);
    }
}

void Splat::render(sf::RenderTarget *renderTarget) const
{
    for (const auto &drop: m_drops) {
        drop.render(renderTarget);
    }
}

void Splat::tick(int32_t deltaTime)
{
    for (auto &drop: m_drops) {
        drop.tick(deltaTime);
    }
}

void Splat::splat(const sf::Vector2f &center,
                  float radius)
{
    const float step = 2.0f * 3.14159265f / m_drops.size();

    for (size_t i = 0; i < m_drops.size(); ++i) {
        const sf::Vector2f direction(std::cos(step * i),
                                     std::sin(step * i));
        m_drops[i].drop(center,
                        center + direction * radius,
                        20.0f);
    }
}
