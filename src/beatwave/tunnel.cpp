#include <SFML/Graphics.hpp>

#include <core/tunnelvector.hpp>

#include <beatwave/tunnel.hpp>
#include <beatwave/player.hpp>

Tunnel::Tunnel(const pugi::xml_node&)
{
    // TODO: Implement XML constructor for Tunnel
    //
    // It should construct the tunnel from the XML node according to
    // the XML schema `level.xsd`. It should also check if the
    // corresponding node exists.
}

Tunnel::Tunnel(const std::string &fileName)
{
    loadTunnelVector(fileName, m_tunnelVector);
}

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
        if (player->fits(rect)) {
            return;
        }
    }

    player->kill();
}
