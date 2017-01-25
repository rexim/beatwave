#include <SFML/Graphics.hpp>
#include <beatwave/filledcircle.hpp>

void FilledCircle::render(sf::RenderTarget *renderTarget) const
{
    auto radius = value<Radius>();

    sf::CircleShape circle(radius);
    circle.setFillColor(value<Color>());
    circle.setPosition(value<Position>() - sf::Vector2f(radius, radius));
    renderTarget->draw(circle);
}
