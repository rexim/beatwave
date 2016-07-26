#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>

#include "player.hpp"
#include "tunnel.hpp"

namespace sf
{
    class RenderTarget;
}

class Game
{
public:
    Game();

    bool init();
    void run();

    void render(sf::RenderTarget *renderTarget);

    void kick();
    void snare();
    void hihat();
    void shaman();

    void reset();

private:
    bool initSounds();

private:
    Player player;
    Tunnel tunnel;
    sf::Sound kickSound, snareSound, hihatSound, shamanSound;
};

#endif  // GAME_HPP_
