#include <core/dsl.hpp>
#include <beatwave/drop.hpp>

Drop::Drop(const sf::Color &color):
    m_radius(0.0f),
    m_position(sf::Vector2f(0.0f, 0.0f)),
    m_color(color)
{}

void Drop::render(sf::RenderTarget *renderTarget) const
{
    sf::CircleShape circle(m_radius.value());
    circle.setFillColor(m_color);
    circle.setPosition(m_position.value() - sf::Vector2f(m_radius.value(), m_radius.value()));
    renderTarget->draw(circle);
}

void Drop::drop(const sf::Vector2f &begin,
                const sf::Vector2f &end,
                double radius)
{
    using namespace dsl;

    // FIXME(#46)
    const int32_t DROP_DURATION = 400;

    m_radius.animate(from(radius).to(0.0f).during(DROP_DURATION));
    m_position.animate(from(begin).to(end).during(DROP_DURATION));
}


void Drop::tick(int32_t deltaTime)
{
    m_radius.tick(deltaTime);
    m_position.tick(deltaTime);
}
