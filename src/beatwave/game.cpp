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
{
    auto firstPathCorrector =
        std::unique_ptr<PathCorrector>(new PathCorrector(config::PLAYER_INIT_POSITION + sf::Vector2f(100.0f, 0.0f)));
    pathCorrectors.insert(std::move(firstPathCorrector));
}

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

    for (auto &pathCorrector: pathCorrectors) {
        pathCorrector->tick(deltaTime);
    }

    tunnel.hit(&player);

    for (auto &pathCorrector: pathCorrectors) {
        pathCorrector->hit(&player);
    }
}

void Game::render(sf::RenderTarget *renderTarget)
{
    renderTarget->clear(config::WALL_COLOR);
    player.centerView(renderTarget);

    tunnel.render(renderTarget);
    player.render(renderTarget);

    for (auto &pathCorrector: pathCorrectors) {
        pathCorrector->render(renderTarget);
    }
}

// TODO: Move Game::(kick|snare|hihat|shaman) into Player::(kick|snare|hihat|shaman)
//
// The exact color, distance and the sound should not be decided
// outside of the Player class. It may require to introduce a new
// entity that keeps all of the sounds and play them. It may be called
// something like DrumSet.
//
// This will virtually eliminate the difference between classes Game
// and Level. Which may allow to get rid of the former.

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
