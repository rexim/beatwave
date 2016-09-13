#ifndef TUNNELVECTOR_HPP_
#define TUNNELVECTOR_HPP_

#include <vector>
#include <SFML/Graphics.hpp>

using TunnelVector = std::vector<sf::FloatRect>;

void loadTunnelVector(const std::string &fileName, TunnelVector &result);

#endif  // TUNNELVECTOR_HPP_
