#ifndef TUNNEL_HPP_
#define TUNNEL_HPP_

#include <vector>
#include <SFML/Graphics.hpp>

// FIXME(#48): extract this to an entity to communicate with the
// player on the wall hitting process
using TunnelVector = std::vector<sf::FloatRect>;

void loadTunnelVector(const std::string &fileName, TunnelVector &result);

#endif  // TUNNEL_HPP_
