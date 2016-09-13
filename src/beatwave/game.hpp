#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>

#include <core/tunnelvector.hpp>
#include <core/animated.hpp>

#include <beatwave/player.hpp>
#include <beatwave/circle.hpp>

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
    TunnelVector tunnel;
    sf::SoundBuffer kickBuffer, snareBuffer, hihatBuffer, shamanBuffer;
    sf::Sound kickSound, snareSound, hihatSound, shamanSound;
};

#endif  // GAME_HPP_
