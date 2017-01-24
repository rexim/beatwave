#ifndef BEATWAVE_GAME_HPP_
#define BEATWAVE_GAME_HPP_

#include <memory>
#include <set>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>

#include <core/animated.hpp>

#include <beatwave/player.hpp>
#include <beatwave/filledcircle.hpp>
#include <beatwave/tunnel.hpp>
#include <beatwave/pathcorrector2.hpp>

namespace sf
{
    class RenderTarget;
}

class Game
{
public:
    Game();

    bool init();

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
    std::set<std::unique_ptr<PathCorrector2>> pathCorrectors;
    sf::SoundBuffer kickBuffer, snareBuffer, hihatBuffer, shamanBuffer;
    sf::Sound kickSound, snareSound, hihatSound, shamanSound;
};

#endif  // BEATWAVE_GAME_HPP_
