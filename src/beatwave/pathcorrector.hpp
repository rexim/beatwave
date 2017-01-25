#ifndef BEATWAVE_PATHCORRECTOR_HPP_
#define BEATWAVE_PATHCORRECTOR_HPP_

#include <beatwave/circle.hpp>
#include <core/nestedgroup.hpp>

class Player;

class PathCorrector: public NestedGroup<Circle, // core
                                        Circle> // wave
{
public:
    PathCorrector(const sf::Vector2f &position);

    void hit(Player *player);
    bool isDestroyed() const;

private:
    void destroy();

private:
    Circle &m_core;
    Circle &m_wave;
    bool m_destroyed;
};

#endif  // BEATWAVE_PATHCORRECTOR_HPP_
