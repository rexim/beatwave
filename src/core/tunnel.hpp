#ifndef TUNNEL_HPP_
#define TUNNEL_HPP_

#include <vector>
#include <SFML/Graphics.hpp>

using Tunnel = std::vector<sf::FloatRect>;

void digTunnel(const std::string &plan, Tunnel &result);

#endif  // TUNNEL_HPP_
