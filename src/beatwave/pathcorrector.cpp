#include <beatwave/pathcorrector.hpp>

PathCorrector::PathCorrector(const sf::Vector2f &position):
    body(10.0f, position, sf::Color(255, 100, 100))
{}

void PathCorrector::tick(int32_t deltaTime)
{
    body.tick(deltaTime);
}

void PathCorrector::render(sf::RenderTarget *renderTarget)
{
    body.render(renderTarget);
}
