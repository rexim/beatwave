#ifndef TUNNEL_HPP_
#define TUNNEL_HPP_

#include <core/tunnelvector.hpp>

namespace sf
{
    class RenderTarget;
}

class Player;

class Tunnel
{
public:
    Tunnel();

    void render(sf::RenderTarget *renderTarget) const;
    void hit(Player *player) const;
    void load(const std::string &fileName);

private:
    TunnelVector m_tunnelVector;
};

#endif  // TUNNEL_HPP_
