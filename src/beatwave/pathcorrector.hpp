#ifndef BEATWAVE_PATHCORRECTOR_HPP_
#define BEATWAVE_PATHCORRECTOR_HPP_

#include <SFML/Graphics.hpp>
#include <beatwave/circle.hpp>

class PathCorrector
{
public:
    PathCorrector(const sf::Vector2f &position);

    void tick(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget);

private:
    Circle body;
};

#endif  // BEATWAVE_PATHCORRECTOR_HPP_
