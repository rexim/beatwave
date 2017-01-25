#include <SFML/Graphics.hpp>
#include <beatwave/circle.hpp>

Circle::Circle(float radius,
               const sf::Vector2f &position,
               const sf::Color &fillColor,
               const sf::Color &outlineColor,
               float outlineThickness):
    AnimatedGroup(radius, position,
                  fillColor, outlineColor,
                  outlineThickness)
{}

void Circle::render(sf::RenderTarget *renderTarget) const
{
    const auto radius = value<Radius>();

    sf::CircleShape circle(radius);
    circle.setOutlineColor(value<OutlineColor>());
    circle.setOutlineThickness(value<OutlineThickness>());
    circle.setFillColor(value<FillColor>());
    circle.setPosition(value<Position>() - sf::Vector2f(radius, radius));
    renderTarget->draw(circle);
}
