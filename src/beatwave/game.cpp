#include <cmath>
#include <iostream>
#include <algorithm>
#include <functional>
#include <array>
#include <vector>

#include <SFML/Audio/SoundBuffer.hpp>

#include <beatwave/game.hpp>
#include <beatwave/config.hpp>
#include <core/animatedgroup.hpp>
#include <core/util.hpp>
#include <core/dsl.hpp>

Game::Game():
    player(config::PLAYER_INIT_POSITION),
    tunnel("tunnel.txt"),
    pathCorrectors({ config::PLAYER_INIT_POSITION + sf::Vector2f(100.0f, 0.0f),
                     config::PLAYER_INIT_POSITION + sf::Vector2f(100.0f, 100.0f) })
{}

void Game::tick(int32_t deltaTime)
{
    player.tick(deltaTime);
    pathCorrectors.tick(deltaTime);

    tunnel.hit(&player);
    pathCorrectors.hit(&player);
}

void Game::render(sf::RenderTarget *renderTarget)
{
    renderTarget->clear(config::WALL_COLOR);
    player.centerView(renderTarget);

    tunnel.render(renderTarget);
    player.render(renderTarget);
    pathCorrectors.render(renderTarget);
}

void Game::kick()
{
    player.kickStep();
}

void Game::snare()
{
    player.snareStep();
}

void Game::hihat()
{
    player.hihatStep();
}

void Game::shaman()
{
    player.shamanStep();
}

void Game::killPlayer()
{
    player.kill();
}

void Game::reset()
{
    player.reset();
}
