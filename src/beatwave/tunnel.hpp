#ifndef TUNNEL_HPP_
#define TUNNEL_HPP_

#include <core/tunnelvector.hpp>

namespace sf
{
    class RenderTarget;
}

class Tunnel
{
public:
    Tunnel(const TunnelVector &tunnelVector);

    void render(sf::RenderTarget *renderTarget) const;

private:
    const TunnelVector m_tunnelVector;
};

#endif  // TUNNEL_HPP_
