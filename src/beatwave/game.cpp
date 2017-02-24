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
    player(config::PLAYER_INIT_POSITION),
    tunnel("tunnel.txt")
{
    auto firstPathCorrector =
        std::unique_ptr<PathCorrector>(new PathCorrector(config::PLAYER_INIT_POSITION + sf::Vector2f(100.0f, 0.0f)));
    pathCorrectors.insert(std::move(firstPathCorrector));
}

bool Game::init()
{
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
