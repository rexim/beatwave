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

namespace
{
    // FIXME(#47)
    bool rectContainsCircle(const sf::FloatRect &rect,
                            const sf::Vector2f &center,
                            float radius)
    {
        const std::array<float, 4> ds = {
            std::abs(rect.top - center.y),
            std::abs(rect.top + rect.height - 1 - center.y),
            std::abs(rect.left - center.x),
            std::abs(rect.left + rect.width - 1 - center.x)
        };

        return rect.contains(center) && std::all_of(ds.begin(), ds.end(), [radius](float d) {
                return radius < d;
        });
    }
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

void Game::tick(int32_t deltaTime)
{
    player.tick(deltaTime);

    // FIXME(#48): this process should be inside of Player and Tunnel
    // entities.
    if (!player.isDead()) {
        for (const auto &rect: tunnel) {
            if (rectContainsCircle(rect, player.getPosition(), config::PLAYER_INIT_RADIUS)) {
                return;
            }
        }

        player.kill();
    }
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
