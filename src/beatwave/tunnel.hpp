#ifndef BEATWAVE_TUNNEL_HPP_
#define BEATWAVE_TUNNEL_HPP_

#include <core/tunnelvector.hpp>

namespace sf
{
    class RenderTarget;
}

class Player;

class Tunnel
{
public:
    Tunnel(const std::string &fileName);

    void render(sf::RenderTarget *renderTarget) const;
    void hit(Player *player) const;

private:
    TunnelVector m_tunnelVector;
};

#endif  // BEATWAVE_TUNNEL_HPP_
