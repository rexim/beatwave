#ifndef TUNNELGENERATOR_HPP_
#define TUNNELGENERATOR_HPP_

#include "./tunnel.hpp"
#include "./captures.hpp"

void generateTunnelsFrom(const std::deque<Capture> &captures,
                         Tunnel &tunnel);

#endif  // TUNNELGENERATOR_HPP_
