#include <cmath>
#include <iostream>
#include <algorithm>
#include <functional>
#include <array>

#include <SFML/Audio/SoundBuffer.hpp>

#include <beatwave/game.hpp>
#include <beatwave/config.hpp>
#include <core/animatedgroup.hpp>
#include <core/util.hpp>
#include <core/dsl.hpp>

Game::Game():
    player(config::PLAYER_INIT_POSITION)
{}

bool Game::initSounds()
{
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

    tunnel.load("tunnel.txt");

    return true;
}

void Game::tick(int32_t deltaTime)
{
    player.tick(deltaTime);
    tunnel.hit(&player);
}

void Game::render(sf::RenderTarget *renderTarget)
{
    renderTarget->clear(config::WALL_COLOR);
    player.centerView(renderTarget);

    tunnel.render(renderTarget);
    player.render(renderTarget);
}

void Game::kick()
{
    player.step(sf::Color::Red,
                sf::Vector2f(config::PLAYER_MOVE_DISTANCE, 0.0f),
                &kickSound);
}

void Game::snare()
{
    player.step(sf::Color::Green,
                sf::Vector2f(0.0f, config::PLAYER_MOVE_DISTANCE),
                &snareSound);
}

void Game::hihat()
{
    player.step(sf::Color::Blue,
                sf::Vector2f(0.0f, -config::PLAYER_MOVE_DISTANCE),
                &hihatSound);
}

void Game::shaman()
{
    player.step(sf::Color::Yellow,
                sf::Vector2f(-config::PLAYER_MOVE_DISTANCE, 0.0f),
                &shamanSound);
}

void Game::killPlayer()
{
    player.kill();
}

void Game::reset()
{
    using namespace dsl;

    tunnel.load("tunnel.txt");
    player.reset();
}
