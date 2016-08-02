#include <iostream>
#include <fstream>
#include <core/captures.hpp>

void dumpCaptureInfo(const std::deque<Capture> &captures,
                     const std::string &capturesFileName)
{
    std::ofstream capturesFile(capturesFileName);

    if (capturesFile) {
        for (const auto &capture: captures) {
            int actionType;
            sf::Int32 captureTime;
            std::tie(actionType, captureTime) = capture;
            capturesFile << actionType << ' ' << captureTime << std::endl;
        }
    } else {
        std::cout << "[ERROR] Cannot load " << capturesFileName << std::endl;
    }
}

void loadCaptureInfo(std::deque<Capture> &captures,
                      const std::string &capturesFileName)
{
    std::ifstream capturesFile(capturesFileName);

    if (capturesFile) {
        int actionType;
        sf::Int32 captureTime;
        while (capturesFile >> actionType >> captureTime) {
            captures.push_back(std::make_pair(actionType, captureTime));
        }
    } else {
        std::cout << "[ERROR] Cannot load " << capturesFileName << std::endl;
    }
}
