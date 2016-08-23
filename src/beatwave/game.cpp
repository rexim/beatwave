#include <iostream>

#include <SFML/Audio/SoundBuffer.hpp>

#include <beatwave/game.hpp>
#include <beatwave/config.hpp>
#include <core/util.hpp>
#include <core/dsl.hpp>

namespace
{
}

Game::Game():
    player(config::PLAYER_INIT_POSITION,
           config::PLAYER_INIT_RADIUS,
           config::PLAYER_INIT_COLOR)
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

    digTunnel("tunnel.txt", tunnel);

    return true;
}

void Game::tick(sf::Int32 deltaTime)
{
    player.tick(deltaTime);
}

void Game::render(sf::RenderTarget *renderTarget)
{
    renderTarget->clear(config::WALL_COLOR);
    player.centerView(renderTarget);

    for (const auto &rect: tunnel) {
        sf::RectangleShape shape;
        shape.setPosition(rect.left, rect.top);
        shape.setSize(sf::Vector2f(rect.width, rect.height));
        shape.setFillColor(sf::Color::Black);
        renderTarget->draw(shape);
    }

    player.render(renderTarget);
}

void Game::kick()
{
    player.step(sf::Color::Red,
                sf::Vector2f(config::PLAYER_MOVE_DISTANCE, 0.0f));
    kickSound.play();
}

void Game::snare()
{
    player.step(sf::Color::Green,
                sf::Vector2f(0.0f, config::PLAYER_MOVE_DISTANCE));
    snareSound.play();
}

void Game::hihat()
{
    player.step(sf::Color::Blue,
                sf::Vector2f(0.0f, -config::PLAYER_MOVE_DISTANCE));
    hihatSound.play();
}

void Game::shaman()
{
    player.step(sf::Color::Yellow,
                sf::Vector2f(-config::PLAYER_MOVE_DISTANCE, 0.0f));
    shamanSound.play();
}

void Game::killPlayer()
{
    player.kill();
}

void Game::reset()
{
    using namespace dsl;

    digTunnel("tunnel.txt", tunnel);
    player.reset();
}
