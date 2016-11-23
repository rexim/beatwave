#ifndef BEATWAVE_PATHCORRECTOR_HPP_
#define BEATWAVE_PATHCORRECTOR_HPP_

#include <SFML/Graphics.hpp>
#include <beatwave/filledcircle.hpp>
#include <beatwave/emptycircle.hpp>

class Player;

class PathCorrector
{
public:
    PathCorrector(const sf::Vector2f &position);

    void tick(int32_t deltaTime);
    void render(sf::RenderTarget *renderTarget);
    void hit(Player *player);

private:
    FilledCircle body;
    EmptyCircle wave;
};

#endif  // BEATWAVE_PATHCORRECTOR_HPP_
