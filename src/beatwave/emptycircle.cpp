#include <SFML/Graphics.hpp>
#include <beatwave/emptycircle.hpp>

void EmptyCircle::render(sf::RenderTarget *renderTarget) const
{
    auto radius = value<Radius>();

    sf::CircleShape circle(radius);
    circle.setOutlineColor(value<Color>());
    circle.setOutlineThickness(value<Thickness>());
    circle.setFillColor(sf::Color::Transparent);
    circle.setPosition(value<Position>() - sf::Vector2f(radius, radius));
    renderTarget->draw(circle);
}
