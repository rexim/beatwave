#include <iostream>

#include <SFML/Audio/SoundBuffer.hpp>

#include "game.hpp"
#include "lineartransitionbuilder.hpp"

namespace
{
    const sf::Vector2f PLAYER_INIT_POSITION(200.0f, 200.0f);
    const float PLAYER_MOVE_DISTANCE = 250.0f;

    const sf::Int32 MOVE_TIME = 500;
    const sf::Int32 COLOR_TIME = 700;

    const float PLAYER_INIT_RADIUS = 50.0f;
    const sf::Color PLAYER_INIT_COLOR = sf::Color::White;

    void stepPlayer(Player &player,
                    const sf::Color &flashColor,
                    const sf::Vector2f direction,
                    sf::Sound &sound)
    {
        player.color.animate(from(flashColor)
                             .to(sf::Color::White)
                             .during(COLOR_TIME));
        player.position.animate(from(player.position.value())
                                .by(direction)
                                .during(MOVE_TIME));
        sound.play();
    }
}

Game::Game():
    player(PLAYER_INIT_POSITION,
           50.0f,
           sf::Color::White)
{

}

bool Game::initSounds()
{
    sf::SoundBuffer kickBuffer, snareBuffer, hihatBuffer, shamanBuffer;

    if (!kickBuffer.loadFromFile("data/kick.wav")) {
        std::cout << "[ERROR] Cannot load data/kick.wav" << std::endl;
        return false;
    }

    if (!snareBuffer.loadFromFile("data/snare.wav")) {
        std::cout << "[ERROR] Cannot load data/snare.wav" << std::endl;
        return false;
    }

    if (!hihatBuffer.loadFromFile("data/hihat.wav")) {
        std::cout << "[ERROR] Cannot load data/hihat.wav" << std::endl;
        return false;
    }

    if (!shamanBuffer.loadFromFile("data/shaman.wav")) {
        std::cout << "[ERROR] Cannot load data/shaman.wav" << std::endl;
        return false;
    }

    kickSound.setBuffer(kickBuffer);
    snareSound.setBuffer(snareBuffer);
    hihatSound.setBuffer(hihatBuffer);
    shamanSound.setBuffer(shamanBuffer);

    return true;
}

bool Game::init()
{
    if (!initSounds()) {
        return false;
    }

    digTunnel("tunnel.txt", tunnel);

    return true;
}

void Game::render()
{

}

void Game::run()
{

}

void Game::kick()
{
    stepPlayer(player, sf::Color::Red,
               sf::Vector2f(PLAYER_MOVE_DISTANCE, 0.0f),
               kickSound);
}

void Game::snare()
{
    stepPlayer(player, sf::Color::Green,
               sf::Vector2f(0.0f, PLAYER_MOVE_DISTANCE),
               snareSound);
}

void Game::hihat()
{
    stepPlayer(player, sf::Color::Blue,
               sf::Vector2f(0.0f, -PLAYER_MOVE_DISTANCE),
               hihatSound);
}

void Game::shaman()
{
    stepPlayer(player, sf::Color::Yellow,
               sf::Vector2f(-PLAYER_MOVE_DISTANCE, 0.0f),
               shamanSound);
}

void Game::reset()
{
    digTunnel("tunnel.txt", tunnel);
    player.position.animate(from(player.position.value()).to(PLAYER_INIT_POSITION).during(MOVE_TIME));
    player.color.animate(from(player.color.value()).to(PLAYER_INIT_COLOR).during(MOVE_TIME));
    player.radius.animate(from(player.radius.value()).to(PLAYER_INIT_RADIUS).during(MOVE_TIME));
}
