#include <iostream>
#include <fstream>
#include <core/tunnel.hpp>

void loadTunnelVector(const std::string &fileName,
                      TunnelVector &result)
{
    std::ifstream tunnelFile(fileName);

    if (!tunnelFile) {
        std::cout << "[ERROR] Cannot load " << fileName << std::endl;
    }

    result.clear();

    sf::Rect<float> rect;
    while(tunnelFile >> rect.left >> rect.top >> rect.width >> rect.height) {
        result.push_back(rect);
    }
}
