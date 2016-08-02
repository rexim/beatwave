#include <iostream>
#include <fstream>
#include "tunnel.hpp"

void digTunnel(const std::string &plan,
               Tunnel &result)
{
    std::ifstream tunnelFile(plan);
    
    if (!tunnelFile) {
        std::cout << "[ERROR] Cannot load " << plan << std::endl;
    }

    result.clear();

    sf::Rect<float> rect;
    while(tunnelFile >> rect.left >> rect.top >> rect.width >> rect.height) {
        result.push_back(rect);
    }
}
