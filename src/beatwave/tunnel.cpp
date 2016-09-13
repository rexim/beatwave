#include <SFML/Graphics.hpp>
#include <beatwave/tunnel.hpp>
#include <beatwave/player.hpp>

Tunnel::Tunnel(const TunnelVector &tunnelVector):
    m_tunnelVector(tunnelVector)
{}

void Tunnel::render(sf::RenderTarget *renderTarget) const
{
    for (const auto &rect: m_tunnelVector) {
        sf::RectangleShape shape;
        shape.setPosition(rect.left, rect.top);
        shape.setSize(sf::Vector2f(rect.width, rect.height));
        shape.setFillColor(sf::Color::Black);
        renderTarget->draw(shape);
    }
}

void Tunnel::hit(Player *player) const
{
    if (player == nullptr) {
        return;
    }

    for (const auto &rect: m_tunnelVector) {
        if (!player->isCompletlyInsideOf(rect)) {
            player->kill();
            return;
        }
    }
}
