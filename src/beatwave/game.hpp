#ifndef BEATWAVE_GAME_HPP_
#define BEATWAVE_GAME_HPP_

#include <memory>
#include <set>

#include <SFML/Graphics/RenderWindow.hpp>

#include <core/animated.hpp>

#include <beatwave/player.hpp>
#include <beatwave/tunnel.hpp>
#include <beatwave/pathcorrectorswarm.hpp>

namespace sf
{
    class RenderTarget;
}

class Game
{
public:
    Game();

    void render(sf::RenderTarget *renderTarget);
    void tick(int32_t deltaTime);

    void kick();
    void snare();
    void hihat();
    void shaman();
    void killPlayer();

    void reset();

private:
    bool initSounds();

private:
    Player player;
    Tunnel tunnel;
    PathCorrectorSwarm pathCorrectors;
};

#endif  // BEATWAVE_GAME_HPP_
