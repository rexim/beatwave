#ifndef BEATWAVE_PATHCORRECTOR_HPP_
#define BEATWAVE_PATHCORRECTOR_HPP_

#include <beatwave/filledcircle.hpp>
#include <beatwave/emptycircle.hpp>
#include <core/nestedgroup.hpp>

class Player;

class PathCorrector: public NestedGroup<FilledCircle, // core
                                        EmptyCircle>  // wave
{
public:
    PathCorrector(const sf::Vector2f &position);

    void hit(Player *player);
    bool isDestroyed() const;

private:
    void destroy();

private:
    FilledCircle &m_core;
    EmptyCircle &m_wave;
    bool m_destroyed;
};

#endif  // BEATWAVE_PATHCORRECTOR_HPP_
