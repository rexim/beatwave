#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include <memory>

#include <beatwave/player.hpp>
#include <beatwave/tunnel.hpp>
#include <beatwave/pathcorrectorswarm.hpp>

namespace sf
{
    class RenderTarget;
}

class Level
{
public:
    Level(const char *levelFilePath);

    void tick(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget);

    void kick();
    void snare();
    void hihat();
    void shaman();

private:
    std::unique_ptr<Player> m_player;
    std::unique_ptr<Tunnel> m_tunnel;
    std::unique_ptr<PathCorrectorSwarm> m_pathCorrectors;
};

#endif  // LEVEL_HPP_
