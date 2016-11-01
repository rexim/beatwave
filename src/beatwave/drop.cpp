#include <core/dsl.hpp>
#include <beatwave/drop.hpp>

Drop::Drop(const sf::Color &color):
    FilledCircle(0.0f, sf::Vector2f(0.0f, 0.0f), color)
{}

void Drop::drop(const sf::Vector2f &begin,
                const sf::Vector2f &end,
                float radius)
{
    using namespace dsl;

    // FIXME(#46)
    const int32_t DROP_DURATION = 400;

    animate<Radius>(from((float)radius).to(0.0f).during(DROP_DURATION));
    animate<Position>(from(begin).to(end).during(DROP_DURATION));
}
