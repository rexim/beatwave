#include <cstdlib>
#include <iostream>
#include <vector>
#include <deque>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "tunnel.hpp"
#include "captures.hpp"

void generateTunnelPoints(const std::deque<Capture> &captures,
                          const sf::Vector2f &position,
                          float velocity,
                          std::vector<sf::Vector2f> &points)
{
    sf::Vector2f currentPosition = position;

    points.push_back(position);

    for (size_t i = 0; i < captures.size() - 1; ++i) {
        int actionType = captures[i].first;
        sf::Int32 intervalTime = captures[i + 1].second;
        sf::Vector2f direction = actionType == 0 ? sf::Vector2f(1.0f, 0.0f) : sf::Vector2f(0.0f, 1.0f);

        currentPosition += (direction * velocity * (intervalTime * 0.001f));
        points.push_back(currentPosition);
    }
}

void generateTunnelRects(const std::vector<sf::Vector2f> &points,
                         float radius,
                         Tunnel &tunnel)
{
    for (size_t i = 0; i < points.size() - 1; ++i) {
        const sf::Vector2f radiusVector = sf::Vector2f(radius, radius);
        const sf::Vector2f leftUpper = points[i] + radiusVector * -1.0f;
        const sf::Vector2f rightBottom = points[i + 1] + radiusVector;

        tunnel.push_back(sf::FloatRect(leftUpper.x, leftUpper.y,
                                       std::abs(static_cast<long>(leftUpper.x - rightBottom.x)),
                                       std::abs(static_cast<long>(leftUpper.y - rightBottom.y))));
    }
}

void generateTunnelFromCaptures(const std::deque<Capture> &captures,
                                const sf::Vector2f &position,
                                float radius,
                                float velocity,
                                Tunnel &tunnel)
{
    std::vector<sf::Vector2f> points;
    generateTunnelPoints(captures, position, velocity, points);
    generateTunnelRects(points, radius, tunnel);
}

int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    const float errorBuffer = 20.0f;
    std::deque<Capture> captures;
    Tunnel tunnel;

    loadCaptureInfo(captures, "replay.txt");
    generateTunnelFromCaptures(captures, sf::Vector2f(200.0f, 200.0f), 50.0f + errorBuffer, 500.0f, tunnel);

    for (const auto &rect: tunnel) {
        std::cout << rect.left << ' '<< rect.top << ' ' << rect.width << ' ' << rect.height << std::endl;
    }

    return 0;
}
