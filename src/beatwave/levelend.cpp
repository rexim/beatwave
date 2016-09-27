#include <cmath>

#include <SFML/Graphics.hpp>

#include <core/math.hpp>
#include <core/dsl.hpp>
#include <beatwave/levelend.hpp>

LevelEnd::LevelEnd(const sf::Vector2f &center):
    m_center(center),
    m_angle(0.0f)
{
    using namespace dsl;
    m_angle.animate(forever(repeat(2,
                                   begin(from(0.0f).to(PI).during(500))
                                   .then(from(PI).to(2.0f * PI).during(100))
                                   .end())));
}

void LevelEnd::tick(int32_t deltaTime)
{
    m_angle.tick(deltaTime);
}

void LevelEnd::render(sf::RenderTarget *renderTarget)
{
    const float radius = 50.0f;
    const auto shift =
        sf::Vector2f(std::cos(m_angle.value()) * radius,
                     std::sin(m_angle.value()) * radius);

    sf::CircleShape circle(10.0f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(m_center + shift - sf::Vector2f(10.0f, 10.0f));
    renderTarget->draw(circle);
}
